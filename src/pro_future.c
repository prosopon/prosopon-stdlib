#include "prosopon_stdlib.h"

#include "prosopon_macros.h"



typedef struct pro_future_queue_node pro_future_queue_node;

typedef struct pro_future_queue pro_future_queue;
struct pro_future_queue
{
    pro_future_queue_node *front, *back;
};

struct pro_future_queue_node
{
    pro_future_queue_node* next;
    pro_ref msg;
};

static pro_future_queue_node* pro_future_queue_node_new(pro_state_ref s,
    pro_ref msg, pro_future_queue_node* next)
{
    pro_alloc* alloc;
    pro_get_alloc(s, &alloc);
    pro_future_queue_node* t = alloc(0, sizeof(*t));
    t->msg = msg;
    t->next = next;
    return t;
}


static void future_queue_deconstructor(pro_state_ref s, void* data)
{
    pro_future_queue* t = data;

    pro_alloc* alloc;
    pro_get_alloc(s, &alloc);

    for (pro_future_queue_node* node = t->front; node; )
    {
        pro_future_queue_node* next = node->next;
        pro_release(s, node->msg);
        alloc(node, 0);
        node = next;
    }

    PRO_DEFAULT_UD_DECONSTRUCTOR(s, data);
}


static void future_behavior_impl(pro_state_ref s,
    pro_ref t, pro_ref msg, pro_ref data)
{
    pro_future_queue* queue;
    pro_ud_write(s, data, (void**)&queue);

    unsigned int msg_length;
    pro_list_length(s, msg, &msg_length);
    if (msg_length > 0)
    {
        pro_ref first;
        pro_list_get(s, msg, 0, &first);
        if (pro_match_string(s, first, "write"))
        {
            pro_ref val;
            pro_list_get(s, msg, 1, &val);
        
            for (pro_future_queue_node* node = queue->front; node; node = node->next)
                pro_send(s, val, node->msg);
            
            pro_become(s, t, val);
            pro_release(s, val);
            
            pro_release(s, first);
            return;
        }
        pro_release(s, first);
    }
    
    pro_retain(s, msg);
    pro_future_queue_node* node = pro_future_queue_node_new(s, msg, 0);
    
    if (!queue->front && !queue->back)
        queue->front = queue->back = node;
    else
    {
        queue->back->next = node;
        queue->back = node;
    }
}


#pragma mark -
#pragma mark Public

PRO_LIBCORE pro_ref pro_future_create(pro_state_ref s)
{
    // create ud
    pro_future_queue* queue;
    pro_ref ud;
    pro_ud_create(s, sizeof(*queue), future_queue_deconstructor, &ud);
    
    // write ud
    pro_ud_write(s, ud, (void**)&queue);
    queue->front = queue->back = 0;
    
    // crreate future actor
    pro_ref future;
    pro_actor_create(s, PRO_DEFAULT_ACTOR_TYPE, future_behavior_impl,
        ud, &future);
    pro_release(s, ud);
    
    return future;
}

PRO_LIBCORE void pro_future_write(pro_state_ref s, pro_ref t, pro_ref val)
{
    pro_ref msg = PRO_EMPTY_REF;
    pro_list_create(s, &msg);
    pro_ref write_str = pro_string_create(s, "write");
    pro_list_append_inplace(s, &msg, write_str);
    pro_list_append_inplace(s, &msg, val);
    
    pro_send(s, t, msg);
    
    pro_release(s, write_str);
    pro_release(s, msg);
}

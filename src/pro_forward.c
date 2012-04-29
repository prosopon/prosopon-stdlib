#include "prosopon_stdlib.h"

#include <prosopon/prosopon.h>

#pragma mark Private

typedef struct
{
    pro_ref dest;
} pro_forward_data;


static void behavior_impl(pro_state_ref s,
    pro_ref t, pro_ref msg, pro_ref ud)
{
    const pro_forward_data* data;
    pro_ud_read(s, ud, (const void**)&data);
    
    pro_ref dest = data->dest;
    
    pro_send(s, dest, msg);
}


static void forward_deconstructor(pro_state_ref s, void* d)
{
    pro_forward_data* data = d;
    pro_release(s, data->dest);
    PRO_DEFAULT_UD_DECONSTRUCTOR(s, d);
}


#pragma mark -
#pragma mark Public 

PRO_LIBCORE pro_ref pro_forward_create(pro_state_ref s, pro_ref dest)
{
    pro_forward_data* data;
    pro_ref ud;
    pro_ud_create(s, sizeof(*data), forward_deconstructor, &ud);

    pro_ud_write(s, ud, (void**)&data);
    data->dest = dest;

    pro_ref actor;    
    pro_actor_create(s, PRO_DEFAULT_ACTOR_TYPE, behavior_impl, ud, &actor);
    pro_release(s, ud);
    
    return actor;
}

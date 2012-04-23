#include "pro_stdio.h"

#include <stdio.h>


#pragma mark Private

static void stdio_behavior_impl(pro_state_ref s,
    pro_ref t, pro_ref msg, pro_ref data)
{
    unsigned int msg_length;
    pro_list_length(s, msg, &msg_length);
    
    for (unsigned int i = 0; i < msg_length; ++i)
    {
        pro_ref arg;
        pro_list_get(s, msg, i, &arg);
        
        pro_ref ud;
        pro_to_string(s, arg, &ud);
        
        if (PRO_EMPTY_REF != ud)
        {
            char* string;
            pro_ud_read(s, ud, (const void**)&string);

            fprintf(stdout, "%s\n", string);
            pro_release(s, ud);
        }
        pro_release(s, arg);
    }
    
    fflush(stdout);
}


#pragma mark -
#pragma mark Internal

void pro_initialize_stdio(pro_state_ref s)
{
    // stdout actor
    pro_ref stdout_actor;
    pro_actor_create(s, PRO_DEFAULT_ACTOR_TYPE, stdio_behavior_impl,
        PRO_EMPTY_REF, &stdout_actor);
    pro_bind(s, stdout_actor, "stdout");
    
    pro_release(s, stdout_actor);
}



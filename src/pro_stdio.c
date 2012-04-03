#include "pro_stdio.h"

#include <stdio.h>


#pragma mark Private

static void stdio_behavior_impl(pro_state_ref s,
    pro_ref t, pro_ref msg, void* data)
{
    unsigned int msg_length;
    pro_message_length(s, msg, &msg_length);
    
    for (unsigned int i = 0; i < msg_length; ++i)
    {
        pro_ref arg;
        pro_message_get(s, msg, i, &arg);
        fprintf(stdout, "%s\n", pro_to_string(s, arg));
    }
    fflush(stdout);
}

#pragma mark -
#pragma mark Internal

void pro_initialize_stdio(pro_state_ref s)
{
    // stdout actor
    pro_ref stdout_actor = pro_actor_create(s, PRO_DEFAULT_ACTOR_TYPE);
    pro_behavior stdout_behavior = {
        .impl = stdio_behavior_impl,
        .data = 0
    };
    pro_become(s, stdout_actor, stdout_behavior);
    pro_bind(s, stdout_actor, "stdout");
}



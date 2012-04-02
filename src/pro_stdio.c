#include "pro_stdio.h"

#include <stdio.h>


#pragma mark Private

static void stdio_behavior_impl(pro_state* s,
    const pro_lookup* t, const pro_lookup* msg, void* data)
{
    for (unsigned int i = 0; i < pro_message_length(s, msg); ++i)
    {
        pro_lookup* arg = pro_message_get(s, msg, i);
        fprintf(stdout, "%s\n", pro_to_string(s, arg));
    }
    fflush(stdout);
}

#pragma mark -
#pragma mark Internal

void pro_initialize_stdio(pro_state* s)
{
    // stdout actor
    pro_lookup* stdout_actor = pro_actor_create(s, PRO_DEFAULT_ACTOR_TYPE);
    pro_behavior stdout_behavior = {
        .impl = stdio_behavior_impl,
        .data = 0
    };
    pro_become(s, stdout_actor, stdout_behavior);
    pro_bind(s, stdout_actor, "stdout");
}



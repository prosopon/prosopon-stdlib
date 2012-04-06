#include "pro_boolean.h"


static void boolean_behavior_impl(pro_state_ref s,
    pro_ref t, pro_ref msg, void* data)
{

}


#pragma mark -
#pragma mark Internal

void pro_initialize_boolean(pro_state_ref s)
{
    pro_ref true_actor, false_actor;
    pro_actor_create(s, PRO_DEFAULT_ACTOR_TYPE, &true_actor);
    pro_actor_create(s, PRO_DEFAULT_ACTOR_TYPE, &false_actor);

    pro_behavior boolean_behavior = {
        .impl = boolean_behavior_impl,
        .data = 0
    };
    pro_become(s, true_actor, boolean_behavior);
    pro_bind(s, true_actor, "true");
    
    pro_become(s, false_actor, boolean_behavior);
    pro_bind(s, false_actor, "false");
}



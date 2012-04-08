#include "pro_boolean.h"


static void boolean_behavior_impl(pro_state_ref s,
    pro_ref t, pro_ref msg, pro_ref data)
{

}


#pragma mark -
#pragma mark Internal

void pro_initialize_boolean(pro_state_ref s)
{
    pro_ref true_actor, false_actor;
    pro_actor_create(s, PRO_DEFAULT_ACTOR_TYPE,
        boolean_behavior_impl, PRO_EMPTY_REF, &true_actor);
    pro_actor_create(s, PRO_DEFAULT_ACTOR_TYPE,
        boolean_behavior_impl, PRO_EMPTY_REF, &false_actor);

    pro_bind(s, true_actor, "true");
    pro_bind(s, false_actor, "false");
}



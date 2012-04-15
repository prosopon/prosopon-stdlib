#include "pro_matching.h"


#pragma mark Private

static pro_matching match(pro_state_ref s, pro_ref t, pro_ref tData, pro_ref o)
{
    return PRO_MATCH_CONTINUE;
}



#pragma mark -
#pragma mark Internal

pro_actor_type pro_match_wildcard_actor_type = "match.wildcard";


const pro_actor_type_info pro_match_wildcard_type_info = {
    .match = match,
    .to_string = 0
};


#pragma mark -
#pragma mark Internal

PRO_INTERNAL void pro_initialize_matching(pro_state_ref s)
{
    pro_ref wildcard_actor;
    pro_actor_create(s, pro_match_wildcard_actor_type,
        0, PRO_EMPTY_REF, &wildcard_actor);
        
    pro_bind(s, wildcard_actor, "?*");
    
    pro_release(s, wildcard_actor);
}

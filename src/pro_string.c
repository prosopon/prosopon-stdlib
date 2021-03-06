#include "pro_string.h"

#include "prosopon_stdlib.h"
#include "prosopon_macros.h"

#include <stdlib.h>
#include <string.h>


#pragma mark Private

static void behavior_impl(pro_state_ref s,
    pro_ref t, pro_ref msg, pro_ref data)
{
}

static pro_matching match(pro_state_ref s,
    pro_ref t, pro_ref tData,
    pro_ref o, pro_ref oData)
{
    const char *s1, *s2;
    pro_ud_read(s, tData, (const void**)&s1);
    pro_ud_read(s, oData, (const void**)&s2);
    
    return strcmp(s1, s2) == 0 ? PRO_MATCH_SUCCEED : PRO_MATCH_FAIL;
}

static pro_ref to_string(pro_state_ref s,
    pro_ref t, pro_ref tData)
{
    pro_retain(s, tData);
    return tData;
}


#pragma mark -
#pragma mark Internal

pro_actor_type pro_string_actor_type = "string";

const pro_actor_type_info pro_string_type_info = {
    .match = match,
    .to_string = to_string
};


#pragma mark - 
#pragma mark Public

PRO_LIBCORE pro_ref pro_string_create(pro_state_ref s, const char* data)
{
    pro_ref actor;
    pro_ref ud = pro_string_ud_create(s, data);    
    pro_actor_create(s, pro_string_actor_type, behavior_impl, ud, &actor);
    pro_release(s, ud);

    return actor;
}

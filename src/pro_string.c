#include "pro_string.h"

#include "prosopon_stdlib.h"

#include <stdlib.h>
#include <string.h>


#pragma mark Private

static void behavior_impl(pro_state_ref s,
    pro_ref t, pro_ref msg, pro_ref data)
{
}

static pro_matching match(pro_state_ref s,
    pro_ref t, pro_ref tData,
    pro_ref o)
{
    const void* s1;
    const void* s2;
    
    pro_ref oData;
    pro_actor_request_ud(s, o, &oData);
    
    pro_ud_read(s, tData, &s1);
    pro_ud_read(s, oData, &s2);

    const char* string1 = s1;
    const char* string2 = s2;
    
    return strcmp(string1, string2) == 0 ? PRO_MATCH_SUCCEED : PRO_MATCH_FAIL;
}

static char* to_string(pro_state_ref s,
    pro_ref t, pro_ref tData)
{
    void* d;
    pro_ud_write(s, tData, &d);
    return d;
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
    pro_ref ud;
    pro_ud_create(s, sizeof(*data) * (strlen(data) + 1),
        PRO_DEFAULT_UD_DECONSTRUCTOR, &ud);
    
    void* ud_ptr;
    pro_ud_write(s, ud, &ud_ptr);
    strcpy(ud_ptr, data);
    
    pro_ref actor;
    pro_actor_create(s, pro_string_actor_type, behavior_impl, ud, &actor);
    pro_release(s, ud);

    return actor;
}

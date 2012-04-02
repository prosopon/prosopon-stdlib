#include "pro_string.h"

#include "prosopon_libcore.h"

#include <stdlib.h>
#include <string.h>


#pragma mark Private

static void behavior_impl(pro_state* s,
    const pro_lookup* t, const pro_lookup* msg, void* data)
{
}

static int match(pro_state* s,
    const pro_lookup* t, const void* tData,
    const pro_lookup* o, const void* oData)
{
    const char* string1 = tData;
    const char* string2 = oData;
    
    return strcmp(string1, string2) == 0 ? 1 : 0;
}

static const char* to_string(pro_state* s,
    const pro_lookup* t, const void* tData)
{
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

PRO_LIBCORE pro_lookup* pro_string_create(pro_state* s, const char* data)
{
    pro_lookup* actor = pro_actor_create(s, pro_string_actor_type);
    pro_behavior behavior = {
        .data = malloc(sizeof(*data) * (strlen(data) + 1)),
        .impl = behavior_impl
    };
    strcpy(behavior.data, data);
    pro_become(s, actor, behavior);
    return actor;
}

#include "pro_string.h"

#include "prosopon_libcore.h"


#pragma mark Private

static int match(pro_state* s,
    const pro_lookup* t, const void* tData,
    const pro_lookup* o, const void* oData)
{
    return 0;
}

#pragma mark Internal

pro_actor_type pro_string_actor_type = "string";

const pro_actor_type_info pro_string_type_info = {
    .match = match
};


#pragma mark - 
#pragma mark Public

PRO_LIBCORE pro_lookup* pro_string_create(pro_state* s, const char* data)
{
    return pro_actor_create(s, pro_string_actor_type);
}

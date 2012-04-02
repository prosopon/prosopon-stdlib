#include "pro_number.h"

#include "prosopon_libcore.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#pragma mark Private


static void behavior_impl(pro_state* s,
    const pro_lookup* t, const pro_lookup* msg, void* data)
{
    
}

static int match(pro_state* s,
    const pro_lookup* t, const void* tData, const pro_lookup* o, const void* oData)
{
    pro_type t_primitive_type = pro_get_type(s, t);
    assert(t_primitive_type == PRO_ACTOR_TYPE);
    pro_type o_primitive_type = pro_get_type(s, o);

    if (o_primitive_type != PRO_ACTOR_TYPE)
        return 0;
    
    const double* d1 = tData;
    const double* d2 = oData;
    return *d1 == *d2;
}

#pragma mark -
#pragma mark Internal

pro_actor_type pro_number_actor_type = "number";


const pro_actor_type_info pro_number_type_info = {
    .match = match
};


#pragma mark -
#pragma mark Public

PRO_LIBCORE pro_lookup* pro_number_create(pro_state* s, double data)
{
    pro_lookup* actor = pro_actor_create(s, pro_number_actor_type);
    pro_behavior behavior = {
        .data = malloc(sizeof(data)),
        .impl = behavior_impl
    };
    *((double*)behavior.data) = data;
    pro_become(s, actor, behavior);
    return actor;
}

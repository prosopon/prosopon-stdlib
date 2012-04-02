#include "pro_number.h"

#include "prosopon_libcore.h"
#include "pro_string.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>


#pragma mark Private

static void behavior_impl(pro_state* s,
    const pro_ref t, const pro_ref msg, void* data)
{
    unsigned int msg_length = pro_message_length(s, msg);
    if (msg_length < 1)
        return;
    
    pro_ref first = pro_message_get(s, msg, 0);
    
    if (strcmp(pro_string_actor_type, pro_get_actor_type(s, first)) == 0 )
    {
        if (pro_match(s, first, pro_string_create(s, "-")))
        {
            pro_ref val = pro_message_get(s, msg, 1);
            pro_ref cust = pro_message_get(s, msg, 2);
            
            const double* d1 = data;
            const double* d2 = pro_request_actor_data(s, val);
            
            pro_ref response = pro_message_create(s);
            pro_message_append(s, response, pro_number_create(s, *d1 - *d2));
            pro_send(s, cust, response);
        }
        else
        {
            pro_ref val = pro_message_get(s, msg, 1);
            pro_ref cust = pro_message_get(s, msg, 2);
            
            const double* d1 = data;
            const double* d2 = pro_request_actor_data(s, val);
            
            pro_ref response = pro_message_create(s);
            pro_message_append(s, response, pro_number_create(s, *d1 * *d2));
            pro_send(s, cust, response);
        }
    }
}

static int match(pro_state* s,
    const pro_ref t, const void* tData, const pro_ref o, const void* oData)
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

static const char* to_string(pro_state* s,
    const pro_ref t, const void* tData)
{
    const double* d = tData;
    char* buffer = malloc(sizeof(*buffer) * (32 + 1));
    snprintf(buffer, 32, "%g", *d);
    return buffer;
}


#pragma mark -
#pragma mark Internal

pro_actor_type pro_number_actor_type = "number";


const pro_actor_type_info pro_number_type_info = {
    .match = match,
    .to_string = to_string
};


#pragma mark -
#pragma mark Public

PRO_LIBCORE pro_ref pro_number_create(pro_state* s, double data)
{
    pro_ref actor = pro_actor_create(s, pro_number_actor_type);
    pro_behavior behavior = {
        .data = malloc(sizeof(data)),
        .impl = behavior_impl
    };
    *((double*)behavior.data) = data;
    pro_become(s, actor, behavior);
    return actor;
}

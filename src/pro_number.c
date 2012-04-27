#include "pro_number.h"

#include "pro_string.h"

#include <prosopon/prosopon_stdlib.h>
#include <prosopon/prosopon_macros.h>

#include <assert.h>
#include <string.h>
#include <stdio.h>


#pragma mark Private

typedef enum
{
    ADD_BINARY_OP,
    SUB_BINARY_OP,
    MUL_BINARY_OP,
    DIV_BINARY_OP
} BINARY_OP;

static void math(pro_state_ref s, pro_ref t, pro_ref data, pro_ref msg, BINARY_OP op)
{
    pro_ref val, cust;
    pro_list_get(s, msg, 1, &val);
    pro_list_get(s, msg, 2, &cust);

    pro_ref val_data;
    pro_actor_request_ud(s, val, &val_data);

    const double d1 = pro_ud_get_number_value(s, data);
    const double d2 = pro_ud_get_number_value(s, val_data);

    pro_ref result;
    switch (op)
    {
    case ADD_BINARY_OP: result = pro_number_create(s, d1 + d2); break;
    case SUB_BINARY_OP: result = pro_number_create(s, d1 - d2); break;
    case MUL_BINARY_OP: result = pro_number_create(s, d1 * d2); break;
    case DIV_BINARY_OP: result = pro_number_create(s, d1 / d2); break;
    }
    
    pro_ref response;
    pro_list_create(s, &response);
    pro_list_append_inplace(s, &response, result);
    pro_release(s, result);
    
    pro_release(s, val);
    
    pro_send(s, cust, response);
    pro_release(s, cust);
    pro_release(s, response);
}


static void behavior_impl(pro_state_ref s,
    pro_ref t, pro_ref msg, pro_ref data)
{
    unsigned int msg_length;
    pro_list_length(s, msg, &msg_length);
    switch (msg_length)
    {
    case 3:
    {
        pro_ref first;
        pro_list_get(s, msg, 0, &first);
        
        if (pro_match_string(s, first, "+"))
            math(s, t, data, msg, ADD_BINARY_OP);
        else if (pro_match_string(s, first, "-"))
            math(s, t, data, msg, SUB_BINARY_OP);
        else if (pro_match_string(s, first, "*"))
            math(s, t, data, msg, MUL_BINARY_OP);
        else if (pro_match_string(s, first, "/"))
            math(s, t, data, msg, DIV_BINARY_OP);
            
        pro_release(s, first);
    }   break;
    default:break;
    }
}

static pro_matching match(pro_state_ref s,
    pro_ref t, pro_ref tData, pro_ref o, pro_ref oData)
{
    pro_type t_primitive_type;
    pro_get_type(s, t, &t_primitive_type);
    assert(PRO_ACTOR_TYPE == t_primitive_type);
    
    pro_type o_primitive_type;
    pro_get_type(s, o, &o_primitive_type);

    if (o_primitive_type != PRO_ACTOR_TYPE)
        return 0;
    
    const double d1 = pro_ud_get_number_value(s, tData);
    const double d2 = pro_ud_get_number_value(s, oData);
    return d1 == d2 ? PRO_MATCH_SUCCEED : PRO_MATCH_FAIL;
}

static pro_ref to_string(pro_state_ref s,
    pro_ref t, pro_ref tData)
{
    const double* n;
    pro_ud_read(s, tData, (const void**)&n);
    
    char* buffer;
    pro_ref ud;
    pro_ud_create(s, sizeof(*buffer) * (32 + 1), PRO_DEFAULT_UD_DECONSTRUCTOR, &ud);
    
    pro_ud_write(s, ud, (void**)&buffer);
    snprintf(buffer, 32, "%g", *n);
    return ud;
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

PRO_LIBCORE pro_ref pro_number_create(pro_state_ref s, double data)
{
    pro_ref actor;

    pro_ref ud = pro_number_ud_create(s, data);
    pro_actor_create(s, pro_number_actor_type, behavior_impl, ud, &actor);
    pro_release(s, ud);
    
    return actor;
}

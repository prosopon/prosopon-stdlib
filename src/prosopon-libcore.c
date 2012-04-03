#include "prosopon.h"

#include "pro_string.h"
#include "pro_number.h"
#include "pro_stdio.h"


void prosopon_library_initialization(pro_state_ref s);


void prosopon_library_initialization(pro_state_ref s)
{
    pro_register_actor_type(s, pro_string_actor_type, &pro_string_type_info);
    pro_register_actor_type(s, pro_number_actor_type, &pro_number_type_info);
    
    pro_initialize_stdio(s);
}
#ifndef prosopon_core_prosopon_macros_h
#define prosopon_core_prosopon_macros_h

#include "prosopon.h"

/**
 * A collection of macros to ease performing common prosopon functions.
 */


#pragma mark -
#pragma mark User Data

PRO_LIBCORE pro_ref pro_number_ud_create(pro_state_ref, double val);

PRO_LIBCORE pro_ref pro_string_ud_create(pro_state_ref, const char* val);

PRO_LIBCORE double pro_ud_get_number_value(pro_state_ref, pro_ref ud);


#pragma mark -
#pragma mark List

PRO_LIBCORE void pro_list_append_inplace(pro_state_ref, pro_ref* msg, pro_ref val);


#pragma mark -
#pragma mark Behavior


PRO_LIBCORE pro_matching pro_match_string(pro_state_ref, pro_ref, const char*);

PRO_LIBCORE int pro_match_actor_type(pro_state_ref, pro_ref, pro_actor_type);
PRO_LIBCORE int pro_match_type(pro_state_ref, pro_ref, pro_type);


#endif

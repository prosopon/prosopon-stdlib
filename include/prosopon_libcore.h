#ifndef prosopon_prosopon_libcore_h
#define prosopon_prosopon_libcore_h

#include "prosopon.h"


#pragma mark String

/**
 * Creates a new string in the current environment
 */
PRO_LIBCORE pro_ref (pro_string_create) (pro_state_ref, const char* data);


#pragma mark Number

/**
 * Creates a new number in the current environment
 */
PRO_LIBCORE pro_ref (pro_number_create) (pro_state_ref, double data);


#pragma mark Boolean

/**
 * @return A reference to a boolean actor.
 */
PRO_LIBCORE pro_ref (pro_boolean_create) (pro_state_ref, int bool);


#endif

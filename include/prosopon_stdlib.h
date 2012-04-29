#ifndef prosopon_prosopon_libcore_h
#define prosopon_prosopon_libcore_h

#include <prosopon/prosopon.h>


#pragma mark Objects

/**
 * Creates a new string in the current environment
 */
PRO_LIBCORE pro_ref (pro_string_create) (pro_state_ref, const char* data);

/**
 * Creates a new number in the current environment
 */
PRO_LIBCORE pro_ref (pro_number_create) (pro_state_ref, double data);

/**
 * @return A new forwarding actor.
 */
PRO_LIBCORE pro_ref (pro_forward_create) (pro_state_ref, pro_ref);


/**
 * @return A new future.
 */
PRO_LIBCORE pro_ref (pro_future_create) (pro_state_ref);
PRO_LIBCORE void (pro_future_write) (pro_state_ref, pro_ref t, pro_ref val);




#endif

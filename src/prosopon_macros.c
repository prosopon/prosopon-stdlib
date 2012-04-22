#include "prosopon_macros.h"

#include "prosopon_stdlib.h"

#include <string.h>



PRO_LIBCORE pro_ref pro_number_ud_create(pro_state_ref s, double val)
{
    pro_ref ud;
    pro_ud_create(s, sizeof(val), PRO_DEFAULT_UD_DECONSTRUCTOR, &ud);
    
    double* number_val;
    pro_ud_write(s, ud, (void**)&number_val);
    *number_val = val;
    
    return ud;
}


PRO_LIBCORE pro_ref pro_string_ud_create(pro_state_ref s, const char* val)
{
    pro_ref ud;
    size_t size = val ? sizeof(*val) * (strlen(val) + 1) : 0;
    pro_ud_create(s, size, PRO_DEFAULT_UD_DECONSTRUCTOR, &ud);
    
    if (val)
    {
        void* ud_ptr;
        pro_ud_write(s, ud, &ud_ptr);
        strcpy(ud_ptr, val);
    }
    return ud;
}


PRO_LIBCORE double pro_ud_get_number_value(pro_state_ref s, pro_ref ud)
{
    const double *val;
    pro_ud_read(s, ud, (const void**)&val);
    return *val;
}


PRO_LIBCORE pro_matching pro_match_string(pro_state_ref s, pro_ref t, const char* str)
{
    pro_matching match;
    pro_ref match_str = pro_string_create(s, str);
    pro_match(s, t, match_str, &match);
    pro_release(s, match_str);
    return match;
}


PRO_LIBCORE int pro_match_type(pro_state_ref s, pro_ref t, pro_actor_type type)
{
    pro_actor_type actor_type;
    pro_get_actor_type(s, t, &actor_type);
    return strcmp(type, actor_type) == 0 ? 1 : 0;    
}

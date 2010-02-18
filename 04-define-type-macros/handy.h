#ifndef __HANDY_H__
#define __HANDY_H__

#include <glib.h>

/* a foreach loop on automatically created list of pointers  */
#define foreach(var, ...)                                       \
    void *G_PASTE(list, __LINE__)[] = {__VA_ARGS__, NULL};      \
    void **G_PASTE(p_list, __LINE__);                           \
    for (G_PASTE(p_list, __LINE__) = G_PASTE(list, __LINE__),   \
         var = *G_PASTE(p_list, __LINE__);                      \
         *G_PASTE(p_list, __LINE__);                            \
         G_PASTE(p_list, __LINE__)++,                           \
         var = *G_PASTE(p_list, __LINE__))

#endif


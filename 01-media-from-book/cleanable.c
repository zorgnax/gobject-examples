#include <glib-object.h>
#include "cleanable.h"

static guint cleanable_base_init_count = 0;

static void cleanable_base_init (CleanableClass *cls) {
    if (cleanable_base_init_count++) return;
    /* constructor code, for example, register signals  */
}

static void cleanable_base_finalize (CleanableClass *cls) {
    if (--cleanable_base_init_count) return;
    /* destructor code, for example, unregister signals  */
}

GType cleanable_get_type (void) {
    static GType type = 0;
    if (type) return type;
    static const GTypeInfo info = {
        sizeof (CleanableClass),
        (GBaseInitFunc)     cleanable_base_init,
        (GBaseFinalizeFunc) cleanable_base_finalize
    };
    type = g_type_register_static(G_TYPE_INTERFACE, "Cleanable", &info, 0);
    return type;
}

void clean (Cleanable *self) {
    g_return_if_fail(IS_CLEANABLE(self));
    g_object_ref(self);
    CLEANABLE_GET_CLASS(self)->clean(self);
    g_object_unref(self);
}


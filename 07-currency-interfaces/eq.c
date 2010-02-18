#include <glib-object.h>
#include "eq.h"
#include "comparable.h"

gboolean eq_not_equal_to (Eq *self, Eq *other) {
    return !eq_equal_to(self, other);
}

gboolean eq_equal_to (Eq *self, Eq *other) {
    return comparable_equal_to(COMPARABLE(self), COMPARABLE(other));
}

GType eq_get_type (void) {
    static GType type = 0;
    if (type) return type;
    static const GTypeInfo info = {sizeof (EqIface)};
    type = g_type_register_static(G_TYPE_INTERFACE, "Equal", &info, 0);
    g_type_interface_add_prerequisite(type, TYPE_COMPARABLE);
    return type;
}


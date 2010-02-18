#include <glib-object.h>
#include "comparable.h"

gboolean comparable_equal_to (Comparable *self, Comparable *other) {
    return comparable_compare(self, other) == 0;
}

gboolean comparable_greater_than (Comparable *self, Comparable *other) {
    return comparable_compare(self, other) == 1;
}

gboolean comparable_less_than (Comparable *self, Comparable *other) {
    return comparable_compare(self, other) == -1;
}

gboolean comparable_greater_than_or_equal_to (Comparable *self, Comparable *other) {
    return comparable_greater_than(self, other) || comparable_equal_to(self, other);
}

gboolean comparable_less_than_or_equal_to (Comparable *self, Comparable *other) {
    return comparable_less_than(self, other) || comparable_equal_to(self, other);
}

gint comparable_compare (Comparable *self, Comparable *other) {
    COMPARABLE_GET_IFACE(self)->compare(self, other);
}

gint comparable_compare_real (Comparable *self, Comparable *other) {
    /* default to comparing pointers  */
    return self < other ? -1 : self == other ? 0 : 1;
}

static void comparable_iface_init (ComparableIface *iface) {
    iface->compare = comparable_compare_real;
}

GType comparable_get_type (void) {
    static GType type = 0;
    if (type) return type;
    
    static const GTypeInfo info = {
        sizeof (ComparableIface),
        NULL,
        NULL,
        (GClassInitFunc) comparable_iface_init
    };
    
    type = g_type_register_static(
        G_TYPE_INTERFACE,
        "Comparable",
        &info,
        0);
    
    return type;
}


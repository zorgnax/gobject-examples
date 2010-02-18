#ifndef __COMPARABLE_H__
#define __COMPARABLE_H__

#include <glib-object.h>

typedef struct _Comparable      Comparable;
typedef struct _ComparableIface ComparableIface;

struct _ComparableIface {
    GTypeInterface parent;
    gint (*compare) (Comparable *self, Comparable *other);
};

#define TYPE_COMPARABLE           (comparable_get_type())
#define COMPARABLE(obj)           (G_TYPE_CHECK_INSTANCE_CAST    ((obj), TYPE_COMPARABLE, Comparable))
#define IS_COMPARABLE(obj)        (G_TYPE_CHECK_INSTANCE_TYPE    ((obj), TYPE_COMPARABLE))
#define COMPARABLE_GET_IFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), TYPE_COMPARABLE, ComparableIface))

GType    comparable_get_type                 (void);
gint     comparable_compare                  (Comparable *self, Comparable *other);
gboolean comparable_equal_to                 (Comparable *self, Comparable *other);
gboolean comparable_greater_than             (Comparable *self, Comparable *other);
gboolean comparable_less_than                (Comparable *self, Comparable *other);
gboolean comparable_greater_than_or_equal_to (Comparable *self, Comparable *other);
gboolean comparable_less_than_or_equal_to    (Comparable *self, Comparable *other);

#endif


#ifndef __EQ_H__
#define __EQ_H__

#include <glib-object.h>

typedef struct _Eq      Eq;
typedef struct _EqIface EqIface;

struct _EqIface {
    GTypeInterface parent;
};

#define TYPE_EQ           (eq_get_type())
#define EQ(obj)           (G_TYPE_CHECK_INSTANCE_CAST    ((obj), TYPE_EQ, Eq))
#define IS_EQ(obj)        (G_TYPE_CHECK_INSTANCE_TYPE    ((obj), TYPE_EQ))
#define EQ_GET_IFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), TYPE_EQ, EqIface))

GType    eq_get_type     (void);
gboolean eq_equal_to     (Eq *self, Eq *other);
gboolean eq_not_equal_to (Eq *self, Eq *other);

#endif


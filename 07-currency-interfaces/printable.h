#ifndef __PRINTABLE_H__
#define __PRINTABLE_H__

#include <glib-object.h>

typedef struct _Printable      Printable;
typedef struct _PrintableIface PrintableIface;

struct _PrintableIface {
    GTypeInterface parent;
    gchar* (*to_string) (Printable *self);
};

#define TYPE_PRINTABLE           (printable_get_type())
#define PRINTABLE(obj)           (G_TYPE_CHECK_INSTANCE_CAST    ((obj), TYPE_PRINTABLE, Printable))
#define IS_PRINTABLE(obj)        (G_TYPE_CHECK_INSTANCE_TYPE    ((obj), TYPE_PRINTABLE))
#define PRINTABLE_GET_IFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), TYPE_PRINTABLE, PrintableIface))

GType  printable_get_type  (void);
gchar *printable_to_string (Printable *self);
void   printable_print     (Printable *self);

#endif


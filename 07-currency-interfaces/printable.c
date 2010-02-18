#include <glib-object.h>
#include "printable.h"

void printable_print (Printable *self) {
    gchar *str = printable_to_string(self);
    g_print("%s\n", str);
    g_free(str);
}

gchar *printable_to_string (Printable *self) {
    return PRINTABLE_GET_IFACE(self)->to_string(self);
}

/* a cautious default  */
gchar *printable_to_string_real (Printable *self) {
    return g_strdup("printable object to string");
}

static void printable_iface_init (PrintableIface *iface) {
    iface->to_string = printable_to_string_real;
}

GType printable_get_type (void) {
    static GType type = 0;
    if (type) return type;
    
    static const GTypeInfo info = {
        sizeof (PrintableIface),
        NULL,
        NULL,
        (GClassInitFunc) printable_iface_init
    };
    
    type = g_type_register_static(
        G_TYPE_INTERFACE,
        "Printable",
        &info,
        0);

    return type;
}


/*
A smaller example like point with inheritance. This time everything is in
one file and I use G_DEFINE_TYPE. I try to be concise.
*/

#include <glib-object.h>
#include "handy.h"

typedef struct {
    GObject parent;
    gint x, y;
} Dot;

typedef struct {
    GObjectClass parent;
    void (*print) (gpointer self);
} DotClass;

#define TYPE_DOT           (dot_get_type               ())
#define DOT(obj)           (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_DOT, Dot))
#define DOT_CLASS(cls)     (G_TYPE_CHECK_CLASS_CAST    ((cls), TYPE_DOT, DotClass))
#define DOT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS  ((obj), TYPE_DOT, DotClass))

G_DEFINE_TYPE(Dot, dot, G_TYPE_OBJECT);

gpointer    dot_new        (gint x, gint y) {Dot *d = g_object_new(TYPE_DOT, NULL); d->x = x; d->y = y; return d;}
void        dot_print      (gpointer self)  {DOT_GET_CLASS(self)->print(self);}
static void dot_print_real (gpointer self)  {g_print("dot at (%d, %d)\n", DOT(self)->x, DOT(self)->y);}
static void dot_class_init (DotClass *cls)  {cls->print = dot_print_real;}
static void dot_init       (Dot *self)      {}

typedef struct {
    Dot parent;
    gint z;
} Dot3D;

typedef struct {
    DotClass parent;
} Dot3DClass;

#define TYPE_DOT3D (dot3d_get_type())
#define DOT3D(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_DOT3D, Dot3D))

G_DEFINE_TYPE(Dot3D, dot3d, TYPE_DOT);

gpointer    dot3d_new        (gint x, gint y, gint z) {Dot3D *d = g_object_new(TYPE_DOT3D, NULL); DOT(d)->x = x; DOT(d)->y = y; d->z = z; return d;}
void        dot3d_print      (gpointer self)          {g_print("dot at (%d, %d, %d)\n", DOT(self)->x, DOT(self)->y, DOT3D(self)->z);}
static void dot3d_class_init (Dot3DClass *cls)        {DOT_CLASS(cls)->print = dot3d_print;}
static void dot3d_init       (Dot3D *self)            {}

int main () {
    Dot *d;

    g_type_init();
    foreach (d,
             dot_new(1, 1),
             dot_new(2, 3),
             dot_new(5, 8),
             dot3d_new(13, 21, 34),
             dot3d_new(55, 89, 144),
             dot_new(233, 377)) {
        dot_print(d);
        g_object_unref(d);
    }

    return 0;
}


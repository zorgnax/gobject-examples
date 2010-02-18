/*
Media class example
From chapter 2 of The Official GNOME 2 Developer's Guide
*/

#include <glib-object.h>
#include "cleanable.h"

#define TYPE_MEDIA           (media_get_type())
#define MEDIA(obj)           (G_TYPE_CHECK_INSTANCE_CAST((obj), TYPE_MEDIA, Media))
#define MEDIA_CLASS(cls)     (G_TYPE_CHECK_CLASS_CAST((cls), TYPE_MEDIA, MediaClass))
#define IS_MEDIA(obj)        (G_TYPE_CHECK_INSTANCE_TYPE((obj), TYPE_MEDIA))
#define IS_MEDIA_CLASS(cls)  (G_TYPE_CHECK_CLASS_TYPE((cls), TYPE_MEDIA))
#define MEDIA_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS((obj), TYPE_MEDIA, MediaClass))

GType media_get_type (void);

typedef struct _MediaClass MediaClass;
typedef struct _Media Media;

struct _MediaClass {
  GObjectClass parent_class;
  void (*unpacked)  (Media *media);
  void (*throw_out) (Media *media, gboolean permanent);
};

struct _Media {
  GObject parent_instance;
  guint inv_nr;
  GString *location;
  GString *title;
  gboolean orig_package;
};

enum {
  PROP_INV_NR = 1,
  PROP_ORIG_PACKAGE
};

static void media_set_property (
  GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec) {
  Media *media = MEDIA(object);

  switch (prop_id) {
  case PROP_INV_NR: {
    guint new_inv_nr = g_value_get_uint(value);
    media->inv_nr = new_inv_nr;
    break;
  }
  
  case PROP_ORIG_PACKAGE: {
    gboolean new_orig_package = g_value_get_boolean(value);
    media->orig_package = new_orig_package;
    break;
  }
    
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void media_get_property (
    GObject *object, guint prop_id, GValue *value, GParamSpec *pspec) {
  Media *media = MEDIA(object);

  switch (prop_id) {
  case PROP_INV_NR:
    g_value_set_uint(value, media->inv_nr);
    break;
  
  case PROP_ORIG_PACKAGE:
    g_value_set_boolean(value, media->orig_package);
    break;
    
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void media_unpacked (Media *media) {
  if (media->orig_package) {
    g_object_set(media, "orig-package", FALSE, NULL);
    g_print("Media unpacked.\n");
  }
  else {
    g_print("Media already unpacked.\n");
  }
}

static void media_throw_out (Media *media, gboolean permanent) {
  if (permanent)
    g_print("Trashing media.\n");
  else
    g_print("Media not in the dumpster quite yet.\n");
}

enum {
  UNPACKED,
  THROW_OUT,
  LAST_SIGNAL
};

static guint media_signal[LAST_SIGNAL] = {0, 0};

static void media_class_init (MediaClass *cls) {
  GParamSpec *inv_nr_param;
  GParamSpec *orig_package_param;
  GObjectClass *g_object_class;

  g_object_class = G_OBJECT_CLASS(cls);
  g_object_class->get_property = media_get_property;
  g_object_class->set_property = media_set_property;
  
  inv_nr_param = g_param_spec_uint(
    "inventory-id",
    "inventory number",
    "number on inventory label",
    0, /* => */ UINT_MAX,
    0,
    G_PARAM_READWRITE);

  orig_package_param = g_param_spec_boolean(
    "orig-package",
    "original package?",
    "is item in its original package?",
    FALSE,
    G_PARAM_READWRITE);

  g_object_class_install_property(
    g_object_class,
    PROP_INV_NR,
    inv_nr_param);

  g_object_class_install_property(
    g_object_class,
    PROP_ORIG_PACKAGE,
    orig_package_param);

  cls->unpacked = media_unpacked;
  cls->throw_out = media_throw_out;

  media_signal[UNPACKED] = g_signal_new(
    "unpacked",                            /* name */
    TYPE_MEDIA,                            /* class type identifier */
    G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED, /* options */
    G_STRUCT_OFFSET(MediaClass, unpacked), /* handler offset */
    NULL,                                  /* accumulator function */
    NULL,                                  /* accumulator data */
    g_cclosure_marshal_VOID__VOID,         /* marshaller */
    G_TYPE_NONE,                           /* type of return value */
    0);

  media_signal[THROW_OUT] = g_signal_new(
    "throw_out",
    TYPE_MEDIA,
    G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED,
    G_STRUCT_OFFSET(MediaClass, throw_out),
    NULL,
    NULL,
    g_cclosure_marshal_VOID__BOOLEAN,
    G_TYPE_NONE,
    1,
    G_TYPE_BOOLEAN);
}

static void media_clean (Cleanable *self) {
    g_print("cleaning media.\n");
}

static void media_cleanable_init (gpointer interface, gpointer data) {
    CleanableClass *cls = interface;
    cls->clean = media_clean;
}

GType media_get_type (void) {
    static GType type = 0;
    if (type) return type;

    static const GTypeInfo media_info = {
        sizeof (MediaClass),                /* class structure size */
        NULL,                               /* base class initializer */
        NULL,                               /* base class finalizer */
        (GClassInitFunc) media_class_init,  /* class initializer */
        NULL,                               /* class finalizer */
        NULL,                               /* class data */
        sizeof (Media),                     /* instance struct size */
        0,                                  /* preallocated instances */
        NULL,                               /* instance initializer */
        NULL                                /* function table */
    };

    type = g_type_register_static(
        G_TYPE_OBJECT, /* parent class */
        "Media",       /* type name */
        &media_info,   /* GtypeInfo struct */
        0);            /* flags */

    const GInterfaceInfo cleanable_info = {media_cleanable_init, NULL, NULL};
    
    g_type_add_interface_static(type, TYPE_CLEANABLE, &cleanable_info);

    return type;
}

void media_print_inv_nr (Media *object) {
  Media *media;
  g_return_if_fail(IS_MEDIA(object));
  media = MEDIA(object);

  g_print("Inventory number: %d\n", media->inv_nr);
}

static void meep_meep (Media *media) {
  guint nr;
  g_object_get(media, "inventory-id", &nr, NULL);
  g_print("Meep-meep! (Inventory number: %d)\n", nr);
}

int main () {
    Media *media;
    guint nr;
    gboolean is_unpacked;
    gulong handler_id;

    g_type_init();
    g_print("Hello World!\n");
    media = g_object_new(TYPE_MEDIA,
                         "inventory-id", 42,
                         "orig-package", FALSE,
                         NULL);

    handler_id = g_signal_connect(
        media,
        "unpacked",
        (GCallback) meep_meep,
        NULL);

    g_signal_emit_by_name(media, "unpacked");

    g_print("Setting inventory-id = 37, orig-package = TRUE\n");
    g_object_set(media,
                 "inventory-id", 37,
                 "orig-package", TRUE,
                 NULL);

    g_print("Verifying.. ");
    g_object_get(media,
                 "inventory-id", &nr,
                 "orig-package", &is_unpacked,
                 NULL);
    g_print("inventory-id = %d, orig-package = %s\n",
            nr, is_unpacked ? "TRUE" : "FALSE");

    g_signal_emit_by_name(media, "unpacked");
    g_signal_emit_by_name(media, "unpacked");
    g_signal_emit_by_name(media, "throw-out", TRUE);

    clean(CLEANABLE(media));

    return 0;
}


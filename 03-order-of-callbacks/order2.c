#include <glib-object.h>
#include "order2.h"
#include "order.h"

enum {
    PROP_0,
    PROP_Z
};

static void point3d_print (Point *self) {
    gint x, y, z;
    g_object_get(self, "x", &x, "y", &y, "z", &z, NULL);
    g_print("x: %d, y: %d, z: %d\n", x, y, z);
}

static void point3d_clear (Point *self) {
    g_object_set(self, "x", 0, "y", 0, "z", 0, NULL);
}

static void point3d_get_property (GObject    *obj,
                                  guint       prop_id,
                                  GValue     *value,
                                  GParamSpec *pspec) {
    Point3D *point3d = POINT3D(obj);

    g_print("point3d_get_property(obj=%p, %s)\n",
        obj, g_param_spec_get_name(pspec));

    switch (prop_id) {
    case PROP_Z:
        g_value_set_int(value, point3d->z);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(obj, prop_id, pspec);
        break;
    }
}

static void point3d_set_property (GObject      *obj,
                                  guint         prop_id,
                                  const GValue *value,
                                  GParamSpec   *pspec) {
    Point3D *point3d = POINT3D(obj);

    {
        gchar *contents = g_strdup_value_contents(value);
        g_print("point3d_set_property(obj=%p, %s => %s)\n",
            obj, g_param_spec_get_name(pspec), contents);
        g_free(contents);
    }
    
    switch (prop_id) {
    case PROP_Z: {
        gint new_z = g_value_get_int(value);
        point3d->z = new_z;
        break;
    }
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(obj, prop_id, pspec);
        break;
    }
}

static GObject *point3d_constructor (GType                  type,
                                     guint                  n_construct_properties,
                                     GObjectConstructParam *construct_properties) {
    GObject *obj;
    PointClass *parent_class = g_type_class_peek(TYPE_POINT);
    
    obj = G_OBJECT_CLASS(parent_class)->constructor(type,
                                        n_construct_properties,
                                        construct_properties);

    {
        int i;
        g_print("point3d_constructor(type=%s", g_type_name(type));
        for (i = 0; i < n_construct_properties; i++) {
            GParamSpec *pspec = construct_properties[i].pspec;
            GValue *value = construct_properties[i].value;
            gchar *contents = g_strdup_value_contents(value);
            g_print(", %s => %s", g_param_spec_get_name(pspec), contents);
            g_free(contents);
        }
        g_print(")\n");
    }
    
    return obj;
}

static void point3d_dispose (GObject *obj) {
    PointClass *parent_class = g_type_class_peek(TYPE_POINT);
    
    g_print("point3d_dispose(obj=%p)\n", obj);
    
    G_OBJECT_CLASS(parent_class)->dispose(obj);
}

static void point3d_finalize (GObject *obj) {
    PointClass *parent_class = g_type_class_peek(TYPE_POINT);
    
    g_print("point3d_finalize(obj=%p)\n", obj);
    
    G_OBJECT_CLASS(parent_class)->finalize(obj);
}

static void point3d_base_init (Point3DClass *cls) {
    g_print("point3d_base_init(cls=%p)\n", cls);
}

static void point3d_base_finalize (Point3DClass *cls) {
    g_print("point3d_base_finalize(cls=%p)\n", cls);
}

static void point3d_class_init (Point3DClass *cls) {
    GObjectClass *g_object_class = G_OBJECT_CLASS(cls);
    PointClass *point_class = POINT_CLASS(cls);
    GParamSpec *z_param;
    
    g_print("point3d_class_init(cls=%p)\n", cls);
    
    g_object_class->constructor = point3d_constructor;
    g_object_class->dispose = point3d_dispose;
    g_object_class->finalize = point3d_finalize;
    g_object_class->get_property = point3d_get_property;
    g_object_class->set_property = point3d_set_property;
    
    point_class->clear = point3d_clear;
    point_class->print = point3d_print;
    
    z_param = g_param_spec_int(
        "z", "z", "z loc of point",
        INT_MIN, /* => */ INT_MAX,
        0,
        G_PARAM_READWRITE);

    g_object_class_install_property(
        g_object_class,
        PROP_Z,
        z_param);
}

static void point3d_init (Point3D *obj, Point3DClass *cls) {
    g_print("point3d_init(obj=%p, cls=%p)\n", obj, cls);
}

GType point3d_get_type (void) {
    static GType point3d_type = 0;

    if (!point3d_type) {
        static const GTypeInfo point3d_info = {
            sizeof (Point3DClass),                     /* class_size */
            (GBaseInitFunc) point3d_base_init,         /* base_init */
            (GBaseFinalizeFunc) point3d_base_finalize, /* base_finalize */
            (GClassInitFunc) point3d_class_init,       /* class_init */
            NULL,                                      /* class_finalize */
            NULL,                                      /* class_data */
            sizeof (Point3D),                          /* instance_size */
            0,                                         /* n_preallocs */
            (GInstanceInitFunc) point3d_init,          /* instance_init */
            NULL                                       /* value_table */
        };

        point3d_type = g_type_register_static(
            TYPE_POINT,     /* parent_type */
            "Point3D",      /* type_name */
            &point3d_info,  /* info */
            0);             /* flags */
    }

    return point3d_type;
}


#include <glib-object.h>
#include "point3d.h"
#include "point.h"

enum {
    PROP_0,
    PROP_Z
};

static void point3d_print (Point *self) {
    g_print("x: %d, y: %d, z: %d\n", self->x, self->y, POINT3D(self)->z);
}

static void point3d_clear (Point *self) {
    g_object_set(self, "x", 0, "y", 0, "z", 0, NULL);
}

static void point3d_get_property (GObject    *obj,
                                  guint       prop_id,
                                  GValue     *value,
                                  GParamSpec *pspec) {
    Point3D *point3d = POINT3D(obj);

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

static void point3d_class_init (Point3DClass *cls) {
    GObjectClass *g_object_class = G_OBJECT_CLASS(cls);
    PointClass *point_class = POINT_CLASS(cls);
    GParamSpec *z_param;
    
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

GType point3d_get_type (void) {
    static GType point3d_type = 0;

    if (!point3d_type) {
        static const GTypeInfo point3d_info = {
            sizeof (Point3DClass),               /* class_size */
            NULL,                                /* base_init */
            NULL,                                /* base_finalize */
            (GClassInitFunc) point3d_class_init, /* class_init */
            NULL,                                /* class_finalize */
            NULL,                                /* class_data */
            sizeof (Point3D),                    /* instance_size */
            0,                                   /* n_preallocs */
            NULL,                                /* instance_init */
            NULL                                 /* value_table */
        };

        point3d_type = g_type_register_static(
            TYPE_POINT,     /* parent_type */
            "Point3D",      /* type_name */
            &point3d_info,  /* info */
            0);             /* flags */
    }

    return point3d_type;
}


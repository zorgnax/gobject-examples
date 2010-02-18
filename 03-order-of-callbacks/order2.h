#ifndef __ORDER2_H__
#define __ORDER2_H__

#include <glib-object.h>
#include "order.h"

typedef struct _Point3DClass Point3DClass;
typedef struct _Point3D      Point3D;

struct _Point3DClass {
    PointClass parent;
};

struct _Point3D {
    Point parent;
    gint z;
};

#define TYPE_POINT3D           (point3d_get_type           ())
#define POINT3D(obj)           (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_POINT3D, Point3D))
#define POINT3D_CLASS(cls)     (G_TYPE_CHECK_CLASS_CAST    ((cls), TYPE_POINT3D, Point3DClass))
#define IS_POINT3D(obj)        (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_POINT3D))
#define IS_POINT3D_CLASS(cls)  (G_TYPE_CHECK_CLASS_TYPE    ((cls), TYPE_POINT3D))
#define POINT3D_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS  ((obj), TYPE_POINT3D, Point3DClass))

GType point3d_get_type (void);

#endif

/* In this example, most of the GType callbacks (init, class_init, base_init, 
base_finalize) and the GObject callbacks (get_property, set_property, 
constructor, dispose, finalize) have a been given a print statement to show 
when they're called and with what data. when objects are created and 
unreferenced.  */

#include <glib-object.h>
#include "order.h"
#include "order2.h"

int main () {
    g_type_init();
    
    g_print("\npoint 1\n=======\n");
    Point *o = g_object_new(TYPE_POINT, "x", 302, "y", 20, NULL);
    point_print(o);
    g_object_unref(o);
    
    g_print("\npoint 2\n=======\n");
    o = g_object_new(TYPE_POINT, "x", 37071092, "y", 5, NULL);
    point_print(o);
    g_object_unref(o);
    
    g_print("\npoint3d 1\n=========\n");
    o = g_object_new(TYPE_POINT3D, "x", 302, "y", 20, "z", 77, NULL);
    point_print(o);
    g_object_unref(o);
    
    g_print("\npoint3d 2\n=========\n");
    o = g_object_new(TYPE_POINT3D, "x", 1, "y", 2, NULL);
    point_print(o);
    g_object_unref(o);
    
    g_print("\npoint class ref\n===============\n");
    /* none of the callbacks I'm interested in get called here */
    PointClass *c = g_type_class_ref(TYPE_POINT3D);
    g_type_class_unref(c);
    /* g_type_class_unref(c);   base_finalize only occurs for plugins, in
                                normal code, you just get a warning when you
                                unreference a type too many times.  */
    
    g_print("\ndone!\n");

    return 0;
}

/* outputs:

point 1
=======
point_base_init(cls=0x8a9f1f0)
point_class_init(cls=0x8a9f1f0)
point_init(obj=0x8a9e918, cls=0x8a9f1f0)
point_constructor(type=Point)
point_set_property(obj=0x8a9e918, x => 302)
point_set_property(obj=0x8a9e918, y => 20)
x: 302, y: 20
point_dispose(obj=0x8a9e918)
point_finalize(obj=0x8a9e918)

point 2
=======
point_init(obj=0x8a9e930, cls=0x8a9f1f0)
point_constructor(type=Point)
point_set_property(obj=0x8a9e930, x => 37071092)
point_set_property(obj=0x8a9e930, y => 5)
x: 37071092, y: 5
point_dispose(obj=0x8a9e930)
point_finalize(obj=0x8a9e930)

point3d 1
=========
point_base_init(cls=0x8a9fcc8)
point3d_base_init(cls=0x8a9fcc8)
point3d_class_init(cls=0x8a9fcc8)
point_init(obj=0x8a9e948, cls=0x8a9fcc8)
point3d_init(obj=0x8a9e948, cls=0x8a9fcc8)
point_constructor(type=Point3D)
point3d_constructor(type=Point3D)
point_set_property(obj=0x8a9e948, x => 302)
point_set_property(obj=0x8a9e948, y => 20)
point3d_set_property(obj=0x8a9e948, z => 77)
x: 302, y: 20, z: 77
point3d_dispose(obj=0x8a9e948)
point_dispose(obj=0x8a9e948)
point3d_finalize(obj=0x8a9e948)
point_finalize(obj=0x8a9e948)

point3d 2
=========
point_init(obj=0x8a9e960, cls=0x8a9fcc8)
point3d_init(obj=0x8a9e960, cls=0x8a9fcc8)
point_constructor(type=Point3D)
point3d_constructor(type=Point3D)
point_set_property(obj=0x8a9e960, x => 1)
point_set_property(obj=0x8a9e960, y => 2)
point3d_set_property(obj=0x8a9e960, z => 3)
x: 1, y: 2, z: 3
point3d_dispose(obj=0x8a9e960)
point_dispose(obj=0x8a9e960)
point3d_finalize(obj=0x8a9e960)
point_finalize(obj=0x8a9e960)

point class ref
===============

done!
*/

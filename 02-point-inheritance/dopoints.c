/* Creates a Point class, then inherits from that with Point3D. Also shows a
polymorphic method call, point_print()  */

#include <stdio.h>
#include "point.h"
#include "point3d.h"

/* print signal print  */
static void psp (Point *p) {
    point_print(p);
    g_signal_emit_by_name(p, "clear");
    point_print(p);
    g_print("...\n");
}

int main () {
    g_type_init();
    
    void *points[] = {
        g_object_new(TYPE_POINT,   "x",  5, "y", 10, NULL),
        g_object_new(TYPE_POINT,   "x",  2, "y", -3, NULL),
        g_object_new(TYPE_POINT3D, "x", -7, "y",  4, "z", 9,  NULL),
        g_object_new(TYPE_POINT3D, "x",  8, "y",  7, "z", 32, NULL),
        NULL
    };

    void **p;
    Point *a;
    for (p = points, a = *p; *p; p++, a = *p)
        psp(a);

    return 0;
}


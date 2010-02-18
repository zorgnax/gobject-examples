#ifndef __CLEANABLE_H__
#define __CLEANABLE_H__

#include <glib-object.h>

typedef struct _Cleanable      Cleanable;
typedef struct _CleanableClass CleanableClass;

struct _CleanableClass {
    GTypeInterface parent;
    void (*clean) (Cleanable *obj);
};

#define TYPE_CLEANABLE           (cleanable_get_type())
#define CLEANABLE(obj)           (G_TYPE_CHECK_INSTANCE_CAST((obj), TYPE_CLEANABLE, Cleanable))
#define IS_CLEANABLE(obj)        (G_TYPE_CHECK_INSTANCE_TYPE((obj), TYPE_CLEANABLE))
#define CLEANABLE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_INTERFACE((obj), TYPE_CLEANABLE, CleanableClass))

GType cleanable_get_type (void);
void  clean              (Cleanable *self);

#endif


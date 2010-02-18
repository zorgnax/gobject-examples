#ifndef __BINARYTREE_H__
#define __BINARYTREE_H__

#include <glib-object.h>

typedef struct _BinaryTree      BinaryTree;
typedef struct _BinaryTreeClass BinaryTreeClass;

struct _BinaryTree {
    GObject     parent_instance;
    gpointer    data;
    BinaryTree *parent;
    BinaryTree *left;
    BinaryTree *right;
};

struct _BinaryTreeClass {
    GObjectClass parent_class;
};

#define TYPE_BINARY_TREE           (binary_tree_get_type())
#define BINARY_TREE(obj)           (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_BINARY_TREE, BinaryTree))
#define BINARY_TREE_CLASS(cls)     (G_TYPE_CHECK_CLASS_CAST    ((cls), TYPE_BINARY_TREE, BinaryTreeClass))
#define IS_BINARY_TREE(obj)        (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_BINARY_TREE))
#define IS_BINARY_TREE_CLASS(cls)  (G_TYPE_CHECK_CLASS_TYPE    ((cls), TYPE_BINARY_TREE))
#define BINARY_TREE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS  ((obj), TYPE_BINARY_TREE, BinaryTreeClass))
#define binary_tree_new(...)       (g_object_new(TYPE_BINARY_TREE, ## __VA_ARGS__, NULL))

GType       binary_tree_get_type   (void);
gboolean    binary_tree_has_parent (BinaryTree *self);
gboolean    binary_tree_has_left   (BinaryTree *self);
gboolean    binary_tree_has_right  (BinaryTree *self);
BinaryTree *binary_tree_get_parent (BinaryTree *self);
BinaryTree *binary_tree_get_left   (BinaryTree *self);
BinaryTree *binary_tree_get_right  (BinaryTree *self);
gpointer    binary_tree_get_data   (BinaryTree *self);
void        binary_tree_set_data   (BinaryTree *self, gpointer data);
void        binary_tree_set_left   (BinaryTree *self, BinaryTree *child);
void        binary_tree_set_right  (BinaryTree *self, BinaryTree *child);
void        binary_tree_print      (BinaryTree *self);

#endif


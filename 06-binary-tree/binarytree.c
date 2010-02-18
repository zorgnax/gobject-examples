#include <glib-object.h>
#include "binarytree.h"

enum {
    PROP_0,
    PROP_DATA,
    PROP_PARENT,
    PROP_LEFT,
    PROP_RIGHT,
    PROP_HAS_PARENT,
    PROP_HAS_LEFT,
    PROP_HAS_RIGHT
};

G_DEFINE_TYPE(BinaryTree, binary_tree, G_TYPE_OBJECT);

void binary_tree_print (BinaryTree *self) {
    BinaryTree *b;
    guint depth = -1;
    
    if (!self) return;
    
    for (b = self; b; b = b->parent)
        depth++;
    
    g_print("%*s%s\n", depth * 4, "", (char *) self->data);
    
    binary_tree_print(self->left);
    binary_tree_print(self->right);
}

gboolean binary_tree_has_parent (BinaryTree *self) {
    return self->parent ? TRUE : FALSE;
}

gboolean binary_tree_has_left (BinaryTree *self) {
    return self->left ? TRUE : FALSE;
}

gboolean binary_tree_has_right (BinaryTree *self) {
    return self->right ? TRUE : FALSE;
}

/* returns the parent of the binary tree node. user does not have to 
unref it when done.  */
BinaryTree *binary_tree_get_parent (BinaryTree *self) {
    return self->parent;
}

/* returns the left child of the binary tree node. user does not have to 
unref it when done.  */
BinaryTree *binary_tree_get_left (BinaryTree *self) {
    if (!self->left)
        self->left = binary_tree_new("parent", self);
    return self->left;
}

/* returns the left child of the binary tree node. user does not have to 
unref it when done.  */
BinaryTree *binary_tree_get_right (BinaryTree *self) {
    if (!self->right)
        self->right = binary_tree_new("parent", self);
    return self->right;
}

gpointer binary_tree_get_data (BinaryTree *self) {
    return self->data;
}

void binary_tree_set_data (BinaryTree *self, gpointer data) {
    self->data = data;
}

void binary_tree_set_left (BinaryTree *self, BinaryTree *child) {
    if (binary_tree_has_parent(child))
        g_error("You cannot insert a tree which already has a parent");
    child->parent = self;
    self->left = child;
}

void binary_tree_set_right (BinaryTree *self, BinaryTree *child) {
    if (binary_tree_has_parent(child))
        g_error("You cannot insert a tree which already has a parent");
    child->parent = self;
    self->right = child;
}

static void binary_tree_get_property (GObject    *obj,
                                      guint       prop_id,
                                      GValue     *value,
                                      GParamSpec *pspec) {
    BinaryTree *self = BINARY_TREE(obj);
    
    switch (prop_id) {
    case PROP_DATA:
        g_value_set_pointer(value, binary_tree_get_data(self));
        break;

    case PROP_PARENT:
        g_value_take_object(value, binary_tree_get_parent(self));
        break;

    case PROP_LEFT:
        g_value_take_object(value, binary_tree_get_left(self));
        break;

    case PROP_RIGHT:
        g_value_take_object(value, binary_tree_get_right(self));
        break;
    
    case PROP_HAS_PARENT:
        g_value_set_boolean(value, binary_tree_has_parent(self));
        break;

    case PROP_HAS_LEFT:
        g_value_set_boolean(value, binary_tree_has_left(self));
        break;
        
    case PROP_HAS_RIGHT:
        g_value_set_boolean(value, binary_tree_has_right(self));
        break;
    
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(obj, prop_id, pspec);
        break;
    }
}

static void binary_tree_set_property (GObject      *obj,
                                      guint         prop_id,
                                      const GValue *value,
                                      GParamSpec   *pspec) {
    BinaryTree *self = BINARY_TREE(obj);
    
    switch (prop_id) {
    case PROP_DATA:
        binary_tree_set_data(self, g_value_get_pointer(value));
        break;

    case PROP_PARENT:
        self->parent = g_value_get_object(value);
        break;

    case PROP_LEFT:
        binary_tree_set_left(self, g_value_get_object(value));
        break;

    case PROP_RIGHT:
        binary_tree_set_right(self, g_value_get_object(value));
        break;

    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(obj, prop_id, pspec);
        break;
    }
}

static void binary_tree_finalize (GObject *obj) {
    GObjectClass *parent_cls = binary_tree_parent_class;
    BinaryTree *self = BINARY_TREE(obj);

    g_free(self->data);
    if (self->left) g_object_unref(self->left);
    if (self->right) g_object_unref(self->right);

    parent_cls->finalize(obj);
}

static void binary_tree_class_init (BinaryTreeClass *cls) {
    GObjectClass *gobject_cls = G_OBJECT_CLASS(cls);

    gobject_cls->get_property = binary_tree_get_property;
    gobject_cls->set_property = binary_tree_set_property;
    gobject_cls->finalize = binary_tree_finalize;
    
    g_object_class_install_property(
        gobject_cls,
        PROP_DATA,
        g_param_spec_pointer(
            "data", "Data", "The data for a tree node",
            G_PARAM_READWRITE));
    
    g_object_class_install_property(
        gobject_cls,
        PROP_PARENT,
        g_param_spec_object(
            "parent", "Parent node", "The parent of the current node",
            TYPE_BINARY_TREE,
            G_PARAM_READWRITE));

    g_object_class_install_property(
        gobject_cls,
        PROP_LEFT,
        g_param_spec_object(
            "left", "Left child", "Left child of the current node",
            TYPE_BINARY_TREE,
            G_PARAM_READWRITE));

    g_object_class_install_property(
            gobject_cls,
            PROP_RIGHT,
            g_param_spec_object(
                "right", "Right child", "Right child of the current node",
                TYPE_BINARY_TREE,
                G_PARAM_READWRITE));

    g_object_class_install_property(
            gobject_cls,
            PROP_HAS_PARENT,
            g_param_spec_boolean(
                "has-parent", "Has parent", "Whether the current node has a parent",
                FALSE,
                G_PARAM_READABLE));

    g_object_class_install_property(
            gobject_cls,
            PROP_HAS_LEFT,
            g_param_spec_boolean(
                "has-left", "Has left", "Whether the current node has a left child",
                FALSE,
                G_PARAM_READABLE));

    g_object_class_install_property(
            gobject_cls,
            PROP_HAS_RIGHT,
            g_param_spec_boolean(
                "has-right", "Has right", "Whether the current node has a right child",
                FALSE,
                G_PARAM_READABLE));
}

static void binary_tree_init (BinaryTree *self) {
    /* nop  */
}


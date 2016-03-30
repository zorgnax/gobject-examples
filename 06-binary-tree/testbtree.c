/*
An example based on the lazy BinaryTree in the Moose cookbook
http://search.cpan.org/~drolsky/Moose-0.98/lib/Moose/Cookbook/Basics/Recipe3.pod

This one shows an object that relies on pointers to object of its own type
and a get method that creates a new binary tree when accessed.

I had trouble deciding whether to use properties or my own accessor methods,
so I used both.
*/

#include <string.h>
#include <glib-object.h>
#include "tap.h"
#include "binarytree.h"

int main () {
    g_type_init();

    plan(34);

    BinaryTree *root = binary_tree_new("data", g_strdup("root"));
    ok (IS_BINARY_TREE(root), "isa BinaryTree");

    ok (!binary_tree_has_left(root), "no left node yet");
    ok (!binary_tree_has_right(root), "no right node yet");
    ok (!binary_tree_has_parent(root), "no parent for root node");

    /* left node  */
    BinaryTree *left = binary_tree_get_left(root);
    ok (IS_BINARY_TREE(left), "isa BinaryTree");

    ok (binary_tree_get_left(root) == left, "got the same node (and it is %p)", left);
    ok (binary_tree_has_left(root), "we have a left node now");

    ok (binary_tree_has_parent(left), "left has a parent");
    ok (binary_tree_get_parent(left) == root, "left's parent is the root");

    ok (!binary_tree_has_left(left), "left has no left node yet");
    ok (!binary_tree_has_right(left), "left has no right node yet");

    ok (!binary_tree_get_data(left), "left has no data");

    lives_ok ({binary_tree_set_data(left, g_strdup("left"));}, "assign to left's data");

    ok (strcmp(binary_tree_get_data(left), "left") == 0, "left's data is correct");

    /* right node  */
    ok (!binary_tree_has_right(root), "still no right node yet");
    ok (!binary_tree_get_data(binary_tree_get_right(root)), "right has no data");
    ok (binary_tree_has_right(root), "now we have a right node");

    BinaryTree *right = binary_tree_get_right(root);
    ok (IS_BINARY_TREE(right), "isa BinaryTree");

    lives_ok ({binary_tree_set_data(right, g_strdup("right"));}, "assign to right's data");
    ok (strcmp(binary_tree_get_data(right), "right") == 0, "right's data is correct");

    ok (binary_tree_get_right(root) == right, "got the same node (and it is %p)", right);
    ok (binary_tree_has_right(root), "we have a right node now");

    /* make a left node of the left node  */
    BinaryTree *left_left = binary_tree_get_left(left);
    ok (IS_BINARY_TREE(left_left), "isa BinaryTree");

    ok (binary_tree_has_parent(left_left), "left_left does have a parent");
    ok (binary_tree_get_parent(left_left) == left, "left_left's parent is left");
    ok (binary_tree_has_left(left), "left has a left node now");
    ok (binary_tree_get_left(left) == left_left, "left's left is left_left");

    /* make a right node of the left node  */
    BinaryTree *left_right = binary_tree_new();
    ok (IS_BINARY_TREE(left_right), "isa BinaryTree");

    lives_ok ({binary_tree_set_right(left, left_right);}, "assign left_right to left's right node");
    ok (binary_tree_has_parent(left_right), "left_right has parent");

    ok (binary_tree_get_parent(left_right) == left, "left_right's parent is left");
    ok (binary_tree_has_right(left), "left has a right node now");
    ok (binary_tree_get_right(left) == left_right, "left's right is left_right");

    /* and check the error  */
    dies_ok ({binary_tree_set_right(left_right, left_left);}, "cant assign a node that already has a parent");

    g_set_print_handler((GPrintFunc) diag);
    binary_tree_print(root);

    g_object_unref(root);

    return exit_status();
}


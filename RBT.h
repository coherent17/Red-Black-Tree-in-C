#ifndef _RBT_H_
#define _RBT_H_

#include <stdlib.h>

typedef enum _rb_color{
    RED = 0,
    BLACK = 1
}rb_color;

typedef struct _rb_node{
    int key;
    rb_color color;
    struct _rb_node *left;
    struct _rb_node *right;
    struct _rb_node *parent;
}rb_node;


void rb_insert(rb_node **rootptr, int key);
int rb_max_height(rb_node *root);
void rb_printRBT(rb_node *root);
void rb_inorder_traversal(rb_node *root);
void rb_freeRBT(rb_node *root);
#endif
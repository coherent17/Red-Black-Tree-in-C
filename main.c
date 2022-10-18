#include "RBT.h"

int main(){
    rb_node *root = NULL;
    rb_insert(&root, 10);
    rb_insert(&root, 20);
    rb_insert(&root, 30);
    rb_insert(&root, 40);
    rb_insert(&root, 50);


    rb_printRBT(root);
    rb_inorder_traversal(root);
    printf("\n");
    rb_freeRBT(root);
    return 0;
}
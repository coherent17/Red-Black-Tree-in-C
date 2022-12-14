#include "RBT.h"
#include <stdlib.h>
#include <stdio.h>

#define PRINT_DUPLICATE_MSG 1

rb_node *rb_newNode(int key){
    rb_node *newnode = malloc(sizeof(rb_node));
    newnode->key = key;
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->parent = NULL;
    return newnode;
}

/*
left rotate: 

     x              y
    / \    ==>     / \
    a  y          x   r
      / \        / \
     b   r      a   b

*/

//Time complexity: O(1)
void rb_left_rotate(rb_node **rootptr, rb_node *x){
    rb_node *y = x->right;      //set y as right child of x
    x->right = y->left;         //turn y's left subtree into x's right subtree

    //update parent pointer of x's right (b) if b is not NULL
    if(y->left != NULL){
        y->left->parent = x;
    }

    //update y's parent pointer
    y->parent = x->parent;

    //if x's parent is NULL, let y as root of tree
    if(x->parent == NULL){
        *rootptr = y;
    }           

    //update x's parent's left/right pointer
    else if(x == x->parent->left){
        x->parent->left = y;
    }   
    else{
        x->parent->right = y;
    }

    y->left = x;                //put x on y's left
    x->parent = y;              //update parent pointer of x
}

/*
right rotate:

        y               x
       / \             / \
      x   r   ==>     a   y
     / \                 / \
    a   b               b   r 

*/

//Time complexity: O(1)
void rb_right_rotate(rb_node **rootptr, rb_node *y){
    rb_node *x = y->left;
    y->left = x->right;     //turn x's right subtree to y's left subtree

    if(x->right != NULL){
        x->right->parent = y;
    }

    x->parent = y->parent;

    if(y->parent == NULL){
        *rootptr = x;
    }

    else if(y == y->parent->left){
        y->parent->left = x;
    }
    else{
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}

//maintain red-black property after rb_insert called
void rb_insert_FixUp(rb_node **rootptr, rb_node *z){

    while((z != *rootptr) && (z->parent->color == RED)){

        if(z->parent == z->parent->parent->left){
            rb_node *y = z->parent->parent->right;

            //case1: if uncle is RED
            //parent and uncle color change to BLACK
            //grandparent color change to RED
            //Moze z to grandparent
            if(y && y->color == RED){
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }

            //uncle is BLACK:
            else{

                //case2: z is a right child
                //Move z to parent
                //left-rotate(z)
                //turn into case 3
                if(z == z->parent->right){
                    z = z->parent;
                    rb_left_rotate(rootptr, z);
                }

                //case3: z is a left child
                //parent change to BLACK
                //grandparent change to RED
                //right-rotate(grandparent)
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rb_right_rotate(rootptr, z->parent->parent);
            }
        }

        else{
            rb_node *y = z->parent->parent->left;

            //case4 (symmetry to case1): if uncle is RED
            //parent and uncle color change to BLACK
            //grandparent color change to RED
            //Moze z to grandparent
            if(y && y->color == RED){
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }

            //uncle is BLACK:
            else{
                //case5 (symmetry to case2): z is a left child
                //Move z to parent
                //right-rotate(z)
                //turn into case 3
                if(z == z->parent->left){
                    z = z->parent;
                    rb_right_rotate(rootptr, z);
                }

                //case6 (symmetry to case3): z is a right child
                //parent change to BLACK
                //grandparent change to RED
                //left-rotate(grandparent)
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rb_left_rotate(rootptr, z->parent->parent);

            }
        }
    }
    (*rootptr)->color = BLACK;
}

void rb_insert(rb_node **rootptr, int key){
    rb_node *z = rb_newNode(key);

    rb_node *y = NULL;      //y track the parent of x
    rb_node *x = *rootptr;

    //standard BST insert function
    while(x != NULL){
        y = x;
        if(key < x->key){
            x = x->left;
        }
        else if(key > x->key){
            x = x->right;
        }
        else{
            if(PRINT_DUPLICATE_MSG){
                printf("Duplicate key = %d error!\n", key);
            }
            free(z);
            return;
        }
    }
    z->parent = y;

    //if the rb tree is empty
    if(y == NULL){
        *rootptr = z;
    }

    else if(key > y->key){
        y->right = z;
    }
    else{
        y->left = z;
    }
    z->color = RED;     //coloring z red might violate red black tree property

    //call rb_insert_fixup to maintain red black tree property
    rb_insert_FixUp(rootptr, z);
}

//calculate max height of the red black tree
int rb_max_height(rb_node *root){
    if(root == NULL) return 0;
    int max_left = rb_max_height(root->left);
    int max_right = rb_max_height(root->right);
    int result = max_left > max_right ? max_left + 1 : max_right + 1;
    return result;
} 


//--------------------------<output part>----------------------------
void printTabs(int numtabs){
    int i;
    for (i = 0; i < numtabs;i++){
        printf("\t");
    }
}

void printTreeRecursive(rb_node *root, int level){
    if(root==NULL){
        printTabs(level);
        printf("---<empty>---\n");
        return;
    }

    //print out the value/color/parent of the node 
    printTabs(level);
    printf("value = %d, ", root->key);

    if(root->color == BLACK){
        printf("color = BLACK, ");
    }
    else{
        printf("color = RED, ");
    }

    if(root->parent){
        printf("parent value = %d", root->parent->key);
    }
    printf("\n");

    //recursive to print the branch of tree

    printTabs(level);
    printf("left\n");
    printTreeRecursive(root->left, level+1);

    printTabs(level);
    printf("right\n");
    printTreeRecursive(root->right, level+1);
    
    printTabs(level);
    printf("Done\n");
}

void rb_printRBT(rb_node *root){
    printf("\n\n");
    printTreeRecursive(root, 0);
}

void rb_inorder_traversal(rb_node *root){
    if(!root) return;
    rb_inorder_traversal(root->left);
    printf("%d ", root->key);
    rb_inorder_traversal(root->right);
}

void rb_freeRBT(rb_node *root){
    if(root == NULL) return;
    rb_freeRBT(root->left);
    rb_freeRBT(root->right);
    free(root);
}
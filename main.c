#include "RBT.h"
#include <stdlib.h>
#include <time.h>

int main(){

    /*
    define b(black), r(red)
    insert(3):
                3(b)
    
    insert(5):
                3(b)
                 \
                  5(r)

    insert(4):
                3(b)
                 \
                  5(r)
                 /
                4(r)

    apply case5: right-rotate(5)

                3(b)
                 \
                  4(r)
                   \
                    5(r)

    apply case6: left-rotate(4)
                4(b)
               / \
           (r)3  5(r)

    insert(0):
                4(b)
               / \
            (r)3  5(r)
            /
        (r)0

    apply case1:(but root should be black)
                4(b)
               / \
           (b)3  5(b)
             /
         (r)0

    insert(2):
                4(b)
               / \
           (b)3  5(b)
             /
         (r)0
             \
           (r)2

    apply case2: left-rotate(0)
                4(b)
               / \
           (b)3   5(b)
             /
         (r)2
           /
       (r)0

    apply case3: right rotate(3)
                4(b)
               / \
           (b)2   5(b)
             / \
         (r)0   3(r)     


    */
    rb_node *r1 = NULL;
    rb_insert(&r1, 3);
    rb_insert(&r1, 5);
    rb_insert(&r1, 4);  //case5 + case6
    rb_insert(&r1, 0);  //case1
    rb_insert(&r1, 2);  //case2 + case3
    //rb_printRBT(r1);
    rb_freeRBT(r1);


    /*
    insert(6):
                6(b)    
    
    insert(8):
                6(b)
                 \
                  8(r)
    insert(4):
                6(b)
               / \
           (r)4   8(r)        
    
    insert(9):
                6(b)
               / \
           (r)4   8(r)
                   \
                    9(r)

    apply case4: (but root should be black)
                6(b)
               / \
           (b)4   8(b)
                   \
                    9(r)    

    */

    rb_node *r2 = NULL;
    rb_insert(&r2, 6);
    rb_insert(&r2, 8);
    rb_insert(&r2, 4);
    rb_insert(&r2, 9);  //case4
    //rb_printRBT(r2);
    rb_freeRBT(r2);


    //test for duplicate key error:
    rb_node *r3 = NULL;
    rb_insert(&r3, 2);
    rb_insert(&r3, 1);
    rb_insert(&r3, 2);
    rb_insert(&r3, 3);
    rb_insert(&r3, 2);
    rb_insert(&r3, 3);
    rb_insert(&r3, 1);
    //rb_printRBT(r3);
    rb_freeRBT(r3);

    //test for large input:
    rb_node *r4 = NULL;
    srand(time(NULL));
    int count = 1000000;
    int i;
    for(i = 0; i < count; i++){
        rb_insert(&r4, rand());
    }
    rb_freeRBT(r4);
    return 0;
}
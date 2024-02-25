
#include"src/wizardry.h" 

#include "tests/test_dynamic_list.c"
#include "tests/test_linked_list.c"
#include "tests/test_hashmap.c"



#include<stdio.h>
#include<time.h>


int main(void)
{
    srand(time(NULL));
    printf("WIZARDRY TEST\n");

    // Dynamic list test
    list_test();

    // Linked list test
    linked_test();

    // Hashmap test
    //hashmap_test();
    
    fprintf(stderr, "\nTEST PASSED\n");
    return 0;
}


#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/wait.h>

#include "../list.h"

void pass(int i)
{
    printf("\033[0;32m");
    printf("test %d passed\033[0m\n", i);
}

void fail(int i)
{
    printf("\033[0;31m");
    printf("test %d failed\033[0m\n", i);
}

void supress_output()
{
    freopen("/dev/null", "w", stdout);
    freopen("/dev/null", "w", stderr);
}

DECLARE_LIST(IntList, int)
int negative_capacity_defaults()
{
    IntList l = IntList_new(-1);
    if (l.capacity == -1) return 0;

    for (int i = 0; i < 100; i++) 
        IntList_push(&l, i);
    while (IntList_size(&l))
        IntList_pop(&l);

    if (l.capacity <= 1) return 0; // should not resize beyond atleast minimum size of 2
    IntList_free(&l);

    return 1;
}

int resizes_correctly()
{
    IntList l = IntList_new(0);
    if (IntList_size(&l) != 0) return 0;
    for (int i = 0; i < 100000; i++) 
        IntList_push(&l, i);
    if (IntList_size(&l) != 100000) return 0;
    for (int i = 0; i < 500; i++) 
        IntList_pop(&l);
    if (IntList_size(&l) != 100000-500) return 0;
    IntList_free(&l);
    return 1;
}

int index_out_of_bounds()
{
    pid_t pid = fork();
    if (pid == 0) {
        supress_output();
        IntList l = IntList_new(10);
        for (int i = 0; i < 8; i++) {
            IntList_push(&l, i);
        }
        IntList_get(&l, 8);
    } else {
        int status = 0;
        wait(&status);
        if (!status) return 0; // child should have failed and not return 0
    }
    return 1;
}

int pop_empty()
{
    pid_t pid = fork();
    if (pid == 0) {
        supress_output();
        IntList l = IntList_new(10);
        IntList_pop(&l);
    } else {
        int status = 0;
        wait(&status);
        if (!status) return 0; // child should have failed and not return 0
    }
    return 1;
}

typedef struct 
{
    char s[50];
} Str;
DECLARE_LIST(StrList, Str);

int str_test()
{
    StrList l = StrList_new(0);
    for (int i = 0; i < 100000; i++) {
        StrList_push(&l, (Str) {"aaaaaaaaaaaaaaa"});
    }    
    if (strcmp("aaaaaaaaaaaaaaa", StrList_get(&l, 25690)->s)) return 0;
    StrList_free(&l);
    return 1;
}

int index_out_of_bounds_2()
{
    pid_t pid = fork();
    if (pid == 0) {
        supress_output();
        StrList l = StrList_new(10);
        StrList_get(&l, -1);
    } else {
        int status = 0;
        wait(&status);
        if (!status) return 0; // child should have failed and not return 0
    }
    return 1;
}



int main()
{
    int test_counter = 0;
    int pass_counter = 0;

    int (*tests[])() = {
        negative_capacity_defaults,
        resizes_correctly,
        index_out_of_bounds,
        pop_empty,
        str_test,
        index_out_of_bounds_2
    };

    for (int i = 0; i < sizeof(tests) / sizeof(void*); i++) {
        ++test_counter;
        if (tests[i]()) {
            ++pass_counter;
            pass(test_counter);
        } else fail(test_counter);
    }
    
    printf("\n**********************\n * %d/%d tests passed * \n**********************\n", pass_counter, test_counter);
}

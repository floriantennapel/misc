#include <stdio.h>
#include <time.h>

#include "vector.h"

int test_ivector_push_back()
{
    ivector vec = new_ivector(0);

    for (int i = 0; i < 100; i++) {
        ivector_push_back(&vec, i);
    }

    int result = ivector_size(&vec) == 100 && ivector_get(&vec, 99) == 99 && ivector_get(&vec, 0) == 0;
    ivector_free(&vec);
    return result;
}

int test_lvector_push_back()
{
    lvector vec = new_lvector(0);

    for (int i = 0; i < 100; i++) {
        lvector_push_back(&vec, i);
    }

    int result = lvector_size(&vec) == 100 && lvector_get(&vec, 99) == 99 && lvector_get(&vec, 0) == 0;
    lvector_free(&vec);
    return result;
}

int test_ivector_pop_back_1()
{
    ivector vec = new_ivector(0);

    // test for process kill
    // ivector_pop_back(&vec);

    int result = 1;

    for (int i = 0; i < 100; i++) {
        ivector_push_back(&vec, i);
        if (ivector_pop_back(&vec) != i) {
            result = 0;
        }
        if (ivector_size(&vec) != 0) {
            result = 0;
        }
    }

    ivector_free(&vec);
    return result;
}

int test_lvector_pop_back_1()
{
    lvector vec = new_lvector(0);

    // test for process kill
    // lvector_pop_back(&vec);

    int result = 1;

    for (int i = 0; i < 100; i++) {
        lvector_push_back(&vec, i);
        if (lvector_pop_back(&vec) != i) {
            result = 0;
        }
        if (lvector_size(&vec) != 0) {
            result = 0;
        }
    }

    lvector_free(&vec);
    return result;
}

int test_ivector_pop_back_2()
{
    ivector vec = new_ivector(0);

    for (int i = 0; i < 100; i++) {
        ivector_push_back(&vec, i);
    }
    for (int i = 0; i < 99; i++) {
        ivector_pop_back(&vec);
    }

    int result = ivector_size(&vec) == 1 && ivector_get(&vec, 0) == 0;
    ivector_free(&vec);
    return result;
}

int test_lvector_pop_back_2()
{
    lvector vec = new_lvector(0);

    for (int i = 0; i < 100; i++) {
        lvector_push_back(&vec, i);
    }
    for (int i = 0; i < 99; i++) {
        lvector_pop_back(&vec);
    }

    int result = lvector_size(&vec) == 1 && lvector_get(&vec, 0) == 0;
    lvector_free(&vec);
    return result;
}

int main()
{
    printf("push_back: %d %d\n", test_ivector_push_back(), test_lvector_push_back());
    printf("pop_back_1: %d %d\n", test_ivector_pop_back_1(), test_lvector_pop_back_1());
    printf("pop_back_2: %d %d\n", test_ivector_pop_back_2(), test_lvector_pop_back_2());
}
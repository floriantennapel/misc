#include <stdio.h>

int count_cars(char* map, int r, int c, int cols) 
{
    int count = 0;
    for (int i = r; i < r+2; i++) {
        for (int j = c; j < c+2; j++) {
            switch (map[i*(cols+1) + j]) {
            case '#':
                return -1;
            case 'X':
                ++count;
                break;
            }
        }
    }

    return count;
}

int main()
{
    int r, c;
    scanf("%d %d\n", &r, &c);
    char map[r*(c+1)];
    for (int i = 0; i < r; i++) {
        fgets(map + (i*(c+1)), c+1, stdin);
        getchar(); // '\n'
    }

    for (int cars = 0; cars <= 4; cars++) {  
        int counter = 0;
        for (int i = 0; i < r-1; i++) {
            for (int j = 0; j < c-1; j++) {
                if (count_cars(map, i, j, c) == cars) ++counter;
            }
        }
        printf("%d\n", counter);
    }
}
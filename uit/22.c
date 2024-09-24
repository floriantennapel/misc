#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void add_ten_pow(char* buf, int* buf_top, char ten_val, char one_val, char half_val, int dec_val)
{ 
    if (dec_val >= 5 && dec_val < 9) {
        buf[(*buf_top)++] = half_val;
    } else if (dec_val == 9 || dec_val == 4) {
        buf[(*buf_top)++] = one_val;
    }

    switch (dec_val) {
    case (9):
        buf[(*buf_top)++] = ten_val;
        break;
    case (4):
        buf[(*buf_top)++] = half_val;
        break;
    default:
        for (int i = 0; i < dec_val % 5; i++) {
            buf[(*buf_top)++] = one_val;
        }
    }
}

/**
* convert integer to roman numerals
*
* @param val integer from 1 to 3999 
* @return heap allocated string that must be free'd after use 
* */
char* int_to_roman(int val) 
{
    if (val < 1 || val > 3999) {
        fprintf(stderr, "int_to_roman: invalid value, must be between 1 and 3999\n");
        exit(1);
    }

    const char tens[] = {'I', 'X', 'C', 'M'};
    const char fives[] = {'V', 'L', 'D'};

    char as_str[6], buf[17];
    int buf_top = 0;

    sprintf(as_str, "%d", val); 
    int len = strlen(as_str); 

    for (int i = 0; i < len; i++) {
        if (as_str[i] == '0') 
            continue;
        
        int pow = len - i;
        if (pow < 4) {
            add_ten_pow(buf, &buf_top, tens[pow], tens[pow-1], fives[pow-1], as_str[i] - '0');
        } else if (pow == 4 && as_str[i] < '4') {
            add_ten_pow(buf, &buf_top, '_', 'M', '_', as_str[i] - '0');
        } else {
            fprintf(stderr, "int_to_roman: value is too large\n");
            exit(1);
        }
    }

    buf[buf_top] = '\0';
    char* ret_str = malloc(strlen(buf) + 1);
    if (ret_str == NULL) {
        perror("int_to_roman, ");
        exit(1);
    }

    strcpy(ret_str, buf);
    return ret_str;
}

int get_roman_val(char roman)
{
    const int vals[] = {100, 500, 0, 0, 0, 0, 1, 0, 0, 50, 1000, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 10};
    
    if (roman < 'C' || roman > 'X' || vals[roman - 'C'] == 0) {
        fprintf(stderr, "get_roman_val: unknown roman numeral\n");
        exit(1);
    }

    return vals[roman - 'C'];
}

int roman_to_int(const char* numeral)
{
    int sum = 0;
    int prev = -1;
    int current = -1;

    int len = strlen(numeral);
    for (int i = 0; i < len; i++) {
        current = get_roman_val(numeral[i]);
        if (prev != -1) {
            if (prev < current) {
                sum += current - prev;
                current = -1;
            } else {
                sum += prev;
            }
        }
        prev = current;
    }

    if (current != -1) sum += current;
    return sum;
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        while (1) {
            for (int i = 1; i < 4000; i++) {
                char* roman = int_to_roman(i);
                //printf("%d %s %d\n", i, roman, roman_to_int(roman));
                free(roman);
            }
        }
    } else if (argv[1][0] >= '0' && argv[1][0] <= '9') {
        char* roman = int_to_roman(atoi(argv[1]));
        printf("%s as a roman numeral: %s\n", argv[1], roman);
        free(roman);
    } else {
        printf("the roman numeral %s is: %d\n", argv[1], roman_to_int(argv[1]));
    }
}

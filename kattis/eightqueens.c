#include <stdio.h>
#include <string.h>

int check_queen_pos(char* board, int r, int c)
{
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if ((!dr) && (!dc)) continue;
            int cr = r;
            int cc = c;
            while ((cr >= 0) && (cr < 8) && (cc >= 0) && (cc < 8)) {
                if ((cr != r) || (cc != c)) {
                    if (board[cr * 8 + cc] == '*') 
                        return 0;
                }
                cr += dr;
                cc += dc;
            }
        }
    }

    return 1;
}

int main()
{
    char board[8*8];
    char buf[10];

    for (int i = 0; i < 8; i++) {
        fgets(buf, 10, stdin);
        memcpy(board + i*8, buf, 8);
    }

    int counter = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i*8 + j] == '*') {
                if (!check_queen_pos(board, i, j)) {
                    puts("invalid");
                    return 0;
                }
                ++counter;
            }
        }
    }

    if (counter != 8) {
        puts("invalid");
    } else {
        puts("valid");
    }
}
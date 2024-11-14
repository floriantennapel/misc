#include <stdio.h>

const int tung = 29260, gold = 29370;

int main()
{
    int w, s;
    scanf("%d %d", &w, &s);
    int total_tung = (s * (s+1) / 2) * tung;
    for (int i = 1; i <= s; i++) {
        if (total_tung - i*tung + i*gold == w) {
            printf("%d\n", i);
            break;
        }
    }
}

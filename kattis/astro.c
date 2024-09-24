#include <stdio.h>
#include <stdlib.h>

char buf[8];
long read_time()
{
    fgets(buf, 8, stdin);
    long tmp = atol(buf) * 60;
    tmp += atol(buf+3);
    return tmp;
}

void write_time(long timestamp)
{
    const char* days[] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    const char* day = days[(timestamp / 60 / 24) % 7];
    int day_mod = timestamp % (60 * 24);
    int h = day_mod / 60;
    int m = day_mod % 60;
    printf("%s\n%02d:%02d\n", day, h, m);
}

int main()
{
    char buf[8];
    long s1 = read_time();
    long s2 = read_time();
    long f1 = read_time();
    long f2 = read_time();

    long max = f1 * f2;

    if (s1 == s2) {
        write_time(s1);
        return 0;
    }

    for (long timestamp = s1; timestamp < s1 + max; timestamp += f1) {
        if (((timestamp - s2) % f2 == 0) && timestamp > s2) {
            write_time(timestamp);
            return 0;
        }
    }

    puts("Never");
}

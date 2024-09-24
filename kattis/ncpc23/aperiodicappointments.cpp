#include <bits/stdc++.h>

using namespace std;

void set_bit(char* bits, int i) 
{
    bits[i / 8] |= 1 << i % 8;
}

bool get_bit(const char* bits, int i)
{
    return (bits[i/8]) & (1 << i%8);
}

bool has_pattern(const char* bits, int t, int k, int ind)
{
    int indexes[k];
    for (int i = 1; i <= k; i++) {
        indexes[i-1] = ind - t * i;
    }

    for (int j = 0; j < t; j++) {
        bool current = get_bit(bits, indexes[0]++);
        for (int i = 1; i < k; i++) {
            if (get_bit(bits, indexes[i]++) != current) return false;
        }
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    char* days = (char*) calloc(n / 8 + 1, 1);

    free(days);
}
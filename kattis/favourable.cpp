#include <bits/stdc++.h>

#define PAGES 401

using namespace std;

long long visited[PAGES];
vector<int> book[PAGES];

long long count_paths(long long current)
{
    if (visited[current] != -1) {
        return visited[current];
    }

    auto& next_or_end = book[current];
    if (next_or_end.size() == 1) {
        return next_or_end[0];
    }

    long long sum = 0;
    for (int n : next_or_end) {
        sum += count_paths(n);
    }
    
    visited[current] = sum;
    return sum;
}

int main()
{
    ios_base::sync_with_stdio(false);
    
    int t, s, page, n2, n3;
    string rest;

    cin >> t;

    for (int i = 0; i < t; i++) {
        memset(visited, -1, sizeof(long long) * PAGES);
        memset(book, 0, sizeof(vector<int>) * PAGES);

        cin >> s;
        for (int j = 0; j < s; j++) {
            cin >> page;
            cin >> rest;
            
            if (rest[0] == 'f') {
                book[page] = {1};
            } else if (rest[0] == 'c') {
                book[page] = {0};
            } else {
                cin >> n2 >> n3;
                book[page] = {stoi(rest), n2, n3};
            }
        }


        auto result = count_paths(1);
        if (result == -1) {
            result = 0;
        }

        cout << result << '\n';
    }
    
}

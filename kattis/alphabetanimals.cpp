#include <iostream>
#include <array>
#include <string>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    array<vector<string>, 26> alpha;
    string prev;
    int n;
    cin >> prev >> n;
    char first = prev[prev.size()-1];

    for (int i = 0; i < n; i++) {
        string a;
        cin >> a;
        alpha[a[0]-'a'].push_back(move(a));
    }

    const auto& animals = alpha[first-'a'];
    if (animals.empty())
        cout << "?\n";
    else {
        for (const string& a : animals) {
            char key = a[a.size()-1];
            const auto& next = alpha[key-'a'];
            if (next.empty() || (next.size() == 1 && first == key)) {
                cout << a << "!\n";
                return 0;
            }
        }
        cout << animals[0] << '\n';
    }
}

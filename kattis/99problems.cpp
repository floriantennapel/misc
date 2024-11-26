#include <iostream>
#include <map>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q, t, d;
    cin >> n >> q;
    
    map<int,int> m;
    for (int i = 0; i < n; i++) {
        cin >> d;
        ++m[d];
    }

    for (int i = 0; i < q; i++) {
        cin >> t >> d;
        auto iter = m.upper_bound(d);
        if (t == 1) {
            if (iter == end(m)) {
                cout << "-1\n";
                continue;
            }
        } else {
            if (iter == begin(m)) {
                cout << "-1\n";
                continue;
            }
            --iter;
        }
        cout << get<0>(*iter) << '\n';
        if ((--get<1>(*iter)) == 0) {
            m.erase(iter);
        }
    }
}

#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

#define LEFT(i) 2*(i)
#define RIGHT(i) 2*(i)+1
#define PARENT(i) (i)/2

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q, x, y, z;
    cin >> n >> q;
    vector<int> tree(n+n);
    for (int i = 1; i <= n; i++)
        cin >> tree[i+n];

    for (int i = n-1; i > 0; i--)
        tree[i] = gcd(tree[LEFT(i)], tree[RIGHT(i)]);

    while (q--) {
        cin >> x >> y >> z;
        if (x == 1) {
            tree[y+n] = z;
            for (int i = PARENT(y+n); i > 0; i = PARENT(i))
                tree[i] = gcd(tree[LEFT(i)], tree[RIGHT(i)]);
        } else {
            int l = y+n, r = z+n;
            int res = gcd(tree[l], tree[r]);
            for (int pl = PARENT(l), pr = PARENT(r); pl != pr; pl = PARENT(pl), pr = PARENT(pr)) {
                if (l % 2 == 0)
                    res = gcd(res, tree[RIGHT(pl)]);
                if (r % 2 == 1)
                    res = gcd(res, tree[LEFT(pr)]);

                l = pl;
                r = pr;
            }
            cout << res << '\n';
        }
    }
}

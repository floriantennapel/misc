#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include <tuple>

using namespace std;

long double dist_sqr(long double x, long double x_i, long double y_i)
{
    long double dx = x - x_i;
    return dx*dx + y_i*y_i; 
}

int furthest_away(vector<long double> houses, long double x)
{
    long double hi = -1;
    int ind = -1;
    for (int i = 0; i < houses.size() / 2; i += 2) {
        auto d = dist_sqr(x, houses[i], houses[i+1]);
        if (d > hi) {
            hi = d;
            ind = i;
        }
    }

    return ind;
}

tuple<long double, long double> greedy_meeting(vector<long double> houses, long double x)
{
    long double x_i, y_i;
    int furthest_ind = furthest_away(houses, x); 
    x_i = houses[furthest_ind];
    y_i = houses[furthest_ind];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    vector<long double> houses = {1.5, 1.5, 3, 0};
    auto [x, dist] = greedy_meeting(houses, 2);
    cout << x << " " << dist << '\n';
}

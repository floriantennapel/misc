#include <bits/stdc++.h>

using namespace std;
using pq_type = priority_queue<tuple<int, tuple<int, int, string>>, vector<tuple<int, tuple<int, int, string>>>, greater<tuple<int, tuple<int, int, string>>>>;

struct hash_tup 
{
    size_t operator()(const tuple<int, int, string>& tup ) const
    {
        size_t h1 = hash<int>{}(get<0>(tup));
        size_t h2 = hash<int>{}(get<1>(tup));
        size_t h3 = hash<string>{}(get<2>(tup));

        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

void add_next(
        const vector<vector<int>>& grid, 
        pq_type& queue,
        const tuple<int, tuple<int, int, string>>& current
)
{
    int max_r = 0;
    int max_c = grid[0].size() - 1;

    auto [cost, pos] = current; 
    int r = get<0>(pos);
    int c = get<1>(pos);
    string current_key = get<2>(pos);

    if (r != 0) {
        queue.push({cost + grid[r-1][c], {r-1, c, current_key}});
    }
    if (c != max_c) {
        queue.push({cost + grid[r][c+1], {r, c+1, current_key}});
    }

    if (current_key.size() != 0) {
        int jump = current_key[0] - '0' + 1;
        string new_key{current_key, 1};

        if (r - jump >= max_r) {
            queue.push({cost + grid[r - jump][c], {r - jump, c, new_key}});
        }
        if (c + jump <= max_c) {
            queue.push({cost + grid[r][c + jump], {r, c + jump, new_key}});
        }
    }
}

int dijkstra(const vector<vector<int>>& grid, const string& key)
{
    int target_row = 0;
    int target_col = grid[0].size() - 1;

    unordered_set<tuple<int, int, string>, hash_tup> visited;
    pq_type queue;

    queue.push({grid[grid.size() - 1][0], {grid.size() - 1, 0, {key}}});

    while (!queue.empty()) {
        auto current = queue.top();
        auto& [cost, pos] = current;
        queue.pop();

        if (visited.contains(pos)) {
            continue;
        }
        visited.insert(pos);

        cout << cost << " " << get<0>(pos) << " " << get<1>(pos) << " " << get<2>(pos) << '\n';

        if (get<0>(pos) == target_row && get<1>(pos) == target_col) {
            return cost;
        }  

        add_next(grid, queue, current); 
    }

    cerr << "No solution found\n";
    return -1;
}

int main()
{
    int x, y;
    char tmp;
    string key;

    cin >> x >> y;
    cin >> key;

    vector<vector<int>> grid;

    for (int i = 0; i < y; i++) {
        vector<int> row;
        for (int j = 0; j < x; j++) {
            cin >> tmp;
            row.push_back(tmp - '0'); 
        }
        grid.push_back(row);
    }

    cout << dijkstra(grid, key) << '\n';
}

#include <bits/stdc++.h>

using namespace std;

struct HashTuple
{
    size_t operator()(const tuple<int, int>& t) const noexcept
    {
        return get<0>(t) ^ (get<1>(t) << 1);
    }
};

int get(const vector<vector<int>>& map, const tuple<int, int>& pos)
{
    return map[get<0>(pos)][get<1>(pos)];
}

vector<tuple<int, int>> getNext(const vector<vector<int>>& map, const tuple<int, int>& pos, const int type)
{
    vector<tuple<int, int>> next;
    int r = get<0>(pos);
    int c = get<1>(pos);

    if (r != 0)
    {
        tuple<int, int> nextTup{r-1, c};
        if (get(map, nextTup) == type)
        {
            next.push_back(nextTup);
        }
    }
    if (r != map.size() - 1)
    {
        tuple<int, int> nextTup{r+1, c};
        if (get(map, nextTup) == type)
        {
            next.push_back(nextTup);
        }
    }
    if (c != 0)
    {
        tuple<int, int> nextTup{r, c-1};
        if (get(map, nextTup) == type)
        {
            next.push_back(nextTup);
        }
    }
    if (c != map[0].size() - 1)
    {
        tuple<int, int> nextTup{r, c+1};
        if (get(map, nextTup) == type)
        {
            next.push_back(nextTup);
        }
    }

    return next;
}

void bfs(vector<vector<int>>& partitions, const tuple<int, int>& pos, const int partitionId, const vector<vector<int>>& map)
{
    int type = get(map, pos);
    queue<tuple<int, int>> queue;
    queue.push(pos);

    while (!queue.empty())
    {
        auto current = queue.front();
        queue.pop();
        int r = get<0>(current);
        int c = get<1>(current);

        if (partitions[r][c] != -1)
        {
            continue;
        }

        partitions[get<0>(current)][get<1>(current)] = partitionId;
        for (auto nextTup : getNext(map, current, type))
        {
            queue.push(nextTup);
        }
    }
}

vector<vector<int>> partition(const vector<vector<int>>& map)
{
    // initializing to -1
    vector<vector<int>> partitions;
    partitions.reserve(map.size());

    for (auto r : map)
    {
        vector<int> row;
        row.reserve(map[0].size());

        for (size_t i = 0; i < map[0].size(); ++i)
        {
            row.push_back(-1);
        }
        partitions.push_back(row);
    }

    int currentPartition = 0;

    for (size_t i = 0; i < map.size(); ++i)
    {
        for (size_t j = 0; j < map[0].size(); ++j)
        {
            if (partitions[i][j] != -1)
            {
                continue;
            }

            bfs(partitions, {i, j}, currentPartition++, map);
        }
    }

    return partitions;
}

string connected(const tuple<int, int>& from, const tuple<int, int>& to, const vector<vector<int>>& partitions, const vector<vector<int>>& map)
{
    if (get(partitions, from) != get(partitions, to))
    {
        return "neither";
    } else
    {
        return get(map, from) ? "decimal" : "binary";
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int r, c, n, r1, r2, c1, c2;
    string line;
    vector<vector<int>> map;

    cin >> r >> c;

    for (size_t i = 0; i < r; i++)
    {
        vector<int> lineVec;
        cin >> line;
        for (char ch : line) {
            lineVec.push_back(ch - '0');
        }
        map.push_back(lineVec);
    }

    auto partitions = partition(map);

    cin >> n;
    for (size_t i = 0; i < n; i++)
    {
        cin >> r1 >> c1 >> r2 >> c2;
        cout << connected({r1-1, c1-1}, {r2-1, c2-1}, partitions, map) << '\n';
    }
}

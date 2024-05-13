#include <bits/stdc++.h>

using namespace std;

typedef struct Room {
  int dist;
  int index;
  int next;
  int end;
  bool isEntry; 
} Room;

vector<Room> rooms;

Room& dfs(int index, bool isFirstCall) {
  Room& current = rooms[index];
  if (!isFirstCall) {
    current.isEntry = false;
  }

  if (current.dist != -1) {
    return current;
  }

  Room& path = dfs(current.next, false);
  current.end = path.end;
  current.dist = path.dist + 1;

  return current;
}

bool cmp(const Room& a, const Room& b) {
  if (a.dist == b.dist) {
    return a.index < b.index;
  } else {
    return a.dist < b.dist;
  }
}

vector<vector<Room>> initialize(int n) {
  int val;
  for (int i = 0; i < n; i++) {
    cin >> val; 
    if (val == -1) {
      rooms.push_back({0, i, -1, i, true});
    } else {
      rooms.push_back({-1, i, val, -1, true});
    }
  }

  for (int i = 0; i < n; i++) {
    dfs(i, true);
  }

  vector<vector<Room>> entryPoints(n);
  for (int i = 0; i < n; i++) {
    Room current = rooms[i];
    if (current.isEntry) {
      entryPoints[current.end].push_back(current);
    }
  }

  return entryPoints;
}

int marioPath(int start, vector<vector<Room>>& entryPoints) {
  int end = rooms[start].end; 
  vector<Room>& entries = entryPoints[end];
  return min_element(entries.begin(), entries.end(), cmp)->index;
}

int main() {
  int n, a, entry;
  cin >> n;

  vector<vector<Room>> entryPoints = initialize(n);
  cin >> a;
  for (int i = 0; i < a; i++) {
    cin >> entry;
    cout << marioPath(entry, entryPoints) << '\n';
  }
}

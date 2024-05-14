#include <bits/stdc++.h>

using namespace std;
using pq_type = priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>;

int findMax(pq_type& schedule, int k) {
  int back = schedule.top().first;
  int front = back + k;

  pq_type current;
  int count = current.size();

  while (schedule.size() > 0) {
    auto p = schedule.top(); schedule.pop();
    current.push({p.second, p.first});

    int diff = p.first - front;
    back += diff;
    front += diff;

    while (current.size() > 0 && current.top().first < back) {
      current.pop();
    }

    while (schedule.size() > 0 && schedule.top().first <= front) {
      auto pa = schedule.top(); schedule.pop();
      current.push({pa.second, pa.first});
    }

    if (current.size() > count) {
      count = current.size();
    }
  }

  return count;
}

int main() {
  int n, k, s, e;
  cin >> n >> k;

  pq_type schedule;

  for (int i = 0; i < n; i++) {
    scanf("%d %d", &s, &e);
    schedule.push({s, e});
  }

  cout << findMax(schedule, k) << "\n";
}

#include <bits/stdc++.h>

using namespace std;

double heuristic(const string &current, const string &target) {
  int sum = 0;

  for (int i = 0; i < 8; i++) {
    char c = current[i] - 'A'; 
    char t = target[i] - 'A'; 

    sum += (t + 6 - c) % 6;
  }

  return sum / 3.;
}

void rotate(string &str, int ind) {
  char c = str[ind];
  str[ind] = (c - 'A' + 1) % 6 + 'A';
}

string pressButton(const string &str, int ind) {
  char button = str[ind];
  string newStr(str);

  switch (button) {
    case 'A':
      if (ind != 0) {
        rotate(newStr, ind-1);
      }
      if (ind != 7) {
        rotate(newStr, ind+1);
      }
      break;
    case 'B':
      if (ind > 0 && ind < 7) {
        newStr[ind+1] = newStr[ind-1];
      } 
      break;
    case 'C':
      rotate(newStr, 7-ind);
      break;
    case 'D':
      if (ind > 0 && ind < 4) {
        for (int i = 0; i < ind; i++) {
          rotate(newStr, i);
        }
      } else if (ind > 3 && ind < 7) {
        for (int i = ind+1; i < 8; i++) {
          rotate(newStr, i);
        }
      }
      break;
    case 'E':
      if (ind > 0 && ind < 7) {
        int y = min(7 - ind, ind);
        rotate(newStr, ind-y);
        rotate(newStr, ind+y);
      }
      break;
    case 'F':
      int x;
      if (ind % 2 == 0) {
        x = (ind + 10) / 2 - 1;
      } else {
        x = (ind + 1) / 2 - 1;
      }
      rotate(newStr, x);
      break;
  }

  return newStr;
 }

vector<string> getNext(const string &current) {
  vector<string> next;  

  for (int i = 0; i < 8; i++) {
    next.push_back(pressButton(current, i));
  }

  return next;
}

int aStar(const string &start, const string &target) {
  using pq_type = tuple<double, int, string>;

  unordered_set<string> visited;
  priority_queue<pq_type, vector<pq_type>, greater<pq_type>> queue;
  queue.push({0, 0, start});

  while (!queue.empty()) {
    auto current = queue.top(); queue.pop();
    auto currentStr = get<2>(current);
    
    if (visited.count(currentStr) != 0) {
      continue;
    }
    visited.insert(currentStr);

    if (currentStr.compare(target) == 0) {
      return get<1>(current);
    } 

    for (const auto &next : getNext(currentStr)) {
      int dist = get<1>(current) + 1;
      queue.push({dist + heuristic(next, target), dist, next});  
    }
  }

  cout << "Could not find path\n";
  return 0;
}

int main() {
  string start, target;
  cin >> start >> target;

  cout << aStar(start, target) << "\n";
}

#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int die[3][6];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 6; j++) {
            cin >> die[i][j];
        }
    }

    for (int i = 0; i < 3; i++) {
        vector<double> score;
        for (int j = 0; j < 3; j++) {
            if (j == i) continue;
            int count_win = 0;
            int total = 36;
            for (int k = 0; k < 6; k++) {
                for (int l = 0; l < 6; l++) {
                    if (die[i][k] == die[j][l]) --total;
                    else if (die[i][k] > die[j][l]) ++count_win;
                }
            }
            score.push_back(count_win / (double) total);
        }
        
        if (score[0] >= 0.5 && score[1] >= 0.5) {
            cout << i + 1 << '\n';
            return 0;
        }
            
    }
    cout << "No dice\n";
}
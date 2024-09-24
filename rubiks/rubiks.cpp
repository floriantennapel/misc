#include <iostream>
#include <array>
#include <string>

using cube = std::array<std::array<int, 8>, 6>;
const std::array<std::string, 6> colors = {"white", "red", "blue", "orange", "green", "yellow"};

cube u(const cube& c)
{
    cube nc(c);
    for (int i = 1; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            nc[i][j] = c[(i%4) + 1][j];
        }
    }
}

int main()
{
    int cube[6*8];
    u(cube);
}

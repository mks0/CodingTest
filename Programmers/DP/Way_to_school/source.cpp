#include <string>
#include <vector>
using namespace std;

int solution(int m, int n, vector<vector<int>> puddles) {
    const long DIV = 1000000007;
    const long WATER = -1;
    vector<vector<long> > field(m+1, vector<long>(n+1, 0));

    for (const auto& iter : puddles)
        field[iter[0]][iter[1]] = WATER;
    for (auto i = 1; i <= m; ++i) {
        if (WATER == field[i][1]) break;
        field[i][1] = 1;
    }
    for (auto i = 1; i <= n; ++i) {
        if (WATER == field[1][i]) break;
        field[1][i] = 1;
    }

    for (auto i = 2; i <= m; ++i)
        for (auto j = 2; j <= n; ++j)
            if (WATER < field[i][j])
                field[i][j] = (((WATER < field[i-1][j]) ? field[i-1][j] : 0) + ((WATER < field[i][j-1]) ? field[i][j-1] : 0)) % DIV;
    return static_cast<int>(field[m][n] % DIV);
}
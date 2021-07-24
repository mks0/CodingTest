#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

enum { LOST = -1, UNKNOWN, WIN };

void Scan(vector<vector<int>>& table, const int n, const int row, const int col) {
    const int result = table[row][col];
    deque<int> q;
    q.push_back(col);
    while (!q.empty()) {
        auto top = q.front();
        for (int i = 0; i < n; ++i) {
            if (result == table[top][i] && UNKNOWN == table[row][i]) {
                table[row][i] = result;
                q.push_back(i);
            }
        }
        q.pop_front();
    }
}

int solution(int n, vector<vector<int>> results) {
    vector<vector<int>> table(n, vector<int>(n, UNKNOWN));
    for (const auto& iter : results) {
        table[iter[0]-1][iter[1]-1] = WIN;
        table[iter[1]-1][iter[0]-1] = LOST;
    }
    
    for (int i = 0; i < n; ++i) {
        if (1 >= count(table[i].begin(), table[i].end(), UNKNOWN))
            continue;
        for (int j = 0; j < n; ++j) {
            if (UNKNOWN != table[i][j])
                Scan(table, n, i, j);
        }
    }
    
    int answer = 0;
    for (int i = 0; i < n; ++i)
        if (1 >= count(table[i].begin(), table[i].end(), UNKNOWN))
            ++answer;
    return answer;
}
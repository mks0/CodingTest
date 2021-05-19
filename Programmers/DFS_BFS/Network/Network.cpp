#include <string>
#include <vector>
using namespace std;
vector<vector<int>>* coms = nullptr;
vector<bool> visited;

void DFS(const int idx) {
    visited[idx] = true;
    for (int i = 0; i < visited.size(); ++i) {
        if ((idx != i) && (1 == (*coms)[idx][i]) && !visited[i])
            DFS(i);
    }
}

int solution(int n, vector<vector<int>> computers) {
    coms = &computers;
    visited.assign(n, false);
    int answer = 0;
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            answer++;
            DFS(i);
        }
    }
    return answer;
}
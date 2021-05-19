#include <string>
#include <vector>
#include <algorithm>
using namespace std;
vector<vector<string>>* ticket = nullptr;
vector<string> answer;
vector<bool> visited;

bool DFS(const string& next) {
    answer.push_back(next);
    if (answer.size() == ticket->size() + 1) return true;
    for (int i = 0; i < visited.size(); ++i) {
        if ((!visited[i]) && ((*ticket)[i][0] == next)) {
            visited[i] = true;
            if(DFS((*ticket)[i][1])) return true;
            visited[i] = false;
        }
    }
    answer.pop_back();
    return false;
}
vector<string> solution(vector<vector<string>> tickets) {
    sort(tickets.begin(), tickets.end(), [](const vector<string>& a, const vector<string>& b){ return a[1] < b[1]; });
    visited.assign(tickets.size(), false);
    answer.clear();
    ticket = &tickets;
    (void)DFS("ICN");
    return answer;
}
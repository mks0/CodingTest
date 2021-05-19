#include <string>
#include <vector>
#include <queue>
using namespace std;
bool Compare(const string& str1, const string& str2) {
    int diff = 0;
    for (int i = 0; i < str1.size(); ++i)
        if (str1[i] != str2[i]) ++diff;
    return (1 == diff) ? true : false;
}
int solution(string begin, string target, vector<string> words) {
    struct QDat { vector<bool> visited; string to; int steps; };
    queue<QDat> q;
    vector<bool> visited(words.size(), false);
    q.push({visited, begin, 0});
    while (!q.empty()) {
        auto top = q.front();
        if (top.to == target)
            break;
        q.pop();
        for (int i = 0; i < words.size(); ++i) {
            if ((!top.visited[i]) && Compare(words[i], top.to)) {
                top.visited[i] = true;
                q.push({top.visited, words[i], top.steps + 1});
            }
        }
    }
    return q.empty() ? 0 : q.front().steps;
}
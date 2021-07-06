#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

using cond = pair<int,int>;
int solution(vector<vector<int>> jobs) {
    int answer = 0, t = 0, i = 0;
    sort(jobs.begin(), jobs.end(), [](const vector<int>& a, const vector<int>& b) { return a[0] < b[0]; }); // 요청시간 오름차순
    auto cmp = [](const cond& a, const cond& b) { return a.second > b.second; }; // 소요시간 오름차순
    priority_queue<cond,vector<cond>,decltype(cmp)> q(cmp);
        
    while (i < jobs.size() || !q.empty()) {
        // 추가 가능 작업들을 큐에 추가
        while (i < jobs.size() && t >= jobs[i][0]) {
            q.push(make_pair(jobs[i][0], jobs[i][1]));
            ++i;
        }
        // 큐의 Top 작업이 완료 가능한 경우
        if (!q.empty() && q.top().first <= t) {
            answer += t - q.top().first + q.top().second;
            t += q.top().second;
            q.pop();
        }
        else
            ++t;
    }
    return answer / jobs.size();
}
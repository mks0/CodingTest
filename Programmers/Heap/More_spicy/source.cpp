#include <string>
#include <vector>
#include <queue>
using namespace std;

int solution(vector<int> scoville, int K) {
    int answer = 0;
    priority_queue<int,vector<int>,greater<int> > q; // 오름차순
    for (auto iter : scoville) q.push(iter);
    auto top = q.top();
    while (top < K) {
        if (q.empty()) return -1;
        q.pop();
        auto mix = top + q.top() * 2;
        
        if (q.empty()) return -1;
        q.pop();
        
        q.push(mix);
        top = q.top();
        answer++;
    }
    return answer;
}
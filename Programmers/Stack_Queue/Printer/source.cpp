#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

struct Jobs {
    Jobs(int p, int i) : pri(p), idx(i) {}
    int pri, idx;	// pri:우선순위, idx:최초 작업순서
};

int solution(vector<int> priorities, int location) {
    deque<Jobs> q;
    for (int i = 0; i < priorities.size(); ++i)
        q.push_back(Jobs(priorities[i], i));
    
    int rank = 1;
    while (!q.empty()) {
		// 큐 내 가장 큰 중요도 확인
        int maxV = max_element(q.begin(), q.end(), [](const Jobs& a, const Jobs& b){ return a.pri < b.pri; })->pri;
        auto& pt = q.front();
        if (pt.pri < maxV) {	// 첫 번째 원소보다 중요도가 큰 원소가 있다면 
            q.push_back(pt);	// 뒤로 되돌리기
            q.pop_front();
        } else {
            if (location == pt.idx)	// 인쇄 요청된 문서라면 현재 순서 값 바로 리턴
                return rank;
            else
                q.pop_front();
            ++rank;
        }
    }
    return 0;
}
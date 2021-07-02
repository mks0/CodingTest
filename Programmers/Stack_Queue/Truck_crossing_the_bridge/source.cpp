#include <string>
#include <vector>
#include <deque>
using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int steps = 0, accWeight = 0, vIdx = 0;
    deque<pair<int,int> > bridge;   // pos, weight

    do {
        ++steps;    // 시간 경과
        // 기존 트럭 통과
        while (!bridge.empty() && bridge_length <= bridge.front().first) {
            accWeight -= bridge.front().second;
            bridge.pop_front();
        }
        // 신규 트럭 진입
        if (vIdx < truck_weights.size() && weight >= accWeight + truck_weights[vIdx]) {
            bridge.push_back(make_pair(0, truck_weights[vIdx]));
            accWeight += truck_weights[vIdx++];
        }
        for (auto& iter : bridge) ++iter.first; // 다리 위 트럭들 이동
    } while (!bridge.empty());
    return steps;
}
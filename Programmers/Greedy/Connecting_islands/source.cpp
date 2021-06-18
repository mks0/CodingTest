#include <vector>
#include <algorithm>
using namespace std;

// 부모 정점 찾기
inline int FindParent(vector<int>& nodes, const int node) {
    if (node == nodes[node]) return node;
    else return nodes[node] = FindParent(nodes, nodes[node]);
}

int solution(int n, vector<vector<int>> costs) {
	// 가중치 기준 오름차순 정렬
    sort(costs.begin(), costs.end(), [](vector<int>& a, vector<int>& b) { return a[2] < b[2]; });
	
	// 정점 생성. 값은 부모 정점을 의미하는 것으로, 자기 자신으로 초기화.
    vector<int> nodes(n);
    for (int i = 0; i < n; ++i) nodes[i] = i;

	// 작은 가중치부터 순회
    int answer = 0;
    for (const auto& iter : costs) {
        const auto first = FindParent(nodes, iter[0]);	// 간선의 시작 정점
        const auto second = FindParent(nodes, iter[1]);	// 간선의 끝 정점
        if (first != second) {
            nodes[first] = nodes[second] = min(first, second);	// 부모 정점 규칙은 작은 값으로 통일
            answer += iter[2];
            if (1 >= --n) break;	// 모든 정점을 연결한 노드 수 = 정점 - 1
        }
    }
    return answer;
}
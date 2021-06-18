#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<vector<int>> routes) {
	// 진입 지점 기준, 오름차순 정렬
    sort(routes.begin(), routes.end(), [](vector<int>& a, vector<int>& b){ return a[0] < b[0]; });
	
	// 루트 순회
    int answer = 0, endVar = 30001;
    for (const auto& iter : routes) {
        if (iter[0] <= endVar)	// 진입 지점보다 최소 진출 지점이 더 큰 경우, 최소 진출 지점 업데이트
			endVar = min(endVar, iter[1]);
        else {					// 진입 지점보다 최소 진출 지점이 더 작은 경우, 카메라 설치하고 최소 진출 지점 신규 수립
            ++answer;
            endVar = iter[1];
        }
    }
    return answer + 1;
}
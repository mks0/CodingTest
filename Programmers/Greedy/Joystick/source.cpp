#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void GetVector(vector<int>& result, const string& name, const int N) {
    const int A = 'A';
    const int Z = 'Z';
    vector<int> v(N);
    for (int i = 0; i < N; ++i)
        v[i] = min(static_cast<int>(name[i]) - A, Z + 1 - static_cast<int>(name[i]));	// 위/아래 중 더 작은 이동으로
    swap(result, v);
}

bool IsLeftMoveBest(const vector<int>& v, const int N) {
    int left = 1, right = N - 1;
    int leftDelta = 0, rightDelta = 0;
    while (left < right) {
        if (0 < v[left++]) leftDelta++;
        if (0 < v[right--]) rightDelta++;
    }
    return leftDelta <= rightDelta;
}

int MoveCursor(vector<int>& v, const int N) {
    // 1글자 문자는 이동 고려 필요 없음. 위/아래 이동 결과만 반환
	if (1 == v.size()) return v[0];
	
	// 2글자 문자는 2번째 문자가 A인 경우/아닌 경우로 구분하여 처리	
    else if (2 == v.size()) return v[0] + ((0 < v[1]) ? 1 + v[1] : 0);

	// 3글자 이상인 경우, 왼쪽 이동이 최적인지 탐색
    const bool leftBest = IsLeftMoveBest(v, N);
	
	// 첫 문자는 이동 없으므로 바로 변경 처리
	// 왼쪽/오른쪽 인덱싱 정의
    int pt = 0, answer = v[0], left = 1, right = N - 1;
    v[0] = 0;
	
	// 왼쪽/오른쪽 인덱싱이 어긋날 때까지
    while (left < right) {
        while (N - 1 > left && 0 == v[left]) ++left;	// 왼쪽
        while (0 < right && 0 == v[right]) --right;		// 오른쪽
        
		// pt로부터의 왼쪽/오른쪽 이동 거리
		auto leftDelta = (N + left - pt) % N;
        auto rightDelta = (pt + N - right) % N;
        
		if (leftBest)	// 왼쪽 착수가 유리한 경우
            pt = (leftDelta <= rightDelta) ? left : right;
        else			// 오른쪽 착수가 유리한 경우
            pt = (leftDelta < rightDelta) ? left : right;
			
        // 왼쪽/오른쪽 이동 거리 중 작은 것 선택
		answer += min(leftDelta, rightDelta);
		
		// 왼쪽/오른쪽 중 작은 쪽에 대해 문자 변경 처리 반영
        answer += v[pt];
		
		// 변경 처리 완료 됐으므로 제거
        v[pt] = 0;
    }
    return answer;
}
int solution(string name) {
    int N = static_cast<int>(name.size());
    vector<int> v;
	
	// 문자열 내 문자 별로 위/아래 커서 움직임 개수 파악
	// ex) JAZ -> {9, 0, 1}, AAB -> {0, 0, 1}
    GetVector(v, name, N);
	
	// 커서 이동을 포함한 결과를 반환
    return MoveCursor(v, N);
}
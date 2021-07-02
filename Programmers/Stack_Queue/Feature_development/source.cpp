#include <string>
#include <vector>
using namespace std;
inline int Remain(const int prog, const int spd) {
    return ((99 - prog) / spd) + 1;	// 배포 가능일
}
vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer(1,0);
    int i = 0;
    while (i < progresses.size()) {
        int next = Remain(progresses[i], speeds[i]);
        answer.back()++;	// 배포 처리
        while ((i + 1 < progresses.size()) &&
		(next >= Remain(progresses[i + 1], speeds[i + 1]))) {
            // 배포 처리(다음 작업도 앞 작업과 함께 배포 가능)
			answer.back()++;
            i++;
        }
		
		// 잔여 작업이 남은 경우 정답 벡터 신규 추가
        if(++i < progresses.size())
            answer.push_back(0);
    }
    return answer;
}
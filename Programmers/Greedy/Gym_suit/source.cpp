#include <string>
#include <vector>
using namespace std;

int solution(int n, vector<int> lost, vector<int> reserve)
{
    // 학생 벡터 선언(인덱스:학생 번호, 값:체육복 보유 수)
    // 모든 학생이 체육복을 보유하고 있다고 가정
    // 균일한 처리를 위해 양 끝에 더미 추가
    vector<int> student(n + 2, 1);
    for (const auto& iter : lost) --student[iter];      // 도난된 학생
    for (const auto& iter : reserve) ++student[iter];   // 여분 학생
    
    // 체육복 학생 수 카운트
    int answer = 0;
    for (int i = 1; i < n + 1; ++i) {
		// 여분 학생
        if (1 < student[i])
		{
			// [도난 학생, 여분 학생, unknown]
            if (1 > student[i - 1]) {
                --student[i];
                answer += 2;
            }
			// [1개 이상 보유 학생, 여분 학생, 도난 학생]
			else if (1 > student[i + 1]) {
                ++i;    //인덱스 점프(다음 턴 볼 필요 없음)
                ++student[i];
                answer += 2;
            }
			// [1개 이상 보유 학생, 여분 학생, 1개 이상 보유 학생]
			else	answer++;
        }
		
		// 본인 것만 보유
        else if (1 == student[i])	answer++;
    }
    return answer;
}
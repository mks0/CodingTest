#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int solution(vector<int> people, int limit) {
    sort(people.begin(), people.end());
    int left = 0, right = people.size() - 1, answer = 0;
    while (left < right) {	// 정렬 벡터 양 끝단에서 서로를 향하는 포인터로 순회
        if (limit >= people[left] + people[right]) {	// 2명 탑승 케이스 카운트
            ++answer; ++left;
            people[right--] = -1;
        }
        else --right;
    }
    for (;left < people.size(); ++left)	// 1명 탑승 케이스 카운트
        if (0 < people[left]) ++answer;
    return answer;
}
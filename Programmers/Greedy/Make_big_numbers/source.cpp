#include <string>
#include <stack>
using namespace std;
string solution(string num, int k) {
    stack<char> s;
    int i = 1;
    s.push(num[0]);
	
	// 잔여 차감횟수(k)가 있고, 탐색 인덱스가 끝이 아닌 경우
    while (0 < k && num.size() > i) {
        if (s.empty()) s.push(num[i++]);
        else if (s.top() < num[i]) {
            s.pop();
            --k;
        }
        else s.push(num[i++]);
    }
    while (0 < k--) s.pop();	// 모두 탐색했으나 잔여 차감횟수가 존재하는 경우, 스택에서 비움
    
    string answer(num.substr(i));	// k 만료로 인해 탐색이 중단된 경우 이후의 문자열은 모두 반환
    while (!s.empty()) {
        answer = s.top() + answer;
        s.pop();
    }
    return answer;
}
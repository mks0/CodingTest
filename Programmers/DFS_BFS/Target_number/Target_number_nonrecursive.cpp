#include <string>
#include <vector>
#include <stack>
using namespace std;
int solution(vector<int> numbers, int target) {
    stack<pair<int, int>> s;    // sum, index
    s.push(make_pair(0, 0));
    int answer = 0;
    while (!s.empty()) {
        auto top = s.top();
        s.pop();
        if (numbers.size() <= top.second) {
            if (top.first == target) answer++;
        } else {
            s.push(make_pair(top.first+numbers[top.second], top.second+1));
            s.push(make_pair(top.first-numbers[top.second], top.second+1));
        }
    }
    return answer;
}

/*
테스트 1 〉	통과 (7.01ms, 3.96MB)
테스트 2 〉	통과 (6.73ms, 3.96MB)
테스트 3 〉	통과 (0.02ms, 3.95MB)
테스트 4 〉	통과 (0.03ms, 3.93MB)
테스트 5 〉	통과 (0.22ms, 3.95MB)
테스트 6 〉	통과 (0.02ms, 3.95MB)
테스트 7 〉	통과 (0.02ms, 3.94MB)
테스트 8 〉	통과 (0.08ms, 3.95MB)
*/
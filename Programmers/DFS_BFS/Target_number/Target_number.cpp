#include <string>
#include <vector>
#include <stack>
using namespace std;

int solution(vector<int> numbers, int target) {
    stack<int> s;
    s.push(0);
    for (const auto& iter : numbers) {
        stack<int> temp;
        while (!s.empty()) {
            auto top = s.top();
            s.pop();
            temp.push(top + iter);
            temp.push(top - iter);
        }
        swap(s, temp);
    }
    
    int answer = 0;
    while (!s.empty()) {
        if (target == s.top()) answer++;
        s.pop();
    }
    return answer;
}

/*
테스트 1 〉	통과 (8.21ms, 7.66MB)
테스트 2 〉	통과 (8.44ms, 7.59MB)
테스트 3 〉	통과 (0.01ms, 3.96MB)
테스트 4 〉	통과 (0.04ms, 3.79MB)
테스트 5 〉	통과 (0.25ms, 3.9MB)
테스트 6 〉	통과 (0.02ms, 3.99MB)
테스트 7 〉	통과 (0.02ms, 3.95MB)
테스트 8 〉	통과 (0.07ms, 3.96MB)
*/
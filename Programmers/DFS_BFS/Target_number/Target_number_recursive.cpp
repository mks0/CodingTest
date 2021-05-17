#include <string>
#include <vector>
using namespace std;
vector<int>* nums = nullptr;
int *targetNum = nullptr;
int answer = 0;

void DFS(int sum, const int idx) {
    if (idx == nums->size()) {
        if (sum == *targetNum) answer++;
        return;
    }    
    DFS(sum + (*nums)[idx], idx + 1);
    DFS(sum - (*nums)[idx], idx + 1);
}
int solution(vector<int> numbers, int target) {
    nums = &numbers;
    targetNum = &target;
    DFS(0, 0);
    return answer;
}

/*
테스트 1 〉	통과 (3.58ms, 3.99MB)
테스트 2 〉	통과 (3.83ms, 3.82MB)
테스트 3 〉	통과 (0.01ms, 3.94MB)
테스트 4 〉	통과 (0.03ms, 3.97MB)
테스트 5 〉	통과 (0.12ms, 3.92MB)
테스트 6 〉	통과 (0.01ms, 3.94MB)
테스트 7 〉	통과 (0.01ms, 3.98MB)
테스트 8 〉	통과 (0.04ms, 3.94MB)
*/
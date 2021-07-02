#include <string>
#include <vector>
using namespace std;

vector<int> solution(vector<int> prices) {
    const int N = prices.size() - 1;
    vector<int> answer(N + 1);
    int minV = prices.back();
    answer.back() = 0;
    for (int i = N - 1; i >= 0; --i) {
        if (minV >= prices[i]) {    // 끝까지 가격이 떨어지지 않음
            minV = prices[i];
            answer[i] = N - i;
            continue;
        }
        for (int j = i + 1; j <= N; ++j) {
            if (prices[i] > prices[j]) {    // 가격이 떨어지는 때
                answer[i] = j - i;
                break;
            }
        }
    }
    return answer;
}
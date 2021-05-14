#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using INT = std::int64_t;

void input(INT& N, vector<INT>& lanCable) {
    INT K, temp;
    scanf("%ld %ld", &K, &N);
    for (INT i = 0LL; i < K; ++i) {
        scanf("%ld", &temp);
        lanCable.push_back(temp);
    }
}

void solution(const INT N, vector<INT>& lanCable) {
    sort(lanCable.begin(), lanCable.end());
    INT left = 0LL;
    INT right = lanCable.back();
    INT mid;
    while (left <= right) {
        mid = ((left + right) < 2) ? 1 : ((left + right) / 2);
        INT accN = 0LL;
        for (const auto& iter : lanCable)
            accN += iter / mid;
        if (accN < N) right = mid - 1LL;
        else left = mid + 1LL;
    }
    printf("%lld\n", left - 1LL);
}

int main() {
    INT N;
    vector<INT> lanCable;
    input(N, lanCable);
    solution(N, lanCable);
    return 0;
}
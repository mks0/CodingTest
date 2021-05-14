#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using INT = int64_t;

void input(INT& M, vector<INT>& A) {
    INT N, temp;
    scanf("%ld %ld", &N, &M);
    for (INT i = 0; i < N; ++i) {
        scanf("%ld", &temp);
        A.push_back(temp);
    }
}

void solution(const INT M, vector<INT>& A) {
    sort(A.begin(), A.end());
    INT left = 0LL;
    INT right = A.back();
    INT mid;
    bool midFlag = false;
    while (left <= right) {
        mid = (left + right) / 2LL;
        INT accM = 0LL;
        for (const auto& iter : A)
            if (0LL < iter - mid)
                accM += (iter - mid);
        if (M == accM) {
            midFlag = true;
            break;
        }
        else if (M > accM) right = mid - 1LL;
        else left = mid + 1LL;
    }
    printf("%lld\n", midFlag ? mid : left - 1LL);
}

int main() {
    INT M;
    vector<INT> A;
    input(M, A);
    solution(M, A);
    return 0;
}

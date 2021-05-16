#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using ll = long long;

//#define UNIT_TEST

int main() {
    int N;
#ifndef UNIT_TEST
    scanf("%d", &N);
    vector<int> v1(N);
    vector<int> v2(N);
    vector<int> v3(N);
    vector<int> v4(N);
    for (int i = 0; i < N; ++i)
        scanf("%d %d %d %d", &v1[i], &v2[i], &v3[i], &v4[i]);
#else
    N = 6;
    vector<int> v1{-45, -41, -36, -36, 26, -32};
    vector<int> v2{22, -27, 53, 30, -38, -54};
    vector<int> v3{42, 56, -37, -75, -10, -6};
    vector<int> v4{-16, 30, 77, -46, 62, 45};
#endif

    vector<int> mergeSrcV(N * N);
    vector<int> mergeDstV(N * N);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            mergeSrcV[N*i + j] = v1[i] + v2[j];
            mergeDstV[N*i + j] = v3[i] + v4[j];
        }
    }
    
    sort(mergeDstV.begin(), mergeDstV.end());
    
    ll result = 0LL;
    for (const auto& iter : mergeSrcV) {
        const auto p = equal_range(mergeDstV.begin(), mergeDstV.end(), -iter);
        for (auto equals = p.first; equals != p.second; ++equals)
            result++;
    }
    
#ifndef UNIT_TEST
    printf("%lld\n", result);
#else
    printf("%s, answer:5, result:%lld\n", (5 == result) ? "Pass" : "Fail", result);
#endif
    return 0;
}
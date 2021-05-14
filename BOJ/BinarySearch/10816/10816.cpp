#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using INT = int64_t;
//#define NO_CONSOLE

void input(vector<INT>& A, vector<INT>& Ms) {
    INT N;
    INT temp;
#ifndef NO_CONSOLE
    scanf("%ld", &N);
    for (INT i = 0L; i < N; ++i) {
        scanf("%ld", &temp);
        A.push_back(temp);
    }
    scanf("%ld", &N);
    for (INT i = 0L; i < N; ++i) {
        scanf("%ld", &temp);
        Ms.push_back(temp);
    }
#else
    A.push_back(6); // result : 3 0 0 1 2 0 0 2
    A.push_back(3);
    A.push_back(2);
    A.push_back(10);
    A.push_back(10);
    A.push_back(10);
    A.push_back(-10);
    A.push_back(-10);
    A.push_back(7);
    A.push_back(3);
    Ms.push_back(10);
    Ms.push_back(9);
    Ms.push_back(-5);
    Ms.push_back(2);
    Ms.push_back(3);
    Ms.push_back(4);
    Ms.push_back(5);
    Ms.push_back(-10);
#endif
}

void solution(vector<INT>& A, const vector<INT>& Ms) {
    sort(A.begin(), A.end());
    for (const auto& iter : Ms) {
        INT cnt = 0L;
        const auto p = std::equal_range(A.begin(), A.end(), iter);
        for (auto i = p.first; i != p.second; ++i)
            cnt++;
        printf("%ld ", cnt);
    }
    printf("\n");
}

int main()
{
    vector<INT> A, Ms;
    input(A, Ms);
    solution(A, Ms);
    return 0;
}
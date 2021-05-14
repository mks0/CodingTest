/*
<숫자 카드 2, C++17>
[문제]
숫자 카드는 정수 하나가 적혀져 있는 카드이다. 상근이는 숫자 카드 N개를 가지고 있다. 정수 M개가 주어졌을 때, 이 수가 적혀있는 숫자 카드를 상근이가 몇 개 가지고 있는지 구하는 프로그램을 작성하시오.

[입력]
첫째 줄에 상근이가 가지고 있는 숫자 카드의 개수 N(1 ≤ N ≤ 500,000)이 주어진다. 둘째 줄에는 숫자 카드에 적혀있는 정수가 주어진다. 숫자 카드에 적혀있는 수는 -10,000,000보다 크거나 같고, 10,000,000보다 작거나 같다.

셋째 줄에는 M(1 ≤ M ≤ 500,000)이 주어진다. 넷째 줄에는 상근이가 몇 개 가지고 있는 숫자 카드인지 구해야 할 M개의 정수가 주어지며, 이 수는 공백으로 구분되어져 있다. 이 수도 -10,000,000보다 크거나 같고, 10,000,000보다 작거나 같다.

[출력]
첫째 줄에 입력으로 주어진 M개의 수에 대해서, 각 수가 적힌 숫자 카드를 상근이가 몇 개 가지고 있는지를 공백으로 구분해 출력한다.

[예제 입력 1]
10
6 3 2 10 10 10 -10 -10 7 3
8
10 9 -5 2 3 4 5 -10

[예제 출력 1] 
3 0 0 1 2 0 0 2
*/

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
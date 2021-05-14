#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//#define UNIT_TEST

vector<int> A;

void input() {
    int temp;
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &temp);
        A.push_back(temp);
    }
}

int TC01() {
    A.assign({10,20,10,30,20,50});
    return 4;
}

int TC02() {
    A.assign({10,20,40,25,20,50,30,70,85});
    return 6;
}

#ifndef UNIT_TEST
void solution() {
#else
void solution(const int answer) {
#endif
    vector<int> lis{0};     // using the constraints (1 <= A_i <= ...)
    for (const auto& iter : A) {
        if (lis.back() < iter)
            lis.push_back(iter);
        else
            *lower_bound(lis.begin(), lis.end(), iter) = iter;
    }
#ifndef UNIT_TEST
    printf("%d\n", static_cast<int>(lis.size()) - 1);
#else
    printf("%s\n", (lis.size() - 1 == answer) ? "Pass" : "Fail");
#endif
}

int main()
{
#ifndef UNIT_TEST
    input();
    solution();
#else
    solution(TC01());
    solution(TC02());
#endif
    return 0;
}
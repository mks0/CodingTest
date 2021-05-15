#include <iostream>
using namespace std;

int N, K;

void input() { scanf("%d %d", &N, &K); }
int TC01() { N = 3; K = 7; return 6;  }
int TC02() { N = 5; K = 8; return 4; }
int TC03() { N = 5; K = 13; return 8; }

//#define UNIT_TEST
//#define DEBUG_PRINT

#ifndef UNIT_TEST
void solution() {
#else
void solution(const int answer) {
#endif
    int left = 1;
    int right = K;
    while (left <= right) {
        const int mid = (left + right) / 2;
        int accK = 0;
        for (int i = 1; i <= N; ++i)
            accK += min(mid / i, N);
#ifdef DEBUG_PRINT
        printf("l:%d, m:%d, r:%d, accK:%d, K:%d, N:%d\n"
            , left, mid, right, accK, K, N);
#endif
        if (accK >= K)  right = mid - 1;
        else            left = mid + 1;
    }
#ifndef UNIT_TEST
    printf("%d\n", right + 1);
#else
    printf("%s, (answer:%d, print:%d)\n"
        , (answer == right + 1) ? "Pass" : "Fail"
        , answer, right + 1);
#endif
}

int main() {
#ifndef UNIT_TEST
    input();
    solution();
#else
    solution(TC01());
    solution(TC02());
    solution(TC03());
#endif
    return 0;
}
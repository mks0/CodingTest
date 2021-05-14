#include <iostream>
using namespace std;

//#define DEBUG_PRINT

const int maxN = 10000;
int reqBudget[maxN];
int N, M, Sum, MaxMoney;

void input() {
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &reqBudget[i]);
        Sum += reqBudget[i];
        MaxMoney = (reqBudget[i] > MaxMoney) ? reqBudget[i] : MaxMoney;
    }
    scanf("%d", &M);
}

void solution() {
    if (M >= Sum)    printf("%d\n", MaxMoney);
    else {
        int left = 0;
        int right = M * 2;
        while (left <= right) {
            const int mid = (left + right) / 2;
            int estBudget = 0;
            for (int i = 0; i < N; ++i)
                estBudget += (reqBudget[i] > mid) ? mid : reqBudget[i];
#ifdef DEBUG_PRINT
            printf("l:%d, m:%d, r:%d, M:%d, MaxMoney:%d, Sum:%d, est:%d\n",
                left, mid, right, M, MaxMoney, Sum, estBudget);
#endif
            if (estBudget > M) right = mid - 1;
            else left = mid + 1;
        }
        printf("%d\n", left - 1);
    }
}

void tc01() {   // result : 127
    N = 4;
    const int p[] = {120,110,140,150};
    for (int i = 0; i < N; ++i) {
        reqBudget[i] = p[i];
        Sum += reqBudget[i];
        MaxMoney = (reqBudget[i] > MaxMoney) ? reqBudget[i] : MaxMoney;
    }
    M = 485;
}

void tc02() {   // result : 497
    N = 100;
    const int p[] = {
        384,387,278,416,294,336,387,493,150,422,363,28,191,
        60,264,427,41,427,173,237,212,369,68,430,283,31,363,
        124,68,136,430,303,23,59,70,168,394,457,12,43,230,374,
        422,420,285,38,199,325,316,371,414,27,92,481,457,374,
        363,171,497,282,306,426,85,328,337,6,347,230,314,358,
        125,396,83,46,315,368,435,365,44,251,88,309,277,179,
        289,85,404,152,255,400,433,61,177,369,240,13,227,87,95,40};
    for (int i = 0; i < N; ++i) {
        reqBudget[i] = p[i];
        Sum += reqBudget[i];
        MaxMoney = (reqBudget[i] > MaxMoney) ? reqBudget[i] : MaxMoney;
    }
    M = 50000;
}

void tc03() {   // result : 41
    N = 10;
    const int p[] = {1,1,1,1,11,11,11,11,11,100};
    for (int i = 0; i < N; ++i) {
        reqBudget[i] = p[i];
        Sum += reqBudget[i];
        MaxMoney = (reqBudget[i] > MaxMoney) ? reqBudget[i] : MaxMoney;
    }
    M = 100;
}

void tc04() {   // result : 1
    N = 4;
    const int p[] = {2,2,2,2};
    for (int i = 0; i < N; ++i) {
        reqBudget[i] = p[i];
        Sum += reqBudget[i];
        MaxMoney = (reqBudget[i] > MaxMoney) ? reqBudget[i] : MaxMoney;
    }
    M = 7;
}

void tc05() {   // result : 9
    N = 6;
    const int p[] = {2,9,20,11,20,30};
    for (int i = 0; i < N; ++i) {
        reqBudget[i] = p[i];
        Sum += reqBudget[i];
        MaxMoney = (reqBudget[i] > MaxMoney) ? reqBudget[i] : MaxMoney;
    }
    M = 50;
}

void tc06() {   // result : 4
    N = 4;
    const int p[] = {4,3,2,1};
    for (int i = 0; i < N; ++i) {
        reqBudget[i] = p[i];
        Sum += reqBudget[i];
        MaxMoney = (reqBudget[i] > MaxMoney) ? reqBudget[i] : MaxMoney;
    }
    M = 10;
}

int main() {
    input();
    //tc06();
    solution();
    return 0;
}
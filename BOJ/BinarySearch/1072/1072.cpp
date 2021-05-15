#include <iostream>
#include <limits>
using namespace std;
using ll = long long;

void input(ll& X, ll& Y) { scanf("%lld %lld", &X, &Y); }
ll TC01(ll& X, ll& Y) { X = 10; Y = 8; return 1; }
ll TC02(ll& X, ll& Y) { X = 100; Y = 80; return 6; }
ll TC03(ll& X, ll& Y) { X = 47; Y = 47; return -1; }
ll TC04(ll& X, ll& Y) { X = 99000; Y = 0; return 1000; }
ll TC05(ll& X, ll& Y) { X = 1000000000LL; Y = 470000000LL; return 19230770LL; }
ll TC06(ll& X, ll& Y) { X = 1000000000LL; Y = 980000000LL; return 1000000000LL; }
ll TC07(ll& X, ll& Y) { X = 100; Y = 99; return -1; }

//#define UNIT_TEST
//#define DEBUG_PRINT

#ifndef UNIT_TEST
void solution(ll X, ll Y) {
#else
void solution(ll& X, ll& Y, const ll answer) {
#endif
    if ((X == Y) || (99LL == (Y * 100LL) / X)) {
#ifndef UNIT_TEST
        printf("-1\n");
#else
        printf("%s, answer:%lld, try:-1\n", (answer == -1) ? "Pass" : "Fail", answer);
#endif
    }
    else {
        ll initZ = (Y * 100LL) / X;
        ll left = 1LL;
        ll right = (numeric_limits<int>::max)();
        ll newZ;
        while (left <= right) {
            const ll mid = (left + right) / 2LL;
            newZ = ((Y + mid) * 100LL) / (X + mid);
#ifdef DEBUG_PRINT
            printf("l:%lld, m:%lld, r:%lld, initZ:%lld, newZ:%lld\n",
                left, mid, right, initZ, newZ);
#endif
            if (newZ <= initZ) left = mid + 1;
            else right = mid - 1;
        }
#ifndef UNIT_TEST
        printf("%lld\n", right + 1);
#else
        printf("%s, answer:%lld, try:%lld\n", (answer == right + 1) ? "Pass" : "Fail", answer, right + 1);
#endif
    }
}

int main() {
    ll X, Y;
#ifndef UNIT_TEST
    input(X, Y);
    solution(X, Y);
#else
    solution(X, Y, TC01(X, Y));
    solution(X, Y, TC02(X, Y));
    solution(X, Y, TC03(X, Y));
    solution(X, Y, TC04(X, Y));
    solution(X, Y, TC05(X, Y));
    solution(X, Y, TC06(X, Y));
    solution(X, Y, TC07(X, Y));
#endif
    return 0;
}
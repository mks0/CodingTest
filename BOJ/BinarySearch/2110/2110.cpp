#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using INT = int64_t;
//#define NO_CONSOLE
//#define DEBUG_PRINT

void input(INT& C, vector<INT>& X) {
    INT N;
    INT temp;
#ifndef NO_CONSOLE
    scanf("%ld %ld", &N, &C);
    for (INT i = 0L; i < N; ++i) {
        scanf("%ld", &temp);
        X.push_back(temp);
    }
#else
#define SAMPLE  8
#if SAMPLE == 1
	C = 3;  X.assign({1,2,8,4,9});  // result : 3
#elif SAMPLE == 2
    C = 3;  X.assign({1,3,5,7});  // result : 2
#elif SAMPLE == 3
    C = 2;  X.assign({5,6});  // result : 1
#elif SAMPLE == 4
    C = 3;  X.assign({100,101,102,103,104});    // result : 2
#elif SAMPLE == 5
    C = 2;  X.assign({6,7,8});  // result : 2
#elif SAMPLE == 6
    C = 3;  X.assign({1,6,7,8,9});  // result : 3
#elif SAMPLE == 7
    C = 2;  X.assign({1,2,8,4,9});  // result : 8
#else
    // result : 6
    C = 3;  X.assign({1000000000,999999996,999999991,999999985});
#endif
#endif
}

void solution(const INT targetCnt, vector<INT>& X) {
    sort(X.begin(), X.end());
    INT left = 1;
	INT right = X.back() - X.front();
	INT mid;
	while (left <= right) {
		mid = (left + right) / 2L;
		INT possibleCnt = 1L;
		int prevIdx = 0;
		for (int i = 1; i < X.size(); ++i) {
			if (X[i] - X[prevIdx] >= mid) {
				possibleCnt++;
				prevIdx = i;
			}
		}
#ifdef DEBUG_PRINT
		printf("l:%ld, m:%ld, r:%ld, accC:%ld, C:%ld\n",
		    left, mid, right, possibleCnt, targetCnt);
#endif
		
		if (possibleCnt < targetCnt) right = mid - 1;
		else left = mid + 1;
	}
	printf("%ld\n", left - 1);
}

int main()
{
	INT C;
    vector<INT> X;
    input(C, X);
    solution(C, X);
    return 0;
}
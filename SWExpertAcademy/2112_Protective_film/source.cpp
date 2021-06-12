#include <iostream>
using namespace std;

enum CHK { A, B, MIX };
int D, W, K;
int m[13][20];
CHK check[13];

void Input() {
	scanf("%d %d %d", &D, &W, &K);
	for (int i = 0; i < D; ++i) {
		check[i] = MIX;
		for (int j = 0; j < W; ++j) {
			scanf("%d", &m[i][j]);
		}
	}
}

inline bool IsOK() {
	for (int j = 0; j < W; ++j) {
		int prev = (MIX == check[0]) ? m[0][j] : check[0];
		int cnt = 1;
		for (int i = 1; i < D; ++i) {
			if (K <= cnt) break;
			const auto cmp = (MIX == check[i]) ? m[i][j] : check[i];
			if (cmp == prev) cnt++;
			else {
				prev = cmp;
				cnt = 1;
			}
		}
		if (K > cnt) return false;
	}
	return true;
}

int answer;

void DFS(int tryPos, int tryCnt) {
	if (tryCnt >= answer) return;
	if (tryPos == D) {
		if (!IsOK()) return;
		answer = min(answer, tryCnt);
		return;
	}
	DFS(tryPos + 1, tryCnt);
	check[tryPos] = A;
	DFS(tryPos + 1, tryCnt + 1);
	check[tryPos] = B;
	DFS(tryPos + 1, tryCnt + 1);
	check[tryPos] = MIX;
}

int Solution() {
	if (1 >= K) return 0;
	answer = K;
	DFS(0, 0);
	return answer;
}

int main(int argc, char** argv) {
	int T;
	freopen("sample_input.txt", "r", stdin);
	scanf("%d", &T);

	for (int test_case = 1; test_case <= T; ++test_case) {
		Input();
		printf("#%d %d\n", test_case, Solution());
	}
	return 0;
}
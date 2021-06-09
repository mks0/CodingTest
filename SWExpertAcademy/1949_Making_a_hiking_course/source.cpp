#include <iostream>
#include <vector>
#include <bitset>
#include <unordered_map>
using namespace std;

enum DIR { UP, DOWN, LEFT, RIGHT };
inline DIR GetOpposite(int dir) {
	return static_cast<DIR>((1 == dir % 2) ? dir - 1 : dir + 1);
}
const int di[] = { -1, 1, 0, 0 };
const int dj[] = { 0, 0, -1, 1 };
struct Pos { int i, j; };

const int MaxN = 8;
int N, K;
int map[MaxN][MaxN];
unordered_map<int, vector<Pos>> startPos;
bitset<MaxN*MaxN> visited;
int answer;

inline int GetKey(int i, int j) {
	return i * MaxN + j;
}
inline bool IsOverMap(int i, int j) {
	return (0 > i) || (0 > j) || (i >= N) || (j >= N);
}
inline bool IsVisited(int i, int j) {
	return visited.test(GetKey(i, j));
}
inline bool IsBigger(int i, int j, int prev) {
	return prev <= map[i][j];
}

int Input() {
	int bestHeight = -1;
	startPos.clear();
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			scanf("%d", &map[i][j]);
			if (bestHeight <= map[i][j]) {
				bestHeight = map[i][j];
				startPos[bestHeight].push_back({ i,j });
			}
		}
	}
	return bestHeight;
}

void DFS(const int _i, const int _j, const DIR dir, int prev, const int cnt, int k) {
	const int i = _i + di[dir];
	const int j = _j + dj[dir];
	if (IsOverMap(i, j)) return;
	if (IsVisited(i, j)) return;
	if (IsBigger(i, j, prev)) {
		if (0 == k) return;
		if (k <= map[i][j] - prev) return;
		k = 0;
		--prev;
	}
	else prev = map[i][j];

	visited.set(GetKey(i,j));
	answer = max(answer, cnt + 1);
	const auto oppo = GetOpposite(dir);
	for (int z = UP; z <= RIGHT; ++z) {
		if (oppo == z) continue;
		DFS(i, j, static_cast<DIR>(z), prev, cnt + 1, k);
	}
	visited.reset(GetKey(i,j));
}

int Solution(const int bestHeight) {
	answer = 0;
	for (const auto& iter : startPos[bestHeight]) {
		visited.set(GetKey(iter.i, iter.j));
		for (int z = UP; z <= RIGHT; ++z)
			DFS(iter.i, iter.j, static_cast<DIR>(z), bestHeight, 1, K);
		visited.reset(GetKey(iter.i, iter.j));
	}
	return answer;
}

int main(int argc, char** argv) {
	int T;
	freopen("sample_input.txt", "r", stdin);
	scanf("%d", &T);
	for (int test_case = 1; test_case <= T; ++test_case)
		printf("#%d %d\n", test_case, Solution(Input()));
	return 0;
}
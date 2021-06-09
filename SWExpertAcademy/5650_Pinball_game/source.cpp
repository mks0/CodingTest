#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

enum DIR { UP, DOWN, LEFT, RIGHT };
const int di[] = { -1, 1, 0, 0 };
const int dj[] = { 0, 0, -1, 1 };
struct Pos {
	bool operator==(const Pos& rhs) const { return i == rhs.i && j == rhs.j; }
	Pos operator+(const int dir) const {
		Pos pos{ i, j };
		pos.i += di[dir];
		pos.j += dj[dir];
		return pos;
	}
	int i, j;
};

////////////////// ◺,  ◸, ◹,  ◿,  ◻,
enum BLOCK { NONE, UR, DR, DL, UL, ALL, WORM6, WORM7, WORM8, WORM9, WORM10, BHOLE = -1  };
const DIR EnterBlk[][RIGHT + 1] = {
/**/	{   UP,  DOWN,  LEFT, RIGHT},
/*◺*/	{ DOWN, RIGHT,    UP,  LEFT},
/*◸*/	{RIGHT,    UP,  DOWN,  LEFT},
/*◹*/	{ LEFT,    UP, RIGHT,  DOWN},
/*◿*/	{ DOWN,  LEFT, RIGHT,    UP},
/*◻*/	{ DOWN,    UP, RIGHT,  LEFT}
};

const int MaxN = 100;
unordered_map<int, vector<Pos>> portal;
int m[MaxN][MaxN];
int N;

inline bool IsOut(const Pos& pos) {
	return 0 > pos.i || 0 > pos.j || pos.i >= N || pos.j >= N;
}

void Input() {
	portal.clear();
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			scanf("%d", &m[i][j]);
			if (WORM6 <= m[i][j])
				portal[m[i][j]].push_back({ i,j });
		}
	}
}

int Simulation(const Pos initPos, int dir) {
	int result = 0;
	Pos pos(initPos);
	while (true) {
		auto nextPos = pos + dir;
		if (BHOLE == m[nextPos.i][nextPos.j]) break;
		else if (IsOut(nextPos)) {
			pos = nextPos;
			dir = EnterBlk[ALL][dir];
			result++;
		}
		else if (NONE == m[nextPos.i][nextPos.j]) pos = nextPos;
		else if (WORM6 > m[nextPos.i][nextPos.j]) {
			pos = nextPos;
			dir = EnterBlk[m[nextPos.i][nextPos.j]][dir];
			result++;
		}
		else {
			pos = (nextPos == portal[m[nextPos.i][nextPos.j]][0])
				? portal[m[nextPos.i][nextPos.j]][1]
				: portal[m[nextPos.i][nextPos.j]][0];
		}
		if (initPos == pos) break;
	}
	return result;
}

int Solution() {
	int maxer = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (NONE == m[i][j]) {
				for (int dir = UP; dir <= RIGHT; ++dir) {
					auto temp = Simulation({ i, j }, dir);
					maxer = max(temp, maxer);
				}
			}
		}
	}
	return maxer;
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
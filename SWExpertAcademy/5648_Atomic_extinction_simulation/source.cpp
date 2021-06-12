#include <iostream>
#include <unordered_map>	// for Solution_umap()
using namespace std;

enum DIR { UP, DOWN, LEFT, RIGHT };
const int dx[] = { 0,  0, -1, 1 };
const int dy[] = { 1, -1,  0, 0 };
struct Pos {
	void Next(const int dir) {
		x += dx[dir];
		y += dy[dir];
	}
	int x, y;
};

struct Atom {
	Pos pos;
	int dir, K;
	bool die;
};

const int MaxMapSize = 4000;
const int MaxAtomCnt = 1000;
Atom atoms[MaxAtomCnt];
int N;

uint32_t* conflicts[2];		// //uint32_t conflicts[2][MaxMapSize * MaxMapSize + MaxMapSize];
uint32_t timeSeq = 1U;

inline int GetIndex(const int x, const int y) {
	return x * MaxMapSize + y;
}
inline bool IsMapOut(const int x, const int y) {
	return 0 > x || 0 > y || x >= MaxMapSize || y >= MaxMapSize;
}

void Input() {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		scanf("%d %d %d %d", &atoms[i].pos.x, &atoms[i].pos.y, &atoms[i].dir, &atoms[i].K);
		atoms[i].pos.x = 2 * atoms[i].pos.x + MaxMapSize / 2;
		atoms[i].pos.y = 2 * atoms[i].pos.y + MaxMapSize / 2;
		atoms[i].die = false;
	}
}

int Solution_umap() {
	int result = 0;
	int remainAtoms = N;
	while (1 < remainAtoms) {
		unordered_map<int, int> conflict;
		for (int i = 0; i < N; ++i) {
			if (atoms[i].die) continue;

			atoms[i].pos.Next(atoms[i].dir);

			if (IsMapOut(atoms[i].pos.x, atoms[i].pos.y)) {
				atoms[i].die = true;
				remainAtoms--;
				continue;
			}

			const auto key = GetIndex(atoms[i].pos.x, atoms[i].pos.y);
			if (conflict.find(key) != conflict.end()) {
				if (!atoms[conflict[key]].die) {
					result += atoms[conflict[key]].K;
					atoms[conflict[key]].die = true;
					remainAtoms--;
				}
				result += atoms[i].K;
				atoms[i].die = true;
				remainAtoms--;
			}
			else {
				conflict[key] = i;
			}
		}
	}
	return result;
}

int Solution() {
	int result = 0;
	int remainAtoms = N;
	while (1 < remainAtoms) {
		for (int i = 0; i < N; ++i) {
			if (atoms[i].die) continue;

			atoms[i].pos.Next(atoms[i].dir);

			if (IsMapOut(atoms[i].pos.x, atoms[i].pos.y)) {
				atoms[i].die = true;
				remainAtoms--;
				continue;
			}

			const auto key = GetIndex(atoms[i].pos.x, atoms[i].pos.y);
			if (conflicts[0][key] == timeSeq) {
				if (!atoms[conflicts[1][key]].die) {
					result += atoms[conflicts[1][key]].K;
					atoms[conflicts[1][key]].die = true;
					remainAtoms--;
				}
				result += atoms[i].K;
				atoms[i].die = true;
				remainAtoms--;
			}
			else {
				conflicts[0][key] = timeSeq;
				conflicts[1][key] = i;
			}
		}
		timeSeq++;
	}
	return result;
}

int main(int argc, char** argv) {
	int T;
	freopen("sample_input.txt", "r", stdin);
	scanf("%d", &T);

	// 아래 동적할당은 Solution_umap() 사용시에는 필요 없음
	conflicts[0] = (uint32_t*)malloc(sizeof(uint32_t) * MaxMapSize * MaxMapSize + MaxMapSize);
	conflicts[1] = (uint32_t*)malloc(sizeof(uint32_t) * MaxMapSize * MaxMapSize + MaxMapSize);
	for (int test_case = 1; test_case <= T; ++test_case) {
		Input();
		printf("#%d %d\n", test_case, Solution());
	}
	return 0;
}
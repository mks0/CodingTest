#include <iostream>
#include <cmath>
using namespace std;

struct Pos { int i, j; };
int mapSize, money, homeCnt;
Pos home[400];

inline int GetCost(const int k) { return k * k + (k - 1) * (k - 1); }
inline int GetDist(const Pos& pos1, const Pos& pos2) { return abs(pos1.i - pos2.i) + abs(pos1.j - pos2.j); }

void Input() {
	scanf("%d %d", &mapSize, &money);
	homeCnt = 0;
	for (int i = 0; i < mapSize; ++i) {
		for (int j = 0; j < mapSize; ++j) {
			int temp;
			scanf("%d", &temp);
			if (temp) {
				home[homeCnt].i = i;
				home[homeCnt++].j = j;
			}
		}
	}
}

int Solution() {
	int result = 0;
	for (int k = 1; k <= mapSize + 1; ++k) {
		const int cost = GetCost(k);
		for (int i = 0; i < mapSize; ++i) {
			for (int j = 0; j < mapSize; ++j) {
				int inCount = 0;
				for (int z = 0; z < homeCnt; ++z)
					if (k > GetDist({ i, j }, home[z]))
						++inCount;
				if (cost <= inCount * money)
					result = max(result, inCount);
			}
		}
	}
	return result;
}

int main(int argc, char** argv) {
	int T;
	//freopen("sample_input.txt", "r", stdin);
	scanf("%d", &T);
	for (int test_case = 1; test_case <= T; ++test_case) {
		Input();
		printf("#%d %d\n", test_case, Solution());
	}
	return 0;
}
#include <iostream>
#include <deque>
using namespace std;

enum DIR { UP, DOWN, LEFT, RIGHT };
const int di[] = { -1,  1,  0,  0 };
const int dj[] = {  0,  0, -1,  1 };
struct Pos { int i, j; };
class Cell {
public:
	inline void Init(const int _x) noexcept {
		x = deactTime = actTime = _x;
		executed = false;
	}
	inline bool Advance() noexcept {
		if (0 < deactTime) {
			--deactTime;
			return false;
		}
		if (0 < actTime) {
			--actTime;
			if (x == actTime + 1) {
				return true;
			}
		}
		return false;
	}
	inline bool IsAlive() const noexcept {
		return IsExist() && (0 < actTime + deactTime);
	}
	inline bool IsNew() const noexcept {
		return !executed && IsExist() && (x == deactTime);
	}
	inline bool IsExist() const noexcept {
		return x > 0;
	}
	int x;
	bool executed;
private:
	int deactTime, actTime;
};

static const int offset = 201;
static const int mapSize = offset * 2;
static Cell map[mapSize][mapSize];
static int row, col, simTime;
static deque<Pos> runQ;
inline void Reset() {
	for (int i = 0; i < mapSize; ++i)
		for (int j = 0; j < mapSize; ++j) map[i][j].Init(0);
	runQ.clear();
}

inline void debug(const int t) {
	const int stds = 14;
	for (int i = offset - stds; i < offset + stds; ++i) {
		for (int j = offset - stds; j < offset + stds; ++j)
			printf("%d ", map[i][j].IsAlive() ? map[i][j].x : 0);
		printf("\n");
	}
	printf("after %d H\n\n", t+1);
}

void Input() {
	scanf("%d %d %d", &row, &col, &simTime);
	for (int i = 0 + offset; i < row + offset; ++i) {
		for (int j = 0 + offset; j < col + offset; ++j) {
			int temp;
			scanf("%d", &temp);
			if (0 < temp) {
				map[i][j].Init(temp);
				runQ.push_back({ i,j });
			}
		}
	}
}

int Solution() {
	for (int times = 0; times < simTime; ++times) {
		deque<Pos> tempQ;
		while (!runQ.empty()) {
			auto &top = runQ.front();
			if (map[top.i][top.j].IsAlive()) {
				if (map[top.i][top.j].Advance()) {
					for (int i = UP; i <= RIGHT; ++i) {
						auto ni = top.i + di[i];
						auto nj = top.j + dj[i];
						if (map[ni][nj].IsNew()) {
							if (map[ni][nj].x < map[top.i][top.j].x)
								map[ni][nj].Init(map[top.i][top.j].x);
						}
						else if (!map[ni][nj].IsExist()) {
							map[ni][nj].Init(map[top.i][top.j].x);
							tempQ.push_back({ ni, nj });
						}
					}
				}
				if (map[top.i][top.j].IsAlive())
					tempQ.push_back(top);
			}
			runQ.pop_front();
		}
		swap(runQ, tempQ);
		for (auto& iter : runQ) {
			map[iter.i][iter.j].executed = true;
		}
		//debug(times);
	}
	//printf("\n");
	return runQ.size();
}

int main(int argc, char** argv) {
	int T;
	freopen("sample_input.txt", "r", stdin);
	scanf("%d", &T);
	for (int test_case = 1; test_case <= T; ++test_case) {
		Reset();
		Input();
		printf("#%d %d\n", test_case, Solution());
	}
	return 0;
}
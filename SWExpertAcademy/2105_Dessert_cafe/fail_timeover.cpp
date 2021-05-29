#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

int N;

enum DIR { NONE, RD, LD, LU, RU };
const int dx[] = { 0, 1,  1, -1, -1 };
const int dy[] = { 0, 1, -1, -1,  1 };
struct Pos {
	Pos(const int _sx, const int _sy, const DIR _next, const set<int>& _s)
		: init_x(_sx), init_y(_sy), x(_sx), y(_sy), next(_next), s(_s) {}
	const int init_x, init_y;
	int x, y;
	DIR next;
	set<int> s;
};
bool IsPossibleRUGo(const Pos& pos) {
	int x = pos.x;
	int y = pos.y;
	do {
		x += dx[RU];
		y += dy[RU];
		if (pos.init_x == x && pos.init_y == y) return true;
	} while (0 <= x && 0 <= y && N > x && N > y);
	return false;
}
bool IsPossibleNext(const Pos& pos, const DIR next, const vector<vector<int>>& m) {
	if (NONE == next) return false;
	auto nx = pos.x + dx[next];
	auto ny = pos.y + dy[next];
	if (0 > nx || 0 > ny || N <= nx || N <= ny) return false;
	if (pos.s.end() != pos.s.find(m[nx][ny])) return false;
	return true;
}
int main(int argc, char** argv) {
	int test_case, T;
	freopen("sample_input.txt", "r", stdin);
	scanf("%d", &T);
	for (test_case = 1; test_case <= T; ++test_case) {
		scanf("%d", &N);
		vector<vector<int>> m(N);
		for (int x = 0; x < N; ++x) {
			for (int y = 0; y < N; ++y) {
				int temp;
				scanf("%d", &temp);
				m[x].push_back(temp);
			}
		}

		int result = -1;
		queue<Pos> q;
		for (int i = 1; i < N - 1; ++i) {
			for (int j = 0; j < N - 2; ++j) {
				q.push(Pos(j, i, NONE, { m[j][i] }));
			}
		}
		while (!q.empty()) {
			auto top = q.front();
			if (top.x + dx[RU] == top.init_x && top.y + dy[RU] == top.init_y)
				result = max(result, static_cast<int>(top.s.size()));

			if (NONE == top.next && IsPossibleNext(top, RD, m)) {
				top.next = RD;
				top.x += dx[top.next];
				top.y += dy[top.next];
				top.s.insert(m[top.x][top.y]);
				q.push(top);
			}
			else if (RD == top.next) {
				if (N - 1 > top.y && N - 2 > top.x && IsPossibleNext(top, RD, m)) {
					auto cp = top;
					cp.x += dx[top.next];
					cp.y += dy[top.next];
					cp.s.insert(m[cp.x][cp.y]);
					q.push(cp);
				}
				if (1 < top.y && N - 1 > top.x && IsPossibleNext(top, LD, m)) {
					top.next = LD;
					top.x += dx[top.next];
					top.y += dy[top.next];
					top.s.insert(m[top.x][top.y]);
					q.push(top);
				}
			}
			else if (LD == top.next) {
				if (1 < top.y && N - 1 > top.x && IsPossibleNext(top, LD, m)) {
					auto cp = top;
					cp.x += dx[top.next];
					cp.y += dy[top.next];
					cp.s.insert(m[cp.x][cp.y]);
					q.push(cp);
				}
				if (0 < top.y && 1 < top.x && IsPossibleNext(top, LU, m)) {
					top.next = LU;
					top.x += dx[top.next];
					top.y += dy[top.next];
					top.s.insert(m[top.x][top.y]);
					q.push(top);
				}
			}
			else if (LU == top.next) {
				if (0 < top.y && 1 < top.x && IsPossibleNext(top, LU, m)) {
					auto cp = top;
					cp.x += dx[top.next];
					cp.y += dy[top.next];
					cp.s.insert(m[cp.x][cp.y]);
					q.push(cp);
				}
				if (N - 1 > top.y && 1 < top.x && IsPossibleNext(top, RU, m)) {
					top.next = RU;
					top.x += dx[top.next];
					top.y += dy[top.next];
					top.s.insert(m[top.x][top.y]);
					q.push(top);
				}
			}
			else {
				if (IsPossibleRUGo(top) && IsPossibleNext(top, RU, m)) {
					top.x += dx[top.next];
					top.y += dy[top.next];
					top.s.insert(m[top.x][top.y]);
					q.push(top);
				}
			}
			q.pop();
		}
		printf("#%d %d\n", test_case, result);
	}
	return 0;
}
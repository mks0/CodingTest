#include <iostream>
#include <bitset>
using namespace std;

int N;
int map[20][20] = { 0, };
enum DIR {RD,LD,LU,RU};
const int di[] = {1, 1,-1,-1};
const int dj[] = {1,-1,-1, 1};
bitset<101> visited;
int si, sj;
int result;

#define	IsMapOut(i,j)		(!(0 <= (i) && N > (i) && 0 <= (j) && N > (j)))
#define	IsOverturn(dir)		(RU < (dir))
#define	IsSameDessert(i,j)	(0 != visited[map[(i)][(j)]])
#define	IsCycled(i,j,dir)	((i) == si && (j) == sj && RU == (dir))

void Input() {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			scanf("%d", &map[i][j]);
}

void DFS(const int _i, const int _j, const int count, const int dir) {
	const int i = _i + di[dir];
	const int j = _j + dj[dir];

	if (IsMapOut(i, j)) return;
	if (IsSameDessert(i, j)) return;
	if (IsCycled(i, j, dir)) result = max(result, count);

	visited.set(map[i][j]);
	DFS(i, j, count + 1, dir);
	DFS(i, j, count + 1, dir + 1);
	visited.reset(map[i][j]);
}

int main(int argc, char** argv) {
	int T;
	freopen("sample_input.txt", "r", stdin);
	scanf("%d", &T);
	for (int test_case = 1; test_case <= T; ++test_case) {
		Input();
		result = -1;
		visited.reset();
		for (int i = 0; i < N - 2; ++i) {
			for (int j = 1; j < N - 1; ++j) {
				si = i; sj = j;
				DFS(i, j, 1, static_cast<int>(RD));
			}
		}
		printf("#%d %d\n", test_case, result);
	}
	return 0;
}
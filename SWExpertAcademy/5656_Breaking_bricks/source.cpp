#include <iostream>
#include <queue>
using namespace std;

enum DIR { LEFT, RIGHT, UP, DOWN };
const int dx[] = {0, 0, 1, -1};
const int dy[] = {-1, 1, 0, 0};
struct Pos {
    Pos(const int _x, const int _y, const int _range) : x(_x), y(_y), range(_range), valid(true) {}
	int x, y, range;
    bool valid;
};
class World {
public:
    World(const int width, const int height) : w(width), h(height), m(h) { for (auto& iter : m) iter.resize(w); }
    void throwBall(const int row) {
        queue<Pos> next;
        for (int i = h - 1; i >= 0; --i) {
            if (0 != m[i][row]) {
                next.push(Pos(i, row, m[i][row]));
                m[i][row] = 0;
                break;
            }
        }
        while (!next.empty()) {
            auto top = next.front();
            Pos p[DOWN + 1] = {top, top, top, top};
            for (int i = top.range; i > 1; --i) {
                for (int j = LEFT; j <= DOWN; ++j) {
                    if (p[j].valid &&
                        0 <= p[j].x + dx[j] && h > p[j].x + dx[j] &&
                        0 <= p[j].y + dy[j] && w > p[j].y + dy[j]) {
                        p[j].x += dx[j];
                        p[j].y += dy[j];
                        if (0 != m[p[j].x][p[j].y]) {
                            next.push(Pos(p[j].x, p[j].y, m[p[j].x][p[j].y]));
                            m[p[j].x][p[j].y] = 0;
                        }
                    }
                    else p[j].valid = false;
                }
            }
            next.pop();
        }
        arrangeMap();
    }
    int getBlockCount() const {
        int cnt = 0;
        for (int y = 0; y < w; ++y) {
            for (int x = 0; x < h; ++x) {
            	if (0 == m[x][y]) break;
                cnt++;
            }
        }
        return cnt;
    }
    bool isValid(const int row) const {
        for (int i = h - 1; i >= 0; --i) if (0 != m[i][row]) return true;
        return false;
    }
    const int w;
    const int h;
    vector<vector<int>> m;
    
    void print() {
        printf("%d %d\n", w, h);
        for (int i = m.size() - 1; i >= 0; --i) {
            for (int j = 0; j < m[i].size(); ++j)
                printf("%d ", m[i][j]);
            printf("\n");
        }
    }
private:
    void arrangeMap() {
        for (int col = 0; col < w; ++col) {
        	queue<int> emptyIdx;
            for (int row = 0; row < h; ++row) {
            	if (0 == m[row][col]) emptyIdx.push(row);
                else {
                    if (!emptyIdx.empty()) {
                        swap(m[emptyIdx.front()][col], m[row][col]);
                        emptyIdx.pop();
                        emptyIdx.push(row);
                    }
                }
            }
        }
    }
};

int main(int argc, char** argv) {
	int test_case, T;
	scanf("%d", &T);
	for(test_case = 1; test_case <= T; ++test_case) {
		int N, W, H;
        scanf("%d %d %d", &N, &W, &H);
        World world(W, H);
        for (int i = H - 1; i >= 0; --i) {
        	for (int j = 0; j < W; ++j) {
                int temp;
                scanf("%d", &temp);
                world.m[i][j] = temp;
            }
        }
        
        queue<pair<World,int>> q;
        q.push(make_pair(world, 0));
        auto result = world.getBlockCount();
        while (!q.empty()) {
            auto top = q.front();
            if (top.second >= N) break;
            for (int i = 0; i < W; ++i) {
                if (top.first.isValid(i)) {
                    World cpyWorld(top.first);
                    cpyWorld.throwBall(i);
                    result = min(cpyWorld.getBlockCount(), result);
                    q.push(make_pair(cpyWorld, top.second + 1));
                }
            }
            q.pop();
        }
        printf("#%d %d\n", test_case, result);
	}
	return 0;
}
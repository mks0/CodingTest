#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int MAX_N = 25;
int map[MAX_N][MAX_N] = { 0, };
int N;

enum DIR { UP, DOWN, LEFT, RIGHT };
class Coord {
public:
    Coord(const int x, const int y, const int n) : _x(x), _y(y), _n(n) {}
    inline int GetX() const noexcept { return _x; }
    inline int GetY() const noexcept { return _y; }
    bool IsMovable(const DIR dir) const noexcept {
        switch (dir) {
        case UP:    return _y > 0;
        case DOWN:  return _y < _n - 1;
        case LEFT:  return _x > 0;
        case RIGHT: return _x < _n - 1;
        default:    return false;
        }
    }
    Coord Move(const DIR dir) const noexcept {
        Coord cpy(*this);
        switch (dir) {
        case UP:    cpy._y--; break;
        case DOWN:  cpy._y++; break;
        case LEFT:  cpy._x--; break;
        case RIGHT: cpy._x++; break;
        default:              break;
        }
        return cpy;
    }
private:
    int _x, _y;
    const int _n;
};

//#define UNIT_TEST
#ifdef  UNIT_TEST
vector<int> TC01_input() {
    memset(map, 0, sizeof(map));
    N = 7;
    int rows[][7] = {{0,1,1,0,1,0,0}
                    ,{0,1,1,0,1,0,1}
                    ,{1,1,1,0,1,0,1}
                    ,{0,0,0,0,1,1,1}
                    ,{0,1,0,0,0,0,0}
                    ,{0,1,1,1,1,1,0}
                    ,{0,1,1,1,0,0,0}};
    for (int i = 0; i < N; ++i) memcpy(map[i], rows[i], sizeof(rows[i]));
    return { 3,7,8,9 };
}
vector<int> TC02_input() {
    memset(map, 0, sizeof(map));
    N = 5;
    int rows[][5] = { {0,1,1,0,1}
                    ,{0,1,1,0,1}
                    ,{1,1,1,0,0}
                    ,{0,0,0,1,1}
                    ,{0,0,1,0,0} };
    for (int i = 0; i < N; ++i) memcpy(map[i], rows[i], sizeof(rows[i]));
    return { 4,1,2,2,7 };
}
vector<int> TC03_input() {
    memset(map, 0, sizeof(map));
    N = 4;
    int rows[][4] = {{1,0,1,0}
                    ,{0,1,0,1}
                    ,{1,0,1,0}
                    ,{0,1,0,1}};
    for (int i = 0; i < N; ++i) memcpy(map[i], rows[i], sizeof(rows[i]));
    return { 8,1,1,1,1,1,1,1,1 };
}
#else
void input() {
    scanf("%d", &N);
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            scanf("%1d", &map[i][j]);
}
#endif

int BFS(const int x, const int y) {
    queue<Coord> q;
    q.push(Coord(x, y, N));
    int count = 0;
    if (0 != map[x][y]) {
        map[x][y] = 0;
        ++count;
    }

    while (!q.empty()) {
        const auto& top = q.front();
        for (int i = UP; i <= RIGHT; ++i) {
            if (top.IsMovable(static_cast<DIR>(i))) {
                auto temp = top.Move(static_cast<DIR>(i));
                auto tmpX = temp.GetX();
                auto tmpY = temp.GetY();
                if (0 != map[tmpX][tmpY]) {
                    map[tmpX][tmpY] = 0;
                    q.push(temp);
                    ++count;
                }
            }
        }
        q.pop();
    }
    return count;
}

#ifdef  UNIT_TEST
void solution(const vector<int>& answer) {
#else
void solution() {
#endif
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (0 != map[i][j])
                pq.push(BFS(i,j));
        }
    }

    vector<int> v{ 0 };
    while (!pq.empty()) {
        v.push_back(pq.top());
        pq.pop();
        v[0]++;
    }

#ifdef  UNIT_TEST
    printf("%s\n", (answer == v) ? "Pass" : "Fail");
#endif
    for (const auto iter : v)
        printf("%d\n", iter);
}

int main() {
#ifdef  UNIT_TEST
    solution(TC01_input());
    solution(TC02_input());
    solution(TC03_input());
#else
    input();
    solution();
#endif
    return 0;
}
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

class Map {
public:
    Map(const int _row, const int _col)
        : map{ 0, }
        , row(_row)
        , col(_col) {}
    static const int MAP_SIZE = 101;
    int map[MAP_SIZE][MAP_SIZE];
    const int row;
    const int col;
};

Map* gMap = nullptr;

class Pos {
public:
    Pos(const int _x, const int _y, Map& _rMap)
        : x(_x)
        , y(_y)
        , rMap(_rMap) {}
    Pos operator+(const Pos& rhs) const {
        return Pos(x + rhs.x, y + rhs.y, rhs.rMap);
    }
    bool IsValidAndReset(const Pos& rhs) const {
        if (((x + rhs.x) > 0) &&
            ((x + rhs.x) <= rMap.row) &&
            ((y + rhs.y) > 0) &&
            ((y + rhs.y) <= rMap.col) &&
            (1 == rMap.map[x + rhs.x][y + rhs.y])) {
            rMap.map[x + rhs.x][y + rhs.y] = 0;
            return true;
        }
        else return false;
    }
    int x, y;
    Map& rMap;
};

//#define UNIT_TEST
#ifdef  UNIT_TEST
int TC01_input() {
    gMap = new Map(4, 6);
    int lMap[][6] = { {1,0,1,1,1,1}
                    ,{1,0,1,0,1,0}
                    ,{1,0,1,0,1,1}
                    ,{1,1,1,0,1,1} };
    for (int i = 0; i < gMap->row; ++i)
        memcpy(&gMap->map[i + 1][1], lMap[i], sizeof(int) * gMap->col);
    return 15;
}
#else
void input() {
    int N, M;
    scanf("%d %d", &N, &M);
    gMap = new Map(N, M);
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= M; ++j)
            scanf("%1d", &gMap->map[i][j]);
}
#endif

#ifdef  UNIT_TEST
void solution(const int answer) {
#else
void solution() {
#endif
    Pos UP(-1, 0, *gMap);
    Pos DOWN(1, 0, *gMap);
    Pos LEFT(0, -1, *gMap);
    Pos RIGHT(0, 1, *gMap);

    queue<pair<Pos, int>> q;
    q.push(make_pair(Pos(1, 1, *gMap), 1));
    q.front().first.IsValidAndReset(Pos(0, 0, *gMap));

    while (!q.empty()) {
        auto top = q.front();
        if ((top.first.x == top.first.rMap.row) &&
            (top.first.y == top.first.rMap.col)) break;

        if (top.first.IsValidAndReset(UP))
            q.push(make_pair(top.first + UP, top.second + 1));
        if (top.first.IsValidAndReset(DOWN))
            q.push(make_pair(top.first + DOWN, top.second + 1));
        if (top.first.IsValidAndReset(LEFT))
            q.push(make_pair(top.first + LEFT, top.second + 1));
        if (top.first.IsValidAndReset(RIGHT))
            q.push(make_pair(top.first + RIGHT, top.second + 1));
        q.pop();
    }
#ifdef  UNIT_TEST
    printf("%s\n", (answer == q.front().second) ? "Pass" : "Fail");
#endif
    printf("%d\n", q.front().second);
}

int main() {
#ifdef  UNIT_TEST
    solution(TC01_input());
#else
    input();
    solution();
#endif
    return 0;
}
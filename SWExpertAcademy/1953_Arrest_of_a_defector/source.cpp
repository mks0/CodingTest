#include <iostream>
#include <vector>
#include <queue>
using namespace std;

enum DIR {LEFT,RIGHT,UP,DOWN};
const int dx[] = {0,0,-1,1};
const int dy[] = {-1,1,0,0};
struct Pos { Pos(const int _x, const int _y) : x(_x), y(_y) {} int x,y; };

enum BLOCK_TYPE {NONE,CROSS,UD,LR,RU,RD,LD,LU};

class Block {
public:
    Block() : bType(NONE), visited(false), dir{false,} {}
    void Init(const int blockType) {
        bType = static_cast<BLOCK_TYPE>(blockType);
        if (CROSS == bType || LR == bType || LD == bType || LU == bType) dir[LEFT] = true;
        if (CROSS == bType || LR == bType || RU == bType || RD == bType) dir[RIGHT] = true;
        if (CROSS == bType || UD == bType || LU == bType || RU == bType) dir[UP] = true;
        if (CROSS == bType || UD == bType || LD == bType || RD == bType) dir[DOWN] = true;
    }
    bool IsConnected(const int d) const {
        if (NONE == bType) return false;
        const auto oppositeD = (0 == d % 2) ? d + 1 : d - 1;
        return dir[oppositeD];
    }
    void Reset() {
        bType = NONE;
        visited = false;
        for (auto& iter : dir) iter = false;
    }

public:
    BLOCK_TYPE bType;
    bool visited;
    bool dir[DOWN + 1];
};

int main(int argc, char** argv)
{
    auto blocks = new Block[50][50];
    int test_case, T;
    scanf("%d", &T);
    for (test_case = 1; test_case <= T; ++test_case) {
        int row, col, startRow, startCol, stepOver;
        scanf("%d %d %d %d %d", &row, &col, &startRow, &startCol, &stepOver);
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                int temp;
                scanf("%d", &temp);
                blocks[i][j].Init(temp);
            }
        }

        queue<pair<Pos, int>> q;
        q.push(make_pair(Pos(startRow, startCol), 1));
        int count = 0;
        while (!q.empty()) {
            auto top = q.front();
            if (stepOver < top.second) break;
            if (!blocks[top.first.x][top.first.y].visited) {
                count++;
                blocks[top.first.x][top.first.y].visited = true;
            }
            for (int i = static_cast<int>(LEFT); i <= static_cast<int>(DOWN); ++i) {
                if (blocks[top.first.x][top.first.y].dir[i]) {
                    auto nX = top.first.x + dx[i];
                    auto nY = top.first.y + dy[i];
                    if (0 <= nX && 0 <= nY && row > nX && col > nY &&
                        !blocks[nX][nY].visited && blocks[nX][nY].IsConnected(i))
                        q.push(make_pair(Pos(nX, nY), top.second + 1));
                }
            }
            q.pop();
        }
        printf("#%d %d\n", test_case, count);
        for (int i = 0; i < row; ++i) for (int j = 0; j < col; ++j) blocks[i][j].Reset();
    }
    return 0;
}
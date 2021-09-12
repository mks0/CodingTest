#include <vector>
#include <deque>
#include <unordered_set>
using namespace std;

enum DIR { UP, DOWN, LEFT, RIGHT };
struct Pos_t {
    int r, c;
};
struct Data_t {
    Pos_t pos1, pos2;
    int steps;
};

int N;

inline bool IsHorizontal(const Pos_t& pos1, const Pos_t& pos2) {
    return pos1.r == pos2.r;
}
inline bool IsMovable(const Pos_t& pos, const DIR dir, const vector<vector<int>>& board) {
    if (UP == dir) return (0 > pos.r - 1) ? false : 1 != board[pos.r - 1][pos.c];
    if (DOWN == dir) return (N <= pos.r + 1) ? false : 1 != board[pos.r + 1][pos.c];
    if (LEFT == dir) return (0 > pos.c - 1) ? false : 1 != board[pos.r][pos.c - 1];
    return (N <= pos.c + 1) ? false : 1 != board[pos.r][pos.c + 1];
}
inline bool Move(Pos_t& pos, const DIR dir, const vector<vector<int>>& board) {
    auto ret = IsMovable(pos, dir, board);
    if (ret) {
        if (UP == dir) pos.r--;
        else if (DOWN == dir) pos.r++;
        else if (LEFT == dir) pos.c--;
        else pos.c++;
    }
    return ret;
}

inline bool GetAllRotateSets(vector<pair<Pos_t, Pos_t>>& v, const vector<vector<int>>& board, const Pos_t& pos1, const Pos_t& pos2, const bool assignFlag) {
    if (IsHorizontal(pos1, pos2)) {
        // pos1 축 회전
        auto pos2Temp = pos2;
        if (Move(pos2Temp, UP, board) && Move(pos2Temp, LEFT, board)) {
            if (assignFlag)
                v.push_back({ pos2Temp, pos1 });
            else
                return true;
        }
        pos2Temp = pos2;
        if (Move(pos2Temp, DOWN, board) && Move(pos2Temp, LEFT, board)) {
            if (assignFlag)
                v.push_back({ pos1, pos2Temp });
            else
                return true;
        }

        // pos2 축 회전
        auto pos1Temp = pos1;
        if (Move(pos1Temp, UP, board) && Move(pos1Temp, RIGHT, board)) {
            if (assignFlag)
                v.push_back({ pos1Temp, pos2 });
            else
                return true;
        }
        pos1Temp = pos1;
        if (Move(pos1Temp, DOWN, board) && Move(pos1Temp, RIGHT, board)) {
            if (assignFlag)
                v.push_back({ pos2, pos1Temp });
            else
                return true;
        }
    }
    else {
        // pos1 축 회전
        auto pos2Temp = pos2;
        if (Move(pos2Temp, LEFT, board) && Move(pos2Temp, UP, board)) {
            if (assignFlag)
                v.push_back({ pos2Temp, pos1 });
            else
                return true;
        }
        pos2Temp = pos2;
        if (Move(pos2Temp, RIGHT, board) && Move(pos2Temp, UP, board)) {
            if (assignFlag)
                v.push_back({ pos1, pos2Temp });
            else
                return true;
        }

        // pos2 축 회전
        auto pos1Temp = pos1;
        if (Move(pos1Temp, LEFT, board) && Move(pos1Temp, DOWN, board)) {
            if (assignFlag)
                v.push_back({ pos1Temp, pos2 });
            else
                return true;
        }
        pos1Temp = pos1;
        if (Move(pos1Temp, RIGHT, board) && Move(pos1Temp, DOWN, board)) {
            if (assignFlag)
                v.push_back({ pos2, pos1Temp });
            else
                return true;
        }
    }
    return !v.empty();
}
inline int Key(const Pos_t& pos1, const Pos_t& pos2) {
    return pos2.c + pos2.r * 100 + pos1.c * 100 * 100 + pos1.r * 100 * 100 * 100;
}

int solution(vector<vector<int>> board) {
    N = static_cast<decltype(N)>(board.size());
    Data_t pos{ {0,0},{0,1},0 };
    deque<Data_t> q;
    q.push_back(pos);
    unordered_set<int> visit;
    visit.insert(Key(pos.pos1, pos.pos2));

    while (!q.empty()) {
        auto t = q.front();
        if (N - 1 == t.pos2.r && N - 1 == t.pos2.c)
            return t.steps;

        vector<pair<Pos_t, Pos_t>> v;
        if (GetAllRotateSets(v, board, t.pos1, t.pos2, true)) {
            for (auto& iter : v) {
                if (visit.end() == visit.find(Key(iter.first, iter.second))) {
                    visit.insert(Key(iter.first, iter.second));
                    q.push_back({ iter.first, iter.second, t.steps + 1 });
                }
            }
        }
        for (int i = static_cast<int>(UP); i <= static_cast<int>(RIGHT); ++i) {
            auto pos1 = t.pos1;
            auto pos2 = t.pos2;
            if (Move(pos1, static_cast<DIR>(i), board) &&
                Move(pos2, static_cast<DIR>(i), board) &&
                (visit.end() == visit.find(Key(pos1, pos2)))) {
                visit.insert(Key(pos1, pos2));
                q.push_back({ pos1, pos2, t.steps + 1 });
            }
        }
        q.pop_front();
    }
    return -1;
}
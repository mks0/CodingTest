#include <vector>
#include <map>
using namespace std;

using pos_t = pair<int, int>;
using field_t = map<pos_t, int>;

const int BASE = 1;
const int BRIDGE = 2;

inline bool CheckPosition(field_t& field, const pos_t& pos, const int condType) {
    if ((field.end() != field.find(pos)) && (condType & field[pos])) return true;
    return false;
}
inline bool AddingBase(field_t& field, const pos_t& pos) {
    if (0 == pos.second)
        return true; // 바닥 설치
    if (CheckPosition(field, { pos.first, pos.second - 1 }, BASE))
        return true; // 추가하려는 기둥 아래에 다른 기둥 있음
    if (CheckPosition(field, { pos.first - 1, pos.second }, BRIDGE))
        return true; // 추가하려는 기둥 왼쪽 아래에 보 있음
    if (CheckPosition(field, { pos.first, pos.second }, BRIDGE))
        return true; // 추가하려는 기둥 오른쪽 아래에 보 있음
    return false;
}
inline bool AddingBridge(field_t& field, const pos_t& pos) {
    if (CheckPosition(field, { pos.first, pos.second - 1 }, BASE))
        return true; // 추가하려는 보 시작 지점 아래에 기둥 있음
    if (CheckPosition(field, { pos.first + 1, pos.second - 1 }, BASE))
        return true; // 추가하려는 보 종료 지점 아래에 기둥 있음
    if (CheckPosition(field, { pos.first - 1, pos.second }, BRIDGE) &&
        CheckPosition(field, { pos.first + 1, pos.second }, BRIDGE))
        return true; // 추가하려는 보 양 옆에 다른 보 있음
    return false;
}
bool CheckAll(field_t& field) {
    for (const auto& iter : field) {
        if (BASE & iter.second) {
            if (!AddingBase(field, iter.first)) return false;
        }
        if (BRIDGE & iter.second) {
            if (!AddingBridge(field, iter.first)) return false;
        }
    }
    return true;
}
void RemovingBase(field_t& field, const pos_t& pos) {
    field[pos] &= ~BASE;
    if (!CheckAll(field))
        field[pos] |= BASE;
}
void RemovingBridge(field_t& field, const pos_t& pos) {
    field[pos] &= ~BRIDGE;
    if (!CheckAll(field))
        field[pos] |= BRIDGE;
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    field_t field;
    const int ADD_CMD = 1;
    const int INPUT_BRIDGE = 1;

    for (auto& iter : build_frame) {
        auto pos = make_pair(iter[0], iter[1]);
        if (ADD_CMD == iter[3]) {
            if (INPUT_BRIDGE == iter[2]) {
                if (AddingBridge(field, pos))
                    field[pos] |= BRIDGE;
            }
            else {
                if (AddingBase(field, pos))
                    field[pos] |= BASE;
            }
        }
        else {
            if (INPUT_BRIDGE == iter[2]) RemovingBridge(field, pos);
            else RemovingBase(field, pos);
        }
    }

    vector<vector<int>> answer;
    for (auto& iter : field) {
        if (iter.second > 0) {
            if (BASE & iter.second)
                answer.push_back({ iter.first.first, iter.first.second, 0 });
            if (BRIDGE & iter.second)
                answer.push_back({ iter.first.first, iter.first.second, 1 });
        }
    }
    return answer;
}
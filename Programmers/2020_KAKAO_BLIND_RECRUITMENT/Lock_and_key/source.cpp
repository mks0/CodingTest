#include <vector>
using namespace std;

size_t offset;
size_t fieldN;
size_t lockN;
size_t keyN;

inline void Rotate(vector<vector<int>>& v) {
    const auto row = v.size();
    const auto col = v[0].size();
    vector<vector<int>> newV(row, vector<int>(col));
    for (size_t i = 0; i < row; ++i)
        for (size_t j = 0; j < col; ++j)
            newV[j][col - i - 1] = v[i][j];
    swap(v, newV);
}

inline void Init(vector<vector<int>>& _originField, vector<vector<vector<int>>>& _keys, vector<vector<int>>& _key, const vector<vector<int>>& _lock) {
    lockN = _lock.size();
    keyN = _key.size();
    offset = keyN - 1;
    fieldN = lockN + offset * 2;
    vector<vector<int>> originField(fieldN, vector<int>(fieldN, 0));
    for (size_t row = 0; row < lockN; ++row)
        for (size_t col = 0; col < lockN; ++col)
            originField[row + offset][col + offset] = _lock[row][col];
    vector<vector<vector<int>>> key;
    for (int i = 0; i < 4; ++i) {
        key.push_back(_key);
        Rotate(_key);
    }
    swap(_originField, originField);
    swap(_keys, key);
}

inline void Spread(vector<vector<int>>& field, const vector<vector<int>>& key, const size_t offset_r, const size_t offset_c, const bool adding) {
    for (size_t row = 0; row < keyN; ++row)
        for (size_t col = 0; col < keyN; ++col)
            field[offset_r + row][offset_c + col] += (adding ? key[row][col] : -key[row][col]);
}

inline bool Check(const vector<vector<int>>& field) {
    for (size_t row = 0; row < lockN; ++row)
        for (size_t col = 0; col < lockN; ++col)
            if (1 != field[row + offset][col + offset])
                return false;
    return true;
}

bool Scan(vector<vector<int>> field, const vector<vector<int>>& key) {
    for (size_t row = 0; row <= fieldN - keyN; ++row) {
        for (size_t col = 0; col <= fieldN - keyN; ++col) {
            Spread(field, key, row, col, true);
            if (Check(field)) return true;
            Spread(field, key, row, col, false);
        }
    }
    return false;
}

bool solution(vector<vector<int>> _key, vector<vector<int>> _lock) {
    vector<vector<int>> originField;
    vector<vector<vector<int>>> key;
    Init(originField, key, _key, _lock);

    for (auto& iter : key)
        if (Scan(originField, iter))
            return true;
    return false;
}
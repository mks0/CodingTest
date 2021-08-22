#include <vector>
#include <deque>
#include <algorithm>
#include <cmath>
#include <limits>
using namespace std;

using pos_t = pair<int, int>;
const int MAX_PAIRS = 6;

int Advance(const pos_t& pos, const pos_t& target, const vector<vector<int>>& board) {
    int cnt = (numeric_limits<int>::max)();
    deque<pair<pos_t, int>> q;
    q.push_back(make_pair(pos, 0));
    while (!q.empty()) {
        auto& top = q.front();
        if (top.first.first == target.first &&
            top.first.second == target.second) {
            cnt = min(top.second, cnt);
        }
        else {
            if (top.first.first != target.first) {
                const auto step = (top.first.first > target.first) ? -1 : 1;
                if (target.first == top.first.first + step) { // 1칸
                    q.push_back(make_pair(make_pair(target.first, top.first.second), top.second + 1));
                }
                else if (target.first == top.first.first + step * 2) { // 2칸
                    if (0 == target.first || 3 == target.first) {
                        q.push_back(make_pair(make_pair(target.first, top.first.second),
                            top.second + ((0 == board[top.first.first + step][top.first.second]) ? 1 : 2)));
                    }
                    else {
                        q.push_back(make_pair(make_pair(target.first, top.first.second),
                            top.second + (((0 == board[top.first.first + step][top.first.second]) &&
                                (0 != board[target.first][top.first.second])) ? 1 : 2)));
                    }
                }
                else { // 3칸
                    q.push_back(make_pair(make_pair(target.first, top.first.second),
                        top.second + 1 +
                        board[top.first.first + step][top.first.second] + 
                        board[top.first.first + step * 2][top.first.second]
                    ));
                }
            }
            if (top.first.second != target.second) {
                const auto step = (top.first.second > target.second) ? -1 : 1;
                if (target.second == top.first.second + step) {
                    q.push_back(make_pair(make_pair(top.first.first, target.second), top.second + 1));
                }
                else if (target.second == top.first.second + step * 2) {
                    if (0 == target.second || 3 == target.second) {
                        q.push_back(make_pair(make_pair(top.first.first, target.second),
                            top.second + ((0 == board[top.first.first][top.first.second + step]) ? 1 : 2)));
                    }
                    else {
                        q.push_back(make_pair(make_pair(top.first.first, target.second),
                            top.second + (((0 == board[top.first.first][top.first.second + step]) &&
                                (0 != board[top.first.first][target.second])) ? 1 : 2)));
                    }
                }
                else {
                    q.push_back(make_pair(make_pair(top.first.first, target.second),
                        top.second + 1 +
                        board[top.first.first][top.first.second + step] +
                        board[top.first.first][top.first.second + step * 2]
                    ));
                }
            }
        }
        q.pop_front();
    }
    return cnt + 1; // +1 == Enter key
}

int walkthrough(vector<vector<int>> board, int r, int c, const vector<pos_t>& steps) {
    int sum = 0;
    pos_t pos{r, c};
    deque<pos_t> q;
    for (const auto& iter : steps) {
        q.push_back(iter);
        sum += Advance(pos, iter, board);
        pos = iter;
        if (2 <= q.size()) {
            while (!q.empty()) {
                board[q.front().first][q.front().second] = 0;
                q.pop_front();
            }
        }
    }
    return sum;
}

void GetTC(vector<vector<pos_t>>& tc, const int pairCnt, const vector<vector<int>>& permutations, const vector<vector<pos_t>>& pairArr) {
    const auto endVar = static_cast<int>(pow(2, pairCnt));
    for (const auto& iter : permutations) {
        for (int i = 0; i < endVar; ++i) {
            tc.push_back(vector<pos_t>(pairCnt * 2));
            auto& p = tc.back();
            for (int j = 0; j < iter.size(); ++j) {
                if (0 == ((1 << j) & i)) {
                    p[2 * j] = pairArr[iter[j]][0];
                    p[2 * j + 1] = pairArr[iter[j]][1];
                }
                else {
                    p[2 * j] = pairArr[iter[j]][1];
                    p[2 * j + 1] = pairArr[iter[j]][0];
                }
            }
        }
    }
}

void permutation(vector<int> v, vector<vector<int>>& ret) {
	sort(v.begin(), v.end());
	do {
        ret.push_back(vector<int>(v.size()));
        auto& p = ret.back();
        for (int i = 0; i < v.size(); ++i) p[i] = v[i];
    } while (next_permutation(v.begin(), v.end()));
}

int GetPermutations(vector<vector<int>>& permutations, const vector<vector<pos_t>>& pairArr) {
    int pairCnt = 0;
    for (int i = 1; i <= MAX_PAIRS; ++i)
        if (!pairArr[i].empty()) ++pairCnt;

    vector<int> permutationsStd(pairCnt);
    for (int i = 0; i < permutationsStd.size(); ++i)
        permutationsStd[i] = i + 1;

    permutation(permutationsStd, permutations);
    return pairCnt;
}

void GetPairArr(vector<vector<pos_t>>& pairArr, const vector<vector<int>>& board) {
    for (int r = 0; r < board.size(); ++r) {
        for (int c = 0; c < board[r].size(); ++c) {
            if (0 != board[r][c]) {
                pairArr[board[r][c]].push_back(make_pair(r, c));
            }
        }
    }
}
int solution(vector<vector<int>> board, int r, int c) {
    vector<vector<pos_t>> pairArr(MAX_PAIRS + 1);
    GetPairArr(pairArr, board);

    vector<vector<int>> permutations;
    auto pairCnt = GetPermutations(permutations, pairArr);
    
    vector<vector<pos_t>> tc;
    GetTC(tc, pairCnt, permutations, pairArr);
    
    int answer = (numeric_limits<int>::max)();
    for (const auto& iter : tc) {
        auto temp = walkthrough(board, r, c, iter);
        answer = min(answer, temp);
    }

    return answer;
}
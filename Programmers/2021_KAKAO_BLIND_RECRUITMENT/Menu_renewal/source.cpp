#include <string>
#include <vector>
#include <bitset>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;

void combination(const string& s, const size_t R, vector<string>& v) {
    if (s.size() < R) return;
    vector<bool> visit(s.size() - R, false);
    visit.insert(visit.end(), R, true);
    do {
        string tmp;
        for (int i = 0; i < s.size(); ++i)
            if (visit[i]) tmp += s[i];
        v.push_back(tmp);
    } while (next_permutation(visit.begin(), visit.end()));
}

const size_t ALPHABET_SIZE = 'Z' - 'A' + 1;
int Count(const vector<bitset<ALPHABET_SIZE>>& menu, const string& s) {
    int ret = 0;
    for (const auto& iter : menu) {
        bool flag = true;
        for (const auto& c : s) {
            if (!iter.test(c - 'A')) {
                flag = false;
                break;
            }
        }
        if (flag) ++ret;
    }
    return ret;
}

vector<string> solution(vector<string> orders, vector<int> courses) {
    vector<bitset<ALPHABET_SIZE>> menu(orders.size());
    set<char> unionMenuSet;
    for (int i = 0; i < orders.size(); ++i) {
        for (const auto& c : orders[i]) {
            unionMenuSet.insert(c);
            menu[i].set(c - 'A');
        }
    }
    string unionMenuStr;
    for (const auto& c : unionMenuSet) unionMenuStr += c;
    
    vector<string> answer;
    for (const auto& course : courses) {
        vector<string> comb;
        combination(unionMenuStr, course, comb);
        priority_queue<pair<int, string>> q;
        int maxV = 2;
        for (const auto& combIter : comb) {
            const auto cnt = Count(menu, combIter);
            if (cnt >= maxV) {
                maxV = cnt;
                q.push(make_pair(cnt, combIter));
            }
        }
        if (!q.empty()) {
            const auto maxVar = q.top().first;
            do {
                answer.push_back(q.top().second);
                q.pop();
            } while (!q.empty() && maxVar == q.top().first);   
        }
    }
    sort(answer.begin(), answer.end());
    return answer;
}
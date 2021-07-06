#include <string>
#include <vector>
#include <map>
using namespace std;

vector<int> solution(vector<string> operations) {
    map<int,int> m;
    for (auto& iter : operations) {
        if ('I' == iter[0]) {
            iter.erase(0, 2);
            auto var = stoi(iter);
            if (m.end() == m.find(var))
                m[var] = 0;
            else
                m[var]++; // 중복 입력 케이스
        } else if (!m.empty()) {
            if ('-' == iter[2]) {
                if (0 == m.begin()->second)
                    m.erase(m.begin()->first);
                else
                    m.begin()->second--;
            } else {
                if (0 == m.rbegin()->second)
                    m.erase(m.rbegin()->first);
                else
                    m.rbegin()->second--;
            }
        }
    }
    if (m.empty()) return {0,0};
    else return {m.rbegin()->first, m.begin()->first};
}
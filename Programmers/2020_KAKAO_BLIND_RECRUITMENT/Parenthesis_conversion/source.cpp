#include <string>
using namespace std;

// s가 올바른 괄호 문자열이면 true
inline bool IsRightPair(const string& s) {
    int cnt = 0;
    for (const auto& iter : s) {
        cnt += ('(' == iter) ? 1 : -1;
        if (0 > cnt) return false;
    }
    return true;
}

// s에서 u로 분리할 수 있는 균형잡힌 괄호 문자열 위치값
inline int Find_uPos(const string& s) {
    int cnt = 0;
    for (int i = 0; i < s.size(); ++i) {
        cnt += ('(' == s[i]) ? 1 : -1;
        if (0 == cnt) return i + 1;
    }
    return s.size();
}

string Process(const string& s) {
    // 0. + 1.
    if (IsRightPair(s)) return s;

    // 2.
    auto uPos = Find_uPos(s);
    string u(s.substr(0, uPos));
    string v(s.substr(uPos));

    // 3.
    if (IsRightPair(u)) return u + Process(v);

    // 4.
    else {
        string temp("(" + Process(v) + ")");
        for (int i = 1; i < u.size() - 1; ++i)
            temp += ('(' == u[i]) ? ')' : '(';
        return temp;
    }
}

string solution(string p) {
    return Process(p);
}
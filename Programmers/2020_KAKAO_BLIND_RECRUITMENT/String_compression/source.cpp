#include <string>
#include <algorithm>
using namespace std;

int compress(const string& s, const int unit) {
    int ret = s.size();
    string prev("");
    int cnt = 0;
    for (int i = 0; i < s.size(); i += unit) {
        auto cur = s.substr(i, unit);
        if (prev == cur)
            cnt++;
        else {
            if (0 < cnt)
                ret -= (cnt * unit) - to_string(cnt + 1).size();
            prev = cur;
            cnt = 0;
        }
    }
    return (0 < cnt) ? ret - ((cnt * unit) - to_string(cnt + 1).size()) : ret;
}

int solution(string s) {
    int answer = s.size();
    for (int i = 1; i <= s.size() / 2; ++i)
        answer = min(answer, compress(s, i));
    return answer;
}
#include <string>
#include <vector>
using namespace std;
inline void step1(string& s) {
    for (auto& c : s)
        if ('A' <= c && 'Z' >= c) c += 'a' - 'A';
}
inline void step2(string& s) {
    string ss;
    for (const auto& c : s)
        if (('a' <= c && 'z' >= c) ||
            ('0' <= c && '9' >= c) ||
            ('-' == c || '_' == c || '.' == c))
            ss += c;
    swap(ss, s);
}
inline void step3(string& s) {
    string ss;    
    for (const auto& c : s) {
        if ('.' == c && '.' == ss.back())
            continue;
        ss += c;
    }
    swap(ss, s);
}
inline void step4(string& s) {
    while ('.' == s.front()) s.erase(0, 1);
    while ('.' == s.back()) s.pop_back();
}
inline void step5(string& s) {
    if (s.empty()) s = "a";
}
inline void step6(string& s) {
    if (16 <= s.size()) s = s.substr(0, 15);
    while ('.' == s.back())
        s.pop_back();
}
inline void step7(string& s) {
    while (2 >= s.size()) s += s.back();
}
string solution(string new_id) {
    step1(new_id);
    step2(new_id);
    step3(new_id);
    step4(new_id);
    step5(new_id);
    step6(new_id);
    step7(new_id);
    return new_id;
}
#include <string>
#include <vector>
using namespace std;

using base_t = int;

inline base_t GetTime(const string& src) {
    return (((src[0] - '0') * 10 + (src[1] - '0')) * 3600)
        + (((src[3] - '0') * 10 + (src[4] - '0')) * 60)
        + ((src[6] - '0') * 10 + (src[7] - '0'));
}

inline string GetTime(base_t src) {
    auto hhv = src / 3600;
    src %= 3600;
    auto mmv = src / 60;
    auto ssv = src % 60;

    auto hh = (hhv >= 10) ? to_string(hhv) : "0" + to_string(hhv);
    auto mm = (mmv >= 10) ? to_string(mmv) : "0" + to_string(mmv);
    auto ss = (ssv >= 10) ? to_string(ssv) : "0" + to_string(ssv);
    return (hh + ":" + mm + ":" + ss);
}

static base_t tp[360000];

string solution(string play_time, string adv_time, vector<string> logs) {
    auto play_t = GetTime(play_time);
    for (const auto& iter : logs) {
        auto finish = GetTime(iter.substr(9, 8));
        for (auto i = GetTime(iter.substr(0, 8)); i < finish; ++i) tp[i]++;
    }

    auto adv_t = GetTime(adv_time);
    long long acc_t = 0;
    for (decltype(adv_t) i = 0; i < adv_t; ++i) acc_t += tp[i];

    base_t maxPt = 0;
    long long maxT = acc_t;
    for (decltype(adv_t) i = adv_t; i < play_t; ++i) {
        acc_t = acc_t - tp[i - adv_t] + tp[i];
        if (maxT < acc_t) {
            maxT = acc_t;
            maxPt = i - adv_t + 1;
        }
    }
    
    return GetTime(maxPt);
}
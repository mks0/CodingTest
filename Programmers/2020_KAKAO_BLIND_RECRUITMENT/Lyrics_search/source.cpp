#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> solution(vector<string> words, vector<string> queries) {
    vector<vector<string>> dic(10001);
    vector<vector<string>> rdic(10001);
    for (auto& iter : words) {
        dic[iter.size()].push_back(iter);
        reverse(iter.begin(), iter.end());
        rdic[iter.size()].push_back(iter);
    }
    for (auto& iter : dic)
        if (!iter.empty()) sort(iter.begin(), iter.end());
    for (auto& iter : rdic)
        if (!iter.empty()) sort(iter.begin(), iter.end());

    vector<int> answer;
    for (auto& query : queries) {
        bool rFlag = ('?' == query[0]);
        const auto& d = rFlag ? rdic : dic;
        if (rFlag) reverse(query.begin(), query.end());
        auto idx = query.size();
        if (d[idx].empty()) answer.push_back(0);
        else {
            string endQuery(query);
            auto wildpos = query.find('?');
            if (string::npos != wildpos) {
                query[wildpos] = 'a';
                endQuery[wildpos] = 'z' + 1;
            }
            auto lower = lower_bound(d[idx].begin(), d[idx].end(), query) - d[idx].begin();
            auto upper = lower_bound(d[idx].begin(), d[idx].end(), endQuery) - d[idx].begin();
            answer.push_back(upper - lower);
        }
    }
    return answer;
}
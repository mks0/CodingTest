#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

enum Langs { CPP, JAVA, PYTHON, LANGS_ };
enum JobType { BACKEND, FRONTEND, JOBTYPE_ };
enum Grade { JUNIOR, SENIOR, GRADE_ };
enum Food { CHICKEN, PIZZA, FOOD_ };
inline int Idx(const Langs langs, const JobType jobtype, const Grade grade, const Food food) {
    return langs + (LANGS_ * jobtype) + (LANGS_ * JOBTYPE_ * grade) + (LANGS_ * JOBTYPE_ * GRADE_ * food);
}

vector<int> solution(vector<string> info, vector<string> query) {
    vector<vector<int>> table(LANGS_ * JOBTYPE_ * GRADE_ * FOOD_);
    vector<int> answer(query.size(), 0);
    for (const auto& iter : info)
    {
        stringstream ss(iter);
        string s[4];
        int score;
        ss >> s[0] >> s[1] >> s[2] >> s[3] >> score;
        const auto langs = ('c' == s[0][0]) ? CPP : (('j' == s[0][0]) ? JAVA : PYTHON);
        const auto jobtype = ('b' == s[1][0]) ? BACKEND : FRONTEND;
        const auto grade = ('j' == s[2][0]) ? JUNIOR : SENIOR;
        const auto food = ('p' == s[3][0]) ? PIZZA : CHICKEN;
        table[Idx(langs, jobtype, grade, food)].push_back(score);
    }
    for (auto& iter : table) sort(iter.begin(), iter.end());
    for (int i = 0; i < query.size(); ++i) {
        string s[7];
        int score;
        vector<Langs> langs;
        vector<JobType> jt;
        vector<Grade> gd;
        vector<Food> fd;
        stringstream ss(query[i]);
        ss >> s[0] >> s[1] >> s[2] >> s[3] >> s[4] >> s[5] >> s[6] >> score;
        if ('-' == s[0][0] || 'c' == s[0][0]) langs.push_back(CPP);
        if ('-' == s[0][0] || 'j' == s[0][0]) langs.push_back(JAVA);
        if ('-' == s[0][0] || 'p' == s[0][0]) langs.push_back(PYTHON);
        if ('-' == s[2][0] || 'b' == s[2][0]) jt.push_back(BACKEND);
        if ('-' == s[2][0] || 'f' == s[2][0]) jt.push_back(FRONTEND);
        if ('-' == s[4][0] || 'j' == s[4][0]) gd.push_back(JUNIOR);
        if ('-' == s[4][0] || 's' == s[4][0]) gd.push_back(SENIOR);
        if ('-' == s[6][0] || 'p' == s[6][0]) fd.push_back(PIZZA);
        if ('-' == s[6][0] || 'c' == s[6][0]) fd.push_back(CHICKEN);
        for (const auto& it1 : langs) {
            for (const auto& it2 : jt) {
                for (const auto& it3 : gd) {
                    for (const auto& it4 : fd) {
                        const auto idx = Idx(it1, it2, it3, it4);
                        answer[i] += table[idx].size() - (lower_bound(table[idx].begin(), table[idx].end(), score) - table[idx].begin());
                    }
                }
            }
        }
    }
    return answer;
}
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
    vector<int> answer;
    for (const auto& iter : commands) {
        vector<int> temp(array.begin() + iter[0] - 1, array.begin() + iter[1]);
        sort(temp.begin(), temp.end());
        answer.push_back(temp[iter[2] - 1]);
    }
    return answer;
}
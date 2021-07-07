#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> solution(vector<int> answers) {
    const size_t students = 3;
    const vector<int> student[students] {
        {1,2,3,4,5},{2,1,2,3,2,4,2,5},{3,3,1,1,2,2,4,4,5,5}
    };
    
    vector<int> score(3,0);
    for (int i = 0; i < answers.size(); ++i)
        for (int j = 0; j < students; ++j)
            if (answers[i] == student[j][i % student[j].size()])
                ++score[j];
    
    const auto maxScore = *max_element(score.begin(), score.end());
    vector<int> answer;
    for (int i = 0; i < students; ++i)
        if (maxScore == score[i]) answer.push_back(i + 1);
    return answer;
}
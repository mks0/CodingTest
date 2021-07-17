#include <vector>
using namespace std;

int solution(vector<int> money) {
    vector<vector<int> > cache(2, vector<int>(money.size()+1, 0));
    for (int i = 2; i <= money.size(); ++i) {
        cache[0][i] = max(cache[0][i-2] + money[i-2], cache[0][i-1]);
        cache[1][i] = max(cache[1][i-2] + money[i-1], cache[1][i-1]);
    }
    return max(cache[0][money.size()], cache[1][money.size()]);
}
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<vector<int>> triangle) {
    if (1 == triangle.size()) return triangle[0][0];
    if (2 == triangle.size()) return triangle[0][0] + max(triangle[1][0], triangle[1][1]);

    vector<vector<int>> cache(triangle.size());
    cache[1].push_back(triangle[0][0] + triangle[1][0]);
    cache[1].push_back(triangle[0][0] + triangle[1][1]);

    for (size_t depth = 2; depth < triangle.size(); ++depth) {
        cache[depth].push_back(cache[depth-1][0] + triangle[depth][0]);
        for (size_t i = 1; i < depth; ++i)
            cache[depth].push_back(triangle[depth][i] + max(cache[depth-1][i-1], cache[depth-1][i]));
        cache[depth].push_back(cache[depth-1][depth-1] + triangle[depth][depth]);
    }
    return *max_element(cache[triangle.size()-1].begin(), cache[triangle.size()-1].end());
}
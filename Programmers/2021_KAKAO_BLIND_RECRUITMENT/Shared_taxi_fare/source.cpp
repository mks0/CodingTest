#include <string>
#include <vector>
#include <algorithm>
using namespace std;

using base_t = long;
const base_t INF = 1e9;

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    vector<vector<base_t>> tab(201, vector<base_t>(201, INF));
    for (const auto& iter : fares)
        tab[iter[0]][iter[1]] = tab[iter[1]][iter[0]] = iter[2];
    for (int i = 1; i <= n; ++i) tab[i][i] = 0;
    
    for (int via = 1; via <= n; ++via)
        for (int from = 1; from <= n; ++from)
            for (int to = 1; to <= n; ++to)
                tab[from][to] = min(tab[from][to], tab[from][via] + tab[via][to]);
    
    base_t answer = tab[s][a] + tab[s][b];
    for (int via = 1; via <= n; ++via) {
        answer = min(answer, tab[s][via] + tab[via][a] + tab[via][b]);
    }
    return static_cast<int>(answer);
}
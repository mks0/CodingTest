#include <vector>
#include <deque>
#include <unordered_map>
#include <algorithm>
using namespace std;

int BFS(const int n, const unordered_map<int, vector<int>>& edge) {
    vector<int> costs(n+1, 0);
    auto cmp = [&costs](const int a) { return 0 == costs[a]; };
    costs[1] = -1;          // 1번 노드의 비용은 탐색에서 제외
    deque<pair<int,int>> q; // (no, cost)
    q.push_back(make_pair(1, 0));
    while (!q.empty()) {
        auto top = q.front();
        if (edge.end() != edge.find(top.first)) {
            auto& p = edge.at(top.first);
            auto pt = find_if(p.begin(), p.end(), cmp);
            while (p.end() != pt) {
                costs[*pt] = top.second + 1;
                q.push_back(make_pair(*pt, costs[*pt]));
                pt = find_if(pt, p.end(), cmp);
            }
        }
        q.pop_front();
    }
    return count(costs.begin(), costs.end(), *max_element(costs.begin(), costs.end()));
}

int solution(int n, vector<vector<int>> edge) {
    unordered_map<int, vector<int>> umap;
    for (const auto& iter : edge) {
        umap[iter[0]].push_back(iter[1]);
        umap[iter[1]].push_back(iter[0]);
    }
    return BFS(n, umap);
}
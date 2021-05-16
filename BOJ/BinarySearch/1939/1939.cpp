#include <iostream>
#include <vector>
#include <queue>
using namespace std;
struct Graph {
    int next;
    int cost;
};
const int MAX_N = 10001;
int N;
vector<Graph> v[MAX_N];
int maxCost = 0;
int startN;
int endN;

void input() {
    int M;
    scanf("%d %d", &N, &M);
    for (int i = 0; i < M; ++i) {
        int start, end, cost;
        scanf("%d %d %d", &start, &end, &cost);
        v[start].push_back({end, cost});
        v[end].push_back({start, cost});
        maxCost = max(maxCost, cost);
    }
    scanf("%d %d", &startN, &endN);
}

int TestCase() {
    N = 3;
    v[1].push_back({2, 2}); v[2].push_back({1, 2});
    v[3].push_back({1, 3}); v[1].push_back({3, 3});
    v[2].push_back({3, 2}); v[3].push_back({2, 2});
    maxCost = 3;
    startN = 1;
    endN = 3;
    return 3;
}

bool BFS(const int targetCost) {
    vector<bool> visited(N, false);
    queue<int> q;
    
    visited[startN] = true;
    q.push(startN);
    
    while (!q.empty()) {
        auto top = q.front();
        q.pop();
        for (const auto& iter : v[top]) {
            if (!visited[iter.next] && (targetCost <= iter.cost)) {
                if (endN == iter.next) return true;
                visited[iter.next] = true;
                q.push(iter.next);
            }
        }
    }
    
    return false;
}

//#define UNIT_TEST

int main() {
#ifndef UNIT_TEST
    input();
#else
    const auto answer = TestCase();
#endif
    int left = 1;
    int right = maxCost;
    while (left <= right) {
        const int mid = (left + right) / 2;
        if (BFS(mid)) left = mid + 1;
        else right = mid - 1;
    }
#ifndef UNIT_TEST
    printf("%d\n", right);
#else
    printf("%s, answer=%d, result=%d\n", (answer == right) ? "Pass" : "Fail", answer, right);
#endif
    return 0;
}
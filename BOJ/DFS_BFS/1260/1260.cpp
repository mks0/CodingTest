#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cstring>
using namespace std;

const int MAX_NODES = 1001;
int nodes;
int edges;
int startNode;
bool edge[MAX_NODES][MAX_NODES] = { false, };

//#define UNIT_TEST
#ifdef UNIT_TEST
void TC01_input() {
    nodes = 4;
    edges = 5;
    startNode = 1;
    vector<pair<int, int>> edgePairs({ {1,2},{1,3},{1,4},{2,4},{3,4} });
    memset(edge, false, sizeof(edge));
    for (const auto& iter : edgePairs) edge[iter.first][iter.second] = edge[iter.second][iter.first] = true;
}
vector<int> TC01_DFS() { return { 1,2,4,3 }; }
vector<int> TC01_BFS() { return { 1,2,3,4 }; }

void TC02_input() {
    nodes = 5;
    edges = 5;
    startNode = 3;
    vector<pair<int, int>> edgePairs({ {5,4},{5,2},{1,2},{3,4},{3,1} });
    memset(edge, false, sizeof(edge));
    for (const auto& iter : edgePairs) edge[iter.first][iter.second] = edge[iter.second][iter.first] = true;
}
vector<int> TC02_DFS() { return { 3,1,2,5,4 }; }
vector<int> TC02_BFS() { return { 3,1,4,2,5 }; }

void TC03_input() {
    nodes = 1000;
    edges = 1;
    startNode = 1000;
    vector<pair<int, int>> edgePairs({ {999,1000} });
    memset(edge, false, sizeof(edge));
    for (const auto& iter : edgePairs) edge[iter.first][iter.second] = edge[iter.second][iter.first] = true;
}
vector<int> TC03_DFS() { return { 1000,999 }; }
vector<int> TC03_BFS() { return { 1000,999 }; }

void TC04_input() {
    nodes = 10;
    edges = 10;
    startNode = 4;
    vector<pair<int, int>> edgePairs({ {5,4},{6,4},{6,8},{8,9},{1,10},{2,10},{10,3},{8,2},{1,7},{4,10} });
    memset(edge, false, sizeof(edge));
    for (const auto& iter : edgePairs) edge[iter.first][iter.second] = edge[iter.second][iter.first] = true;
}
vector<int> TC04_DFS() { return { 4,5,6,8,2,10,1,7,3,9 }; }
vector<int> TC04_BFS() { return { 4,5,6,10,8,1,2,3,9,7 }; }
#else
void input() {
    scanf("%d %d %d", &nodes, &edges, &startNode);
    int temp1, temp2;
    for (int i = 0; i < edges; ++i) {
        scanf("%d %d", &temp1, &temp2);
        edge[temp1][temp2] = edge[temp2][temp1] = true;
    }
}
#endif

void DFS(const int node, vector<int>& answer) {
    vector<bool> visited(nodes + 1, false);
    stack<int> s;
    s.push(node);

    while (!s.empty()) {
        auto top = s.top();
        if (!visited[top]) {
            visited[top] = true;
            answer.push_back(top);
        }
        if (answer.size() >= static_cast<decltype(answer.size())>(nodes)) break;

        int i = 1;
        for (; i <= nodes; ++i)
            if (edge[top][i] && !visited[i]) break;
        (i > nodes) ? s.pop() : s.push(i);
    }
}

void BFS(const int node, vector<int>& answer) {
    vector<bool> visited(nodes + 1, false);
    queue<int> s;
    s.push(node);

    while (!s.empty()) {
        auto top = s.front();
        if (!visited[top]) {
            visited[top] = true;
            answer.push_back(top);
        }
        if (answer.size() >= static_cast<decltype(answer.size())>(nodes)) break;

        for (int i = 1; i <= nodes; ++i)
            if (edge[top][i] && !visited[i]) s.push(i);
        s.pop();
    }
}

#ifdef UNIT_TEST
void solution(const vector<int> answer_dfs, const vector<int> answer_bfs) {
#else
void solution() {
#endif
    vector<int> dfs, bfs;

    DFS(startNode, dfs);
    BFS(startNode, bfs);

#ifdef UNIT_TEST
    printf("%s\n", (answer_dfs == dfs) ? "DFS Pass" : "DFS Fail");
#endif
    for (const auto iter : dfs) {
        printf("%d ", iter);
    }
    printf("\n");
#ifdef UNIT_TEST
    for (const auto iter : answer_dfs) {
        printf("%d ", iter);
    }
    printf("\n");
#endif

#ifdef UNIT_TEST
    printf("%s\n", (answer_bfs == bfs) ? "BFS Pass" : "BFS Fail");
#endif
    for (const auto iter : bfs) {
        printf("%d ", iter);
    }
    printf("\n");
#ifdef UNIT_TEST
    for (const auto iter : answer_bfs) {
        printf("%d ", iter);
    }
    printf("\n");
#endif
}

int main() {
#ifdef UNIT_TEST
    TC01_input();
    solution(TC01_DFS(), TC01_BFS());

    TC02_input();
    solution(TC02_DFS(), TC02_BFS());

    TC03_input();
    solution(TC03_DFS(), TC03_BFS());

    TC04_input();
    solution(TC04_DFS(), TC04_BFS());
#else
    input();
    solution();
#endif
    return 0;
}
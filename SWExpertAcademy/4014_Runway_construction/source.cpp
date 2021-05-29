#include <iostream>
#include <unordered_map>
using namespace std;

enum LINE { ROW, COL };

int m[20][20];
int N, X;

inline bool IsPossible(const int startIdx, const int length, const LINE line) {
    int i, j, di, dj, fallingValue;
    if (ROW == line) { i = startIdx; di = j = 0; dj = 1; }
    else { j = startIdx; dj = i = 0; di = 1; }
    bool fallingEdge = false;
    int prev = m[i][j];
    unordered_map<int,int> umap;
    for (int k = 0; k < length; ++k) {
        const int edge = m[i][j] - prev;
        if (-1 > edge || 1 < edge) return false;
        umap[m[i][j]]++;
        if (fallingEdge) {
            if (0 != edge) return false;
            if (X == umap[fallingValue]) {
                umap[fallingValue] = 0;
                fallingEdge = false;
            }
        } else {
            if (1 == edge) {
                if (X <= umap[prev]) umap[prev] = 0;
                else return false;
            } else if (-1 == edge) {
                fallingEdge = true;
                fallingValue = m[i][j];
            }
        }
        prev = m[i][j];
        i += di;
        j += dj;
    }
    return !fallingEdge;
}

int main(int argc, char** argv) {
	int test_case, T;
	scanf("%d", &T);
	for(test_case = 1; test_case <= T; ++test_case) {
        scanf("%d %d", &N, &X);
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j) scanf("%d", &m[i][j]);
        
        int result = 0;
        for (int i = 0; i < 2; ++i) {
            LINE line = static_cast<LINE>(i);
            for (int j = 0; j < N; ++j) result += (IsPossible(j, N, line)) ? 1 : 0;
        }
        printf("#%d %d\n", test_case, result);
	}
	return 0;
}
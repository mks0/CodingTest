#include <vector>
#include <unordered_set>
using namespace std;

int solution(int N, int number) {
    const int LIMIT = 8;
    vector<long long> concate(LIMIT, N);
    for (int i = 1; i < concate.size(); ++i)
        concate[i] += concate[i-1] * 10LL;

    if (N == number) return 1;
    vector<unordered_set<long long> > cache(LIMIT);
    cache[0].insert(N);

    for (int i = 1; i < LIMIT; ++i) {
        for (int j = 0; j < i; ++j) {
            for (const auto& outer : cache[i-(j+1)]) {
                for (const auto& inner : cache[j]) {
                    cache[i].insert(outer + inner);
                    cache[i].insert(outer - inner);
                    cache[i].insert(outer * inner);
                    if (0LL != inner)
                        cache[i].insert(outer / inner);
                    cache[i].insert(concate[i]);
                }
            }
        }
        if (cache[i].end() != cache[i].find(number))
            return static_cast<int>(i+1);
    }
    return -1;
}
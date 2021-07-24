#include <vector>
#include <unordered_map>
#include <bitset>
using namespace std;

struct point {
    bitset<8> in, out;
    bool visited = false;
};
using Key_t = long long;
using Map_t = unordered_map<Key_t, point>;
using Pos_t = pair<int, int>;
const int di[] = { -1, -1, 0, 1, 1,  1,  0, -1 };
const int dj[] = { 0,  1, 1, 1, 0, -1, -1, -1 };

inline Key_t Key(const Pos_t& pos) {
    const Key_t BOUND = 200000LL;
    return ((pos.first + BOUND) << 23) + (pos.second + BOUND);
}
inline int Opposite(const int dir) {
    return (dir + 4) % 8;
}
int solution(vector<int> arrows) {
    int answer = 0;
    Map_t umap;
    Pos_t pos(0,0);
    for (const auto& iter : arrows) {
        for (int i = 0; i < 2; ++i) {
            umap[Key(pos)].visited = true;
            umap[Key(pos)].out.set(iter);

            pos.first += di[iter];
            pos.second += dj[iter];

            if (umap[Key(pos)].visited && !umap[Key(pos)].in.test(iter) && !umap[Key(pos)].out.test(Opposite(iter)))
                ++answer;
				
            umap[Key(pos)].visited = true;
            umap[Key(pos)].in.set(iter);
        }
    }
    return answer;
}
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

class GoldBox {
public:
    GoldBox(const int _N) : p(_N/4) {}
    void Process() {
        for (int i = 0; i < p; ++i) {
            int sum = 0;
            int scale = 1;
            for (int j = dq.size() - 1; j >= 0; --j) {
            	sum += dq[j] * scale;
                scale *= 16;
                if (0 == j % p) {
                    arr.push_back(sum);
                	sum = 0;
                    scale = 1;
                }
            }
            
            // rotate
            auto t = dq.back();
            dq.pop_back();
            dq.push_front(t);
        }
    }
    void Sort() {
    	sort(arr.begin(), arr.end(), greater<int>());
        arr.erase(unique(arr.begin(), arr.end()), arr.end());
    }
    
    const int p;
    deque<int> dq;
    vector<int> arr;
};

int main(int argc, char** argv)
{
	int test_case, T;
	scanf("%d", &T);
	for(test_case = 1; test_case <= T; ++test_case) {
        int N, K;
        scanf("%d %d", &N, &K);
        GoldBox box(N);
        for (int i = 0; i < N; ++i) {
            int temp;
            scanf("%1x", &temp);
            box.dq.push_back(temp);
        }
        box.Process();
        box.Sort();
        printf("#%d %d\n", test_case, box.arr[K - 1]);
	}
	return 0;
}
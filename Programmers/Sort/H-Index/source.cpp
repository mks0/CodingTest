#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<int> citations) {
    sort(citations.begin(), citations.end(), greater<int>());
    int n = 0;
    for (int h = citations[n]; h >= 0; --h) {
        while (n < citations.size() && h <= citations[n]) n++;
        if (h <= n) return h;
    }
}
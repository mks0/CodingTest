#include <string>
#include <vector>
#include <algorithm>
using namespace std;

using Int = long long;

long long solution(int n, vector<int> times) {
    Int left = 1LL;
    Int right = *max_element(times.begin(), times.end()) * static_cast<Int>(n);
    while (left <= right) {
        const Int mid = (left + right) / 2LL;
        
        Int possibleN = 0LL;
        for (const auto& iter : times)
            possibleN += (mid / iter);
        
        if (possibleN >= n)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return left;
}
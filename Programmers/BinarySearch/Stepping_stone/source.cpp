#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

void initialize(const int distance, vector<int>& rocks) {
    rocks.push_back(0);
    rocks.push_back(distance);
    sort(rocks.begin(), rocks.end());
}

int solution(int distance, vector<int> rocks, int n) {
    initialize(distance, rocks);
    
    int left = 0;
    int right = distance;
    while (left <= right) {
        const int mid = (left + right) / 2;
        
        int baseIdx = 0;
        int delRockCnt = 0;
        for (int i = 1; i < rocks.size(); ++i) {
            if (mid < (rocks[i] - rocks[baseIdx]))
                baseIdx = i;
            else
                delRockCnt++;
        }
        
        if (delRockCnt > n)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return left;
}
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

int solution(vector<vector<string>> clothes) {
    int result = 1;
    unordered_map<string, int> m;
    
    for (auto iter : clothes)
        m[iter[1]]++;
    
    for (auto iter : m)
        result *= (1 + iter.second);
    
    return result - 1;
}
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string solution(vector<int> numbers) {
    vector<string> nums(numbers.size());
    for (int i = 0; i < numbers.size(); ++i)
        nums[i] = to_string(numbers[i]);
    
    sort(nums.begin(), nums.end(), [](string& a, string& b){ return a + b > b + a; });
    if ("0" == nums[0]) return nums[0];
    
    string answer = "";
    for (auto& iter : nums) answer += iter;
    return answer;
}
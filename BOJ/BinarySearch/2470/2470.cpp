#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

using Long = long long;

vector<Long> v;
pair<Long,Long> result;
const Long SCORE_INIT = 10000000000LL;
Long score = SCORE_INIT;

void input() {
    Long N, temp;
    scanf("%lld", &N);
    for (Long i = 0LL; i < N; ++i) {
        scanf("%lld", &temp);
        v.push_back(temp);
    }
}

void initforTC() {
    v.clear();
    result.first = 0LL;
    result.second = 0LL;
    score = SCORE_INIT;
}
pair<Long,Long> TC01() { initforTC(); v.assign({-2,4,-99,-1,98}); return make_pair(-99,98); }
pair<Long,Long> TC02() { initforTC(); v.assign({-5,-4,-3,-2,-1}); return make_pair(-2,-1); }
pair<Long,Long> TC03() { initforTC(); v.assign({-3,1,2,10}); return make_pair(-3,2); }
pair<Long,Long> TC04() { initforTC(); v.assign({-2,-4,-5}); return make_pair(-4,-2); }
pair<Long,Long> TC05() { initforTC(); v.assign({1,2,-100,-1000}); return make_pair(1,2); }
pair<Long,Long> TC06() { initforTC(); v.assign({-3,-1,1,10}); return make_pair(-1,1); }
pair<Long,Long> TC07() { initforTC(); v.assign({-99,-2,-1,1,98,100,101}); return make_pair(-1,1); }
pair<Long,Long> TC08() { initforTC(); v.assign({1,2,3,4,5}); return make_pair(1,2); }
pair<Long,Long> TC09() { initforTC(); v.assign({-1,-2,-3,-4,-5}); return make_pair(-2,-1); }
pair<Long,Long> TC10() { initforTC(); v.assign({-99,-60,3,7,61,130}); return make_pair(-60,61); }

//#define UNIT_TEST
//#define DEBUG_PRINT

// true : left++, false : right--
inline bool update(const Long leftValue, const Long rightValue) {
    auto diff = abs(leftValue + rightValue);
    if (score > diff) {
        score = diff;
        result.first = leftValue;
        result.second = rightValue;
    }
    
    bool ret;
    if ((0LL >= leftValue) && (0LL >= rightValue)) ret = true;
    else if ((0LL <= leftValue) && (0LL <= rightValue)) ret = false;
    else if (0LL > leftValue + rightValue) ret = true;
    else ret = false;
#ifdef DEBUG_PRINT
    printf("lv:%lld, rv:%lld, diff:%lld, score:%lld, result1:%lld, result2:%lld, ret:%s\n"
        , leftValue, rightValue, diff, score, result.first, result.second,
        ret ? "true" : "false");
#endif
    return ret;
}

#ifndef UNIT_TEST
void solution() {
#else
void solution(pair<Long,Long> answer) {
#endif
    sort(v.begin(), v.end());
    result.first = v.front();
    result.second = v.back();
    
    Long left = 0LL;
    Long right = v.size() - 1LL;
    while (left < right) {
        if (update(v[left], v[right]))
            left++;
        else
            right--;
    }
#ifndef UNIT_TEST
    printf("%lld %lld\n", result.first, result.second);
#else
    printf("%s, %lld==%lld, %lld==%lld\n"
    , ((answer.first == result.first) && (answer.second == result.second)) ? "Pass" : "Fail"
    , answer.first, result.first
    , answer.second, result.second);
#endif
}

int main() {
#ifndef UNIT_TEST
    input();
    solution();
#else
    solution(TC01());
    solution(TC02());
    solution(TC03());
    solution(TC04());
    solution(TC05());
    solution(TC06());
    solution(TC07());
    solution(TC08());
    solution(TC09());
    solution(TC10());
#endif
    return 0;
}
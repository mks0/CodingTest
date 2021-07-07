#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

class Prime {
public:
    Prime(const size_t N) : _v(N) {
        _v[0] = _v[1] = true;
        for (size_t i = 2U; i < N; ++i)
            if (!_v[i])
                for (size_t j = i * i; j < N; j += i) _v[j] = true;
    }
    bool IsPrime(const size_t N) const {
        return N < _v.size() ? !_v[N] : false;
    }
private:
    vector<bool> _v;
};

int solution(string numbers) {
    sort(numbers.begin(), numbers.end(), greater<char>());
    Prime p(stoi(numbers) + 1);
    unordered_set<int> us;
    for (int R = 1; R <= numbers.size(); ++R) {
        do {
            if ('0' != numbers[0]) {
                const auto var = stoi(numbers.substr(0, R));
                if (p.IsPrime(var)) us.insert(var);
            }
        } while (prev_permutation(numbers.begin(), numbers.end()));
    }
    return us.size();
}
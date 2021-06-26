#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool solution(vector<string> phone_book) {
    sort(phone_book.begin(), phone_book.end());
    
    const auto endIter = phone_book.end() - 1;
    for (auto iter = phone_book.begin(); iter != endIter; iter++)
        if (0 == (*(iter + 1)).find(*iter))
            return false;
    return true;
}
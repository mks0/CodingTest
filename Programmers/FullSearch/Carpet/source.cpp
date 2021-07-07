#include <string>
#include <vector>
using namespace std;

vector<int> solution(int brown, int yellow) {
    for (int yRow = 1; yRow <= yellow; ++yRow) { // yellow 가로/세로 찾기
        for (int yCol = 1; yCol <= yRow; ++yCol) { // 가로 >= 세로
            if (yellow != yRow * yCol) continue;
            if (brown == (yRow + 2) * 2 + yCol * 2)
                return {yRow + 2, yCol + 2};
        }
    }
}
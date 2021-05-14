#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void input(int& N, vector<int>& A, int& M, vector<int>& Ms)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int temp;
    
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> temp;
        A.push_back(temp);
    }
    
    cin >> M;
    for (int i = 0; i < M; ++i) {
        cin >> temp;
        Ms.push_back(temp);
    }
}

void solution(const int N, vector<int>& A, const int M, const vector<int>& Ms) {
    sort(A.begin(), A.end());
    for (const auto& iter : Ms) {
        int left = 0;
        int right = A.size() - 1;
        int mid;
        int result = 0;
        while (left <= right) {
            mid = (left + right) / 2;
            if (iter == A[mid]) {
                result = 1;
                break;
            }
            else if (iter < A[mid]) right = mid - 1;
            else left = mid + 1;
        }
        cout << result << "\n";
    }
}

int main()
{
    int N, M;
    vector<int> A, Ms;
    input(N, A, M, Ms);
    solution(N, A, M, Ms);
    return 0;
}
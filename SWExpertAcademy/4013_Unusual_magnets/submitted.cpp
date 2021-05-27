#include <iostream>
#include <vector>
#include <deque>
using namespace std;

class Magnet {
public:
	Magnet(const vector<int>& _v, const int _scale)
		: left(nullptr), right(nullptr), dq(), scale(_scale), rotFlag(0) {
		for (const auto iter : _v) dq.push_back(iter);
	}
	Magnet(const int _scale)
		: left(nullptr), right(nullptr), dq(), scale(_scale), rotFlag(0) {}
	void push_back(const vector<int>& v) { for (const auto iter : v) dq.push_back(iter); }
	void push_back(const int v) { dq.push_back(v); }
	void clear() { dq.clear(); rotFlag = 0; }

	void Rotate() {
		if (0 != rotFlag) {
			if (1 == rotFlag) {
				auto t = dq.back();
				dq.pop_back();
				dq.push_front(t);
			}
			else {
				auto t = dq.front();
				dq.pop_front();
				dq.push_back(t);
			}
			rotFlag = 0;
		}
	}

	int GetLeftEdge() const { return dq[6]; }
	int GetRightEdge() const { return dq[2]; }
	int GetScore() const { return dq[0] * scale; }
	void SetRotateFlag(const int flag) { rotFlag = flag; }

	Magnet* left;
	Magnet* right;

private:
	deque<int> dq;
	const int scale;
	int rotFlag;
};

int Action(vector<Magnet>& magnet, const vector<pair<int, int>>& rotateTry) {
	for (const auto& iter : rotateTry) {
		Magnet* pt = &magnet[iter.first - 1];
		pt->SetRotateFlag(iter.second);

		int sign = -1;
		while (pt->left) {
			if (pt->GetLeftEdge() != pt->left->GetRightEdge()) pt->left->SetRotateFlag(iter.second * sign);
			else break;
			pt = pt->left;
			sign *= -1;
		}

		pt = &magnet[iter.first - 1];
		sign = -1;
		while (pt->right) {
			if (pt->GetRightEdge() != pt->right->GetLeftEdge()) pt->right->SetRotateFlag(iter.second * sign);
			else break;
			pt = pt->right;
			sign *= -1;
		}

		for (auto& magIter : magnet) magIter.Rotate();
	}

	int sum = 0;
	for (auto& magIter : magnet)
		sum += magIter.GetScore();
	return sum;
}

int main(int argc, char** argv)
{	
	int test_case;
	int T;
	scanf("%d", &T);
	
	vector<Magnet> magnet{ {1},{2},{4},{8} };
	for (int i = 0; i < 3; ++i) {
		magnet[i].right = &magnet[i + 1];
		magnet[i + 1].left = &magnet[i];
	}
	
	for(test_case = 1; test_case <= T; ++test_case)	{
		int K;
		scanf("%d", &K);
		for (int j = 0; j < 4; ++j) {
			for (int k = 0; k < 8; ++k) {
				int temp;
				scanf("%d", &temp);
				magnet[j].push_back(temp);
			}
		}

		vector<pair<int, int>> rotateTry;
		for (int j = 0; j < K; ++j) {
			int temp1, temp2;
			scanf("%d %d", &temp1, &temp2);
			rotateTry.push_back(make_pair(temp1, temp2));
		}
		printf("#%d %d\n", test_case, Action(magnet, rotateTry));
		for (int j = 0; j < 4; ++j) magnet[j].clear();
	}
	return 0;
}
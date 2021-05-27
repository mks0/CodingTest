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

void solution() {
	vector<Magnet> magnet{ {1},{2},{4},{8} };
	for (int i = 0; i < 3; ++i) {
		magnet[i].right = &magnet[i + 1];
		magnet[i + 1].left = &magnet[i];
	}

	int T;
	scanf("%d", &T);

	vector<int> answer;

	for (int i = 0; i < T; ++i) {
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

		answer.push_back(Action(magnet, rotateTry));
		//printf("#%d %d\n", i + 1, Action(magnet, rotateTry));

		for (int j = 0; j < 4; ++j) magnet[j].clear();
	}
	
	for (int i = 0; i < T; ++i)
		printf("#%d %d\n", i + 1, answer[i]);
}

void unitTest_reset(vector<Magnet>& magnet, vector<pair<int, int>>& rotateTry) {
	for (auto& iter : magnet) iter.clear();
	rotateTry.clear();
}

void unitTest_input01(vector<Magnet>& magnet, vector<pair<int, int>>& rotateTry) {
	magnet[0].push_back({ 0,0,1,0,0,1,0,0 });
	magnet[1].push_back({ 1,0,0,1,1,1,0,1 });
	magnet[2].push_back({ 0,0,1,0,1,1,0,0 });
	magnet[3].push_back({ 0,0,1,0,1,1,0,1 });
	
	rotateTry.push_back(make_pair(1, 1));
	rotateTry.push_back(make_pair(3, -1));
}
void unitTest_output01(vector<Magnet>& magnet, vector<pair<int, int>>& rotateTry) {
	printf("정답:10, 계산:%d\n", Action(magnet, rotateTry));
}

void unitTest_input02(vector<Magnet>& magnet, vector<pair<int, int>>& rotateTry) {
	magnet[0].push_back({ 1, 0, 0, 1, 0, 0, 0, 0 });
	magnet[1].push_back({ 0, 1, 1, 1, 1, 1, 1, 1 });
	magnet[2].push_back({ 0, 1, 0, 1, 0, 0, 1, 0 });
	magnet[3].push_back({ 0, 1, 0, 0, 1, 1, 0, 1 });

	rotateTry.push_back(make_pair(3, 1));
	rotateTry.push_back(make_pair(1, 1));
}
void unitTest_output02(vector<Magnet>& magnet, vector<pair<int, int>>& rotateTry) {
	printf("정답:14, 계산:%d\n", Action(magnet, rotateTry));
}

void unitTest_input03(vector<Magnet>& magnet, vector<pair<int, int>>& rotateTry) {
	magnet[0].push_back({ 0,0,1,1,1,1,1,1 });
	magnet[1].push_back({ 1,1,1,1,1,0,1,0 });
	magnet[2].push_back({ 0,0,0,0,1,0,0,1 });
	magnet[3].push_back({ 0,1,0,1,0,1,0,1 });

	rotateTry.push_back(make_pair(4, -1));
	rotateTry.push_back(make_pair(3, 1));
	rotateTry.push_back(make_pair(4, -1));
	rotateTry.push_back(make_pair(3, -1));
	rotateTry.push_back(make_pair(1, -1));
}
void unitTest_output03(vector<Magnet>& magnet, vector<pair<int, int>>& rotateTry) {
	printf("정답:3, 계산:%d\n", Action(magnet, rotateTry));
}

void unitTest() {
	vector<pair<int, int>> rotateTry;
	vector<Magnet> magnet{ {1},{2},{4},{8} };
	for (int i = 0; i < 3; ++i) {
		magnet[i].right = &magnet[i + 1];
		magnet[i + 1].left = &magnet[i];
	}
	unitTest_input01(magnet, rotateTry);
	unitTest_output01(magnet, rotateTry);
	unitTest_reset(magnet, rotateTry);

	unitTest_input02(magnet, rotateTry);
	unitTest_output02(magnet, rotateTry);
	unitTest_reset(magnet, rotateTry);

	unitTest_input03(magnet, rotateTry);
	unitTest_output03(magnet, rotateTry);
	unitTest_reset(magnet, rotateTry);
}

int main() {
	solution();
	//unitTest();
	return 0;
}
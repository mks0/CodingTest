#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

enum DIR { NONE, UP, DOWN, LEFT, RIGHT };
const int di[] = { 0, -1, 1,  0, 0};
const int dj[] = { 0,  0, 0, -1, 1};

int mapSize, endTime, virusCnt;

class VirusGroup {
public:
	void Init(int _i, int _j, int _hp, int _next) {
		i = _i;
		j = _j;
		hp = _hp;
		next = static_cast<DIR>(_next);
	}
	void Move() {
		i += di[next];
		j += dj[next];
		if (IsKill()) Kill();
	}
	inline bool IsDied() const { return 0 == hp; }
	inline int GetKey() const { return i * 1000 + j; }
private:
	inline bool IsKill() const { return (0 == i) || (0 == j) || (mapSize - 1 == i) || (mapSize - 1 == j); }
	void Kill() {
		hp /= 2;
		auto dir = static_cast<int>(next);
		next = static_cast<DIR>((0 == dir % 2) ? dir - 1 : dir + 1);
	}
	int i, j;
public:
	int hp;
	DIR next;
};

VirusGroup v[1000];

void Input() {
	scanf("%d %d %d", &mapSize, &endTime, &virusCnt);
	for (int i = 0; i < virusCnt; ++i) {
		int _i, _j, _hp, _next;
		scanf("%d %d %d %d", &_i, &_j, &_hp, &_next);
		v[i].Init(_i, _j, _hp, _next);
	}
}

void Merge(const unordered_map<int, vector<int>>& um) {
	for (const auto& iter : um) {
		if (1U >= iter.second.size()) continue;
		DIR maxNext = NONE;
		int maxHP = 0;
		int accHP = 0;
		for (int k = 0; k < static_cast<int>(iter.second.size()); ++k) {
			if (maxHP < v[iter.second[k]].hp) {
				maxHP = v[iter.second[k]].hp;
				maxNext = v[iter.second[k]].next;
			}
			accHP += v[iter.second[k]].hp;
			v[iter.second[k]].hp = 0;
		}
		v[iter.second[0]].hp = accHP;
		v[iter.second[0]].next = maxNext;
	}
}

void Simulation() {
	for (int times = 0; times < endTime; ++times) {
		unordered_map<int, vector<int>> um;
		bool flag = false;
		for (int i = 0; i < virusCnt; ++i) {
			if (v[i].IsDied()) continue;
			v[i].Move();
			um[v[i].GetKey()].push_back(i);
			if (um[v[i].GetKey()].size() > 1U) flag = true;
		}
		if (flag) Merge(um);
	}
}

int GetResult() {
	int result = 0;
	for (int i = 0; i < virusCnt; ++i) result += v[i].hp;
	return result;
}

int main(int argc, char** argv) {
	int T;
	//freopen("sample_input.txt", "r", stdin);
	scanf("%d", &T);
	for (int test_case = 1; test_case <= T; ++test_case) {
		Input();
		Simulation();
		printf("#%d %d\n", test_case, GetResult());
	}
	return 0;
}
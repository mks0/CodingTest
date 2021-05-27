#include <iostream>
#include <vector>
#include <queue>
using namespace std;

enum DIR { STAY, UP, RIGHT, DOWN, LEFT };
const int dx[] = { 0, -1, 0, 1, 0 };
const int dy[] = { 0, 0, 1, 0, -1 };
struct Pos { Pos(const int _x = 0, const int _y = 0) : x(_x), y(_y) {} int x, y; };
class User {
public:
	User(const Pos& _pos, const vector<DIR>& _schedule)
		: pos(_pos), schedule(_schedule) {}
	Pos pos;
	vector<DIR> schedule;
};
class BC {
public:
	BC(const Pos& _pos, const int _coverage, const int _performance, const int _idx)
		: pos(_pos), coverage(_coverage), performance(_performance), idx(_idx) {}
	const Pos pos;
	const int coverage;
	const int performance;
	const int idx;
};
class Block {
public:
	Block() : bcID(), visited(false) {}
	void Reset() { bcID.clear(); visited = false; }
	vector<int> bcID;
	bool visited;
};
const int MAX_ROW = 11;
const int MAX_COL = 11;

int GetScore(const vector<BC>& vBC, const vector<int>& a, const vector<int>& b) {
	const auto* minV = (a.size() >= b.size()) ? &b : &a;
	const auto* maxV = (a.size() < b.size()) ? &b : &a;

	auto min_first = make_pair(0, -1);
	auto min_second = make_pair(0, -1);
	for (const auto& iter : (*minV)) {
		if (min_first.first < vBC[iter].performance) {
			min_second.first = min_first.first;
			min_second.second = min_first.second;
			min_first.first = vBC[iter].performance;
			min_first.second = iter;
		}
		else if (min_second.first < vBC[iter].performance) {
			min_second.first = vBC[iter].performance;
			min_second.second = iter;
		}
	}

	auto max_first = make_pair(0, -1);
	auto max_second = make_pair(0, -1);
	for (const auto& iter : (*maxV)) {
		if (max_first.first < vBC[iter].performance) {
			max_second.first = max_first.first;
			max_second.second = max_first.second;
			max_first.first = vBC[iter].performance;
			max_first.second = iter;
		}
		else if (max_second.first < vBC[iter].performance) {
			max_second.first = vBC[iter].performance;
			max_second.second = iter;
		}
	}

	if (-1 == max_first.second && -1 == min_first.second) return 0;
	if (-1 == max_second.second && -1 == min_first.second) return max_first.first;
	if (max_first.second != min_first.second) return max_first.first + min_first.first;
	if (-1 == min_first.second) return max_second.first + min_first.first;

	return max_first.first + max(max_second.first, min_second.first);
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	//freopen("sample_input.txt", "r", stdin);
	scanf("%d", &T);
	auto m = new Block[MAX_ROW][MAX_COL];

	for (test_case = 1; test_case <= T; ++test_case) {
		// inputs
		int Ms, BCs;
		scanf("%d %d", &Ms, &BCs);
		vector<User> vUser;
		for (int i = 0; i < 2; ++i) {
			vector<DIR> schedule;
			for (int j = 0; j < Ms; ++j) {
				int k;
				scanf("%d", &k);
				schedule.push_back(static_cast<DIR>(k));
			}
			Pos pos;
			if (0 == i) { pos.x = 1; pos.y = 1; }
			else { pos.x = 10; pos.y = 10; }
			vUser.push_back(User(pos, schedule));
		}
		vector<BC> vBC;
		for (int i = 0; i < BCs; ++i) {
			int BCx, BCy, BCcov, BCperf;
			scanf("%d %d %d %d", &BCy, &BCx, &BCcov, &BCperf);
			vBC.push_back(BC(Pos(BCx, BCy), BCcov, BCperf, i));
		}

		// map setting
		for (const auto& iter : vBC) {
			queue<pair<Pos, int>> q;
			q.push(make_pair(iter.pos, iter.coverage));
			while (!q.empty()) {
				auto top = q.front();
				if (0 > top.second) break;
				if (!m[top.first.x][top.first.y].visited) {
					m[top.first.x][top.first.y].visited = true;
					m[top.first.x][top.first.y].bcID.push_back(iter.idx);
				}
				if (0 < top.first.x + dx[UP] && !m[top.first.x + dx[UP]][top.first.y].visited)
					q.push(make_pair(Pos(top.first.x + dx[UP], top.first.y), top.second - 1));
				if (MAX_COL > top.first.y + dy[RIGHT] && !m[top.first.x][top.first.y + dy[RIGHT]].visited)
					q.push(make_pair(Pos(top.first.x, top.first.y + dy[RIGHT]), top.second - 1));
				if (MAX_ROW > top.first.x + dx[DOWN] && !m[top.first.x + dx[DOWN]][top.first.y].visited)
					q.push(make_pair(Pos(top.first.x + dx[DOWN], top.first.y), top.second - 1));
				if (0 < top.first.y + dy[LEFT] && !m[top.first.x][top.first.y + dy[LEFT]].visited)
					q.push(make_pair(Pos(top.first.x, top.first.y + dy[LEFT]), top.second - 1));
				q.pop();
			}
			for (int i = 1; i < MAX_ROW; ++i) for (int j = 1; j < MAX_COL; ++j) m[i][j].visited = false;
		}

		// simulation
		auto sum = GetScore(vBC, m[vUser[0].pos.x][vUser[0].pos.y].bcID, m[vUser[1].pos.x][vUser[1].pos.y].bcID);
		for (int i = 0; i < Ms; ++i) {
			for (int j = 0; j < 2; ++j) {
				vUser[j].pos.x += dx[vUser[j].schedule[i]];
				vUser[j].pos.y += dy[vUser[j].schedule[i]];
			}
			sum += GetScore(vBC, m[vUser[0].pos.x][vUser[0].pos.y].bcID, m[vUser[1].pos.x][vUser[1].pos.y].bcID);
		}
		printf("#%d %d\n", test_case, sum);
		for (int i = 1; i < MAX_ROW; ++i) for (int j = 1; j < MAX_COL; ++j) m[i][j].Reset();
	}
	return 0;
}
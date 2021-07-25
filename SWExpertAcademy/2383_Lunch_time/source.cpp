#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAX_STEPS = 2;
const int STEP_CAPACITY = 3;
struct Step {
	int r, c;
	int len;
} steps[MAX_STEPS];

const int MAX_PEOPLE = 10;
struct People {
	int r, c;
} people[MAX_PEOPLE];
int peopleN;
int N;

void Input() {
	scanf("%d", &N);
	peopleN = 0;
	int stepN = 0;
	for (int r = 0; r < N; ++r) {
		for (int c = 0; c < N; ++c) {
			int temp;
			scanf("%d", &temp);
			if (1 == temp) {
				people[peopleN].r = r;
				people[peopleN++].c = c;
			}
			else if (2 <= temp) {
				steps[stepN].r = r;
				steps[stepN].c = c;
				steps[stepN++].len = temp;
			}
		}
	}
}

void Simulation(int& result, const int standard) {
	int state[MAX_STEPS][MAX_PEOPLE];
	int idx[MAX_STEPS]{ 0, 0 };

	for (int i = 0; i < peopleN; ++i) {
		const int pt = (0 == (standard & (1 << i))) ? 0 : 1;
		const int temp = abs(people[i].r - steps[pt].r) + abs(people[i].c - steps[pt].c);
		// 계단까지의 거리가 현재까지의 최소값보다 크면 더 계산할 필요 없음
		if (temp + 1 >= result) return;
		state[pt][idx[pt]++] = temp;
	}

	for (int i = 0; i < MAX_STEPS; ++i)
		sort(state[i], state[i] + idx[i]);

	for (int i = 0; i < MAX_STEPS; ++i) {
		for (int j = STEP_CAPACITY; j < idx[i]; ++j) {
			const auto diff = state[i][j] - state[i][j - STEP_CAPACITY] - steps[i].len;
			if (0 > diff)
				state[i][j] -= diff;
		}
	}

	const auto maxV = max((0 < idx[0]) ? state[0][idx[0] - 1] + steps[0].len : 0,
					(0 < idx[1]) ? state[1][idx[1] - 1] + steps[1].len : 0);

	result = min(maxV, result);
}

int Solution() {
	int result = 99999;
	
	// 조합 조건 탐색 방법에 이진수 이용
	auto endValue = static_cast<int>(pow(2, peopleN));
	for (int i = 0; i < endValue; ++i)
		Simulation(result, i);
	return result + 1;	// 통과하는데 걸리는 1 time 추가
}

int main(int argc, char** argv)
{
	int T;
	//freopen("sample_input.txt", "r", stdin);
	scanf("%d", &T);
	for (int test_case = 1; test_case <= T; ++test_case) {
		Input();
		printf("#%d %d\n", test_case, Solution());
	}
	return 0;
}
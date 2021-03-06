# K번째 수
## 문제 링크
[백준 1300](https://www.acmicpc.net/problem/1300)
## 분류
이진탐색
## 언어
C++17
## 주의사항
* 탐색 값이 없는 경우는 큰 수로 봐야 함.
  + N = 3, K = 7을 구하는 경우
    - 5보다 작거나 같은 원소의 수는 총 6개 -> 6번째 수는 5.
	- 6보다 작거나 같은 원소의 수는 총 8개 -> 8번째 수는 6.
	- 6이 2개가 있다는 의미이므로 7번째 수는 6.
## 특이사항
* 규칙 파악 못하여 풀이 시도도 못함
## 접근 방법
* 무엇을 찾는가?
  + K번째에 오는 수
* 찾는 범위는?
  + 1 ~ K
* 찾는 범위에 대한 증명
  + N에 대한 N x N 행렬은 1 <= i <= N, 1 <= j <= N의 조합에 의해 i x j 원소들로 구성되고, K는 오름차순 정렬에서의 순번이라고 정의한다.
  + 가정 : N 행렬 내 임의의 K번째 원소는 K 값보다 작거나 같음. 
  + N = 1, 행렬 원소는 1개
    - 1번째 원소는 1 -> 가정 성립.
  + (구체 예시) N = 2, 행렬 원소는 4개
    - N = 1 행렬보다 큰 조합은 1 x 2, 2 x 1, 2 x 2
	- 4번째 원소는 4 -> 가정 성립.
	- 2 ~ 3번째 원소는 2 -> 가정 성립.
	- 1번째 원소는 1 -> 가정 성립.
  + (구체 예시) N = 3, 행렬 원소는 9개
    - N = 2 행렬보다 큰 조합은 2 x 3, 3 x 2, 3 x 3
	- 9번째 원소는 9 -> 가정 성립.
	- 7 ~ 8번째 원소는 6 -> 가정 성립
	- 6번째 원소는 4 -> 가정 성립.
	- 1 ~ 5번째 원소에 대해, N = 2 행렬에서과 중복되는 원소는 3개이므로 N = 2 대비 추가되는 2개의 원소를 최악의 케이스인 4 ~ 5번째 원소로 가정해도 오름차순 특성에 의해 6번째 원소인 4보다 작거나 같음 -> 가정 성립.
  + (구체 예시) N = 4, 행렬 원소는 16개
    - N = 3 행렬보다 큰 조합은 3 x 4, 4 x 3, 4 x 4
	- 16번째 원소는 16 -> 가정 성립.
	- 14 ~ 15번째 원소는 12 -> 가정 성립.
	- 13번째 원소는 9 -> 가정 성립.
	- 1 ~ 12번째 원소에 대해, N = 3 행렬에서과 중복되는 원소는 8개이므로 N = 3 대비 추가되는 4개의 원소를 최악의 케이스인 9 ~ 12번째 원소로 가정해도 오름차순 특성에 의해 13번째 원소인 9보다 작거나 같음 -> 가정 성립.
  + N 행렬 원소는 N<sup>2</sup>개 (N >= 2)
    - N - 1 행렬보다 큰 조합은 (N-1) x N, N x (N-1), N x N
	- N<sup>2</sup>번째 원소는 N<sup>2</sup> -> 가정 성립
	- N<sup>2</sup>-2 ~ N<sup>2</sup>-1번째 원소는 N<sup>2</sup> - N -> 가정 성립
	- N<sup>2</sup>-3번째 원소는 (N-1)<sup>2</sup> -> 가정 성립
	- 1~N<sup>2</sup>-4번째 원소에 대해, N-1 행렬에서과 중복되는 원소는 (N-1)<sup>2</sup>-1개이므로 N-1 대비 추가되는 2(N-2)개의 원소를 최악의 케이스인 (N-1)<sup>2</sup> ~ N<sup>2</sup>-4번째 원소로 가정해도 오름차순 특성에 의해 N<sup>2</sup>-3번째 원소인 (N-1)<sup>2</sup>보다 작거나 같음 -> 가정 성립.
  + 따라서 가정(N 행렬 내 임의의 K번째 원소는 K 값보다 작거나 같음)은 참임
  + ![843700C3-04F3-4D5E-AD65-77A955BE2F8D](https://user-images.githubusercontent.com/83868994/118358405-8f23d700-b5b9-11eb-9169-8fc778e74ca0.jpeg)
* left/right 조정 기준은?
  + 오름차순으로 정렬된 배열에서 특정 수 X보다 작거나 같은 수들의 총 개수 = X의 순서(X가 중복하여 나타나는 경우, '마지막' 순서.)
  + X의 마지막 순서가 K번째보다 크다면? -> K번째에 오는 수는 X보다 작거나 같다는 의미
  + X의 마지막 순서가 K번째보다 작다면? -> K번째에 오는 수는 적어도 X보다 크다는 의미
* left/right 조정 기준 값 산출은?
  + 해당 행에서 mid 값보다 작거나 같은 원소들을 카운팅하는 방식을 각 행별로 구하고 합산

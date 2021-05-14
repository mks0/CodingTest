# 예산
## 문제
[백준 12015](https://www.acmicpc.net/problem/12015)
## 분류
이진탐색
## 언어
C++17
## 주의사항
* 문제를 잘못 이해하여 이진탐색 없이 정렬 후 카운팅했다가 틀림
* LIS(Longest increasing Subsequence, 최장 증가 수열) 문제로 이진탐색 이용 필요
## 특이사항
* lower_bound는 binary_search 방식으로 구현된 알고리즘으로 O(logN) 성능임
  + 정렬된 배열 A를 대상으로 X <= A<sub>i</sub>를 만족하는 최소의 A<sub>i</sub>의 반복자를 반환하는 알고리즘
  + 예) A = {1,3,5}에서 X=4를 lower_bound로 탐색하면 A[2]=5의 반복자를 획득함   
* LIS 배열을 신규 생성하는 방법으로 접근함
  + LIS 배열을 생성하고 탐색 대상 배열을 순회하며 LIS 배열에 원소를 추가
    - 탐색 대상 원소가 LIS 배열의 마지막 원소보다 클 경우, LIS 마지막 위치에 원소 추가
    - 탐색 대상 원소가 LIS 배열의 마지막 원소보다 크지 않을 경우, lower_bound로 탐색하여 LIS의 원소와 교체
* LIS 학습 후 풀었음

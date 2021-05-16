# 숫자 카드 2
## 문제 링크
[백준 10816](https://www.acmicpc.net/problem/10816)
## 분류
이진탐색
## 언어
C++17
## 주의사항
해당사항 없음
## 특이사항
* binary_search 미사용
* std::equal_range 사용
  + 대상 배열 내 찾고자 하는 원소를 가리키는 pair 객체 반환
  + pair의 first부터 second까지 순회하는 방식으로 확인 가능
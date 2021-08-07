# 신규 아이디 추천
## 문제 링크
[프로그래머스 신규 아이디 추천]
(https://programmers.co.kr/learn/courses/30/lessons/72410?language=cpp)
## 분류
2021 카카오 블라인드 채용
## 언어
C++17
## 주의사항
해당사항 없음
## 접근 방법
각 절차 별 작업을 문자열에 적용
## 기타 사항
* 대소문자 변환
  + transform(s.begin(), s.end(), s.begin(), ::tolower) // 소문자 변환
  + 대문자 변환 시엔 ::toupper 이용
  + algorithm 헤더 필요
* STL의 find 함수 비교 대상은 end(). string에서는 string::npos임.
* C++11부터 문자열에 대해 front()/back()/pop_back() 메소드 지원됨.
# 특이한 자석
## 문제 링크(로그인 필요)
[SWExpertAcademy 4013]
## 분류
없음(모의 SW 역량테스트)
## 언어
C++17
## 주의사항
* 테스트 환경이 없는 줄 알고 구축하는데 많은 시간 소요
* 회전하는 자석 양옆의 자석 선택 시 왼쪽/오른쪽 전환 때 반드시 초기화 필요 
## 접근 방법
* 자석 클래스 작성
  + 회전 기능, 왼쪽/오른쪽 날 확인 기능, 점수 산정 기능
    - 회전용 자료 구조는 deque(STL) 이용
* 회전 작업 순서에 따라 대상 자석 객체를 선택 후 왼쪽/오른쪽 자석들의 회전 여부 체크
* 회전 여부가 체크된 자석들을 회전함.
* 회전이 종료되면 점수 산정
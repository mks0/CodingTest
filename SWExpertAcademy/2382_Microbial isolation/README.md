# 미생물 격리
## 문제 링크(로그인 필요)
[SWExpertAcademy 2382]
## 분류
없음(모의 SW 역량테스트)
## 언어
C++17
## 주의사항
* 3개 이상의 미생물 군집이 병합될 때, 방향 설정 유의
## 접근 방법
* 미생물 군집(여기서는 바이러스로 정의) 클래스 배열 선언
* 격리 시간 M 동안 미생물 군집 이동 모의
  + 이동 시 약품에 걸리는 경우 바이러스 1/2 소멸 및 방향 전환
  + 이동 시 다른 미생물 군집과 같은 위치에 있게 되는 경우 체크
    - 병합 케이스는 매 단일 격리 모의가 종료되면 일괄 갱신
## 기타 사항
* 전체 맵을 별도 정의하지 않고 unordered_map을 이용하여 중첩 케이스 체크함
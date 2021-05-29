# 활주로 건설
## 문제 링크(로그인 필요)
[SWExpertAcademy 4014]
## 분류
없음(모의 SW 역량테스트)
## 언어
C++17
## 주의사항
해당사항 없음
## 접근 방법
* 맵의 행/열 줄 별로 확인하여 건설에 문제가 없다면 카운팅
  + Rising/Falling Edge 케이스로 구분하여 조건식 삽입
    - Rising Edge는 Edge 전 값 개수가 X 이상이면 Pass
	  - Pass 카운팅 값이 X를 초과하더라도 모두 0 처리
	- Falling Edge는 Edge 후 값 개수가 X 도달하면 Pass
	  - Pass 카운팅 값을 X만큼만 제하여 처리 
## 기타 사항
* 최적화 필요. 좋은 사례 참조 필요.
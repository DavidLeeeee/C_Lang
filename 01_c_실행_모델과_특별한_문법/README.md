# 토픽 1. C의 실행 모델과 특별한 문법
_권장 기간: 4주_

## 목표
C의 "기본 문법"이 아니라, **C다운 문법과 메모리 관점**을 몸에 익힌다.

## 핵심 개념

### 1) 선언 해독
반드시 직접 읽고 쓰는 수준까지 가야 한다.

- 포인터
- 이중 포인터
- 함수 포인터
- 배열의 포인터
- 포인터 배열
- `typedef`를 이용한 타입 정리

예시로 아래 차이를 입으로 설명할 수 있어야 한다.

- `int *a[3]`
- `int (*a)[3]`
- `int (*fp)(int, int)`

### 2) 배열과 포인터의 관계
여기서 초반 혼란이 많이 난다.

- 배열은 언제 포인터로 decay되는가
- `sizeof(array)`와 `sizeof(pointer)`의 차이
- 문자열 리터럴과 문자 배열의 차이
- 포인터 연산이 왜 element size를 고려하는가

### 3) 저장 기간, 스코프, 링키지
- automatic storage duration
- static storage duration
- thread storage duration
- dynamic storage duration
- scope
- internal linkage / external linkage
- `static`, `extern`

### 4) 데이터 레이아웃
- `struct`
- `union`
- padding
- alignment
- `offsetof`
- bit-field는 읽을 줄만 알고 남용하지 않기

### 5) 전처리기
- `#include`
- include guard
- object-like macro
- function-like macro
- 조건부 컴파일
- 매크로의 부작용

### 6) C에서 특히 중요한 키워드
- `const`
- `volatile`
- `restrict`
- `inline`

## 반드시 실습할 것

- [ ] 포인터 선언 20개를 손으로 해석하기
- [ ] `struct` 5개를 만들고 `sizeof`, `alignof`, `offsetof` 비교하기
- [ ] 전역 변수/정적 변수/지역 변수의 lifetime 비교하기
- [ ] 헤더(`.h`)와 구현(`.c`) 파일을 나눠 작은 라이브러리 만들기
- [ ] 아래 3개를 직접 구현하기
  - [ ] 동적 배열 `vector`
  - [ ] 문자열 빌더 `string_builder`
  - [ ] 바이너리 파일 파서 또는 hexdump 도구

## 완료 조건

아래 질문에 막힘 없이 답할 수 있으면 통과다.

- 배열과 포인터는 왜 "비슷하지만 동일하지 않은가?"
- `static`은 함수 안, 파일 스코프, 전역에서 각각 무슨 의미인가?
- `struct` padding은 왜 생기며, 언제 성능이나 ABI에 영향을 주는가?
- `const`와 `volatile`은 왜 서로 다른 문제를 해결하는가?
- 함수 포인터는 어떤 상황에서 유용한가?

## 추천 자료

- **Modern C** — Jens Gustedt
- GCC / Clang C 상태 페이지
- CMake는 이 토픽에서 아직 깊게 들어가지 말고, "멀티 파일 프로젝트" 정도만 시작

# 토픽 4. CPU 아키텍처, 성능, 동시성
_권장 기간: 6주_

## 목표
이 단계에서는 프로그램이 CPU 위에서 실제로 어떻게 실행되는지와,  
왜 같은 알고리즘도 **메모리 접근 패턴과 동시성 설계**에 따라 성능이 갈리는지를 배운다.

## 핵심 개념

### 1) 어셈블리 읽기 입문
- x86-64 레지스터
- 호출 규약
- stack frame
- 함수 호출/반환
- 주소 계산
- 분기

### 2) CPU 관점의 성능
- cache line
- locality
- TLB
- branch prediction
- instruction throughput/latency를 대충이라도 체감하기
- false sharing

### 3) 최적화와 코드 생성
- `-O0`, `-O2`, `-O3` 차이
- 인라이닝
- loop optimization
- aliasing이 최적화에 미치는 영향
- 불필요한 추상화가 실제 코드를 어떻게 바꾸는지 보기

### 4) 성능 측정
- microbenchmark 작성 주의
- `perf stat`
- `perf record`
- `perf report`

### 5) 동시성
- thread
- mutex
- condition variable
- atomic
- data race
- happens-before 개념
- acquire / release / seq_cst의 직관
- lock-based design 먼저, lock-free는 나중

## 반드시 실습할 것

- [ ] 같은 C 코드로 `-O0`와 `-O2` 어셈블리 비교
- [ ] 연속 메모리 접근 vs 랜덤 접근 벤치마크
- [ ] cache-friendly / cache-unfriendly 루프 비교
- [ ] `perf stat`으로 기본 카운터 보기
- [ ] `perf record` + `perf report`로 핫 함수 찾기
- [ ] TSan으로 data race 하나 잡기
- [ ] mutex 기반 bounded queue 만들기
- [ ] thread pool 만들기
- [ ] 병렬 word count 만들기

## 권장 미니 프로젝트

### 프로젝트 A: thread pool
- 작업 큐
- worker thread
- graceful shutdown
- 간단한 통계 출력

### 프로젝트 B: parallel word count
- 파일 분할
- 병렬 처리
- reduce 단계 설계
- lock contention 분석

### 프로젝트 C: cache 실험 세트
- stride를 바꾸며 접근
- 배열 크기를 바꾸며 캐시/TLB 영향 보기
- 결과를 표와 그래프로 정리

## 완료 조건

- 어셈블리를 보며 함수 호출/반환, 지역 변수 접근, 분기를 대충 따라갈 수 있다.
- "이 코드는 왜 느린가?"를 감이 아니라 데이터(`perf`, 벤치마크)로 말하기 시작한다.
- race condition을 재현하고 TSan으로 검출할 수 있다.
- lock-free를 아직 깊게 못 해도, **왜 어려운지**는 설명할 수 있다.

## 여기서의 금지 사항

- lock-free를 멋있어 보인다고 먼저 파기
- benchmark를 한 번만 돌리고 결론 내리기
- 성능 문제를 컴파일러 탓만 하기
- cache/TLB/branch 영향 없이 알고리즘 복잡도만 보기

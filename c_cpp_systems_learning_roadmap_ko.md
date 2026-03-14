# C/C++ 시스템 학습서
_작성 기준: 2026-03-14_  
_대상: 웹 백엔드/FastAPI/JavaScript 경험은 있지만, 시스템·언어 내부 동작을 본격적으로 배우고 싶은 개발자_

---

## 이 학습서의 목표

이 문서는 **C 문법 암기용 요약집이 아니라**,  
**“프로그램이 실제로 메모리에서 어떻게 움직이고, 컴파일러가 무엇을 바꾸며, 운영체제와 CPU가 그 실행을 어떻게 떠받치는지”**를 몸에 익히기 위한 로드맵이다.

이 학습서를 끝냈을 때의 목표는 다음과 같다.

- C의 특별한 문법(포인터, 선언 해독, 배열/포인터 차이, struct/union, 전처리기, 링크 개념)을 설명할 수 있다.
- 메모리 오류와 UB(Undefined Behavior)를 **재현 → 디버깅 → 수정**할 수 있다.
- 컴파일, 링크, 오브젝트 파일, 심볼, ABI를 대략이 아니라 실제 도구로 확인할 수 있다.
- Linux 시스템 콜과 프로세스/스레드/가상 메모리의 관계를 코드로 이해한다.
- 어셈블리를 “외계어”가 아니라 **C 코드의 그림자**처럼 읽기 시작한다.
- Modern C++에서 **RAII, 소유권, move semantics, 템플릿, 표준 라이브러리**를 실전적으로 사용한다.
- Python/FastAPI 쪽 경험과 연결해 **네이티브 모듈/성능 개선/시스템 프로젝트**를 포트폴리오로 만든다.

---

## 학습 기준 버전

최신 표준을 무작정 좇기보다, **호환성과 실무성**을 기준으로 잡는다.

- **C**: 실습 코드는 기본적으로 `-std=c11` 또는 `-std=c17`로 작성한다.
- **C23**: 문법과 라이브러리 추가 사항은 읽고 실험하되, “선택 과목”처럼 다룬다.
- **C++**: 실습 코드는 기본적으로 `-std=c++20`으로 작성한다.
- **C++23**: 일부 유용한 기능만 선택적으로 맛본다.

> 이유: GCC는 C23을 적극 지원하고 최근에는 기본 C 모드까지 C23 계열로 바뀌었지만, Clang 쪽은 C23 지원이 여전히 부분적인 항목이 있다. C++ 쪽은 C++20을 중심축으로 두는 것이 안정적이다.

---

## 권장 학습 환경

- **OS**: Linux x86-64 우선  
  - 실제 리눅스가 가장 좋다.
  - Windows라면 WSL2로 시작해도 괜찮다.
- **컴파일러**: GCC + Clang 둘 다 사용
- **빌드**: CMake
- **디버깅/검사 도구**
  - GDB
  - AddressSanitizer (ASan)
  - UndefinedBehaviorSanitizer (UBSan)
  - ThreadSanitizer (TSan)
  - Valgrind / Memcheck
  - perf
- **보조 도구**
  - Compiler Explorer
  - `objdump`, `readelf`, `nm`
  - `strace` (선택)
  - `ltrace` (선택)

---

## 학습 운영 원칙

### 1) 문법보다 실행 모델을 먼저 본다
“이 문법이 왜 존재하는가?”를 **메모리, 호출 규약, 링킹, 성능**과 연결해서 본다.

### 2) 모든 공부는 결과물로 남긴다
각 토픽마다 반드시 아래 셋 중 하나를 만든다.

- 작은 라이브러리
- CLI 프로그램
- 디버깅/성능 분석 보고서

### 3) 모든 코드는 최소 3가지 빌드로 돌린다

- Debug
- Release (`-O2`)
- Sanitizer 빌드 (`ASan/UBSan` 또는 `TSan`)

### 4) GCC와 Clang을 둘 다 써 본다
한쪽에서 돌아간다고 끝내지 않는다.  
컴파일러를 둘 다 돌려 보면 경고, 최적화, UB 반응이 다르다. 그 차이가 아주 좋은 공부 재료다.

### 5) C와 C++을 “같은 언어”처럼 취급하지 않는다
- C는 **데이터 표현과 실행 모델**을 배우는 언어
- C++은 **저수준 제약을 유지한 채 추상화를 안전하게 쌓는 언어**

둘은 혈연관계는 깊지만, 성격은 꽤 다르다.

---

## 전체 일정 요약 (권장 28주)

| 토픽 | 기간 | 핵심 산출물 |
|---|---:|---|
| 1. C의 실행 모델과 특별한 문법 | 4주 | 동적 배열, 문자열 빌더, 바이너리 파서 |
| 2. 메모리, UB, 빌드/링크, ABI | 6주 | allocator 1종, hexdump/serializer, Python 연동 C 라이브러리 |
| 3. 운영체제와 Linux 시스템 프로그래밍 | 6주 | mini shell, tiny HTTP server, mmap 실험 |
| 4. CPU 아키텍처, 성능, 동시성 | 6주 | perf 보고서, thread pool, 병렬 word count |
| 5. Modern C++ + 캡스톤 | 6주 | RAII wrapper, C++20 기반 프로젝트, 최종 포트폴리오 |

> 주당 10~12시간 기준이다.  
> 시간이 더 적으면 기간을 늘리고, 시간이 더 많으면 토픽 내부 프로젝트를 더 깊게 판다.

---

# 토픽 1. C의 실행 모델과 특별한 문법
_권장 기간: 4주_

## 목표
C의 “기본 문법”이 아니라, **C다운 문법과 메모리 관점**을 몸에 익힌다.

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

- 배열과 포인터는 왜 “비슷하지만 동일하지 않은가?”
- `static`은 함수 안, 파일 스코프, 전역에서 각각 무슨 의미인가?
- `struct` padding은 왜 생기며, 언제 성능이나 ABI에 영향을 주는가?
- `const`와 `volatile`은 왜 서로 다른 문제를 해결하는가?
- 함수 포인터는 어떤 상황에서 유용한가?

## 추천 자료

- **Modern C** — Jens Gustedt
- GCC / Clang C 상태 페이지
- CMake는 이 토픽에서 아직 깊게 들어가지 말고, “멀티 파일 프로젝트” 정도만 시작

---

# 토픽 2. 메모리, UB, 빌드/링크, ABI
_권장 기간: 6주_

## 목표
C를 배우는 진짜 이유 중 하나는 **“왜 어떤 버그는 돌아가는 것처럼 보이는데 틀렸는지”**를 이해하는 데 있다.  
이 토픽은 바로 그 세계다. 지뢰밭이지만 몸값이 올라가는 구간이기도 하다.

## 핵심 개념

### 1) 메모리 모델의 실전 감각
- stack / heap / static storage
- `malloc`, `calloc`, `realloc`, `free`
- lifetime
- dangling pointer
- double free
- use-after-free
- memory leak

### 2) UB(Undefined Behavior)와 구현 정의/미정의 동작
- signed overflow
- out-of-bounds access
- uninitialized read
- strict aliasing
- alignment 위반
- 잘못된 포인터 캐스팅
- sequence / evaluation order 주의

### 3) 바이너리 표현
- endianness
- object representation
- byte order
- alignment
- packing을 무작정 믿지 않기

### 4) 컴파일 파이프라인
- 전처리
- 컴파일
- 어셈블
- 링크

### 5) 오브젝트 파일과 링크
- object file
- symbol
- relocation
- static library
- shared library
- dynamic linking
- ABI의 감각
- calling convention을 아주 거칠게라도 이해하기

### 6) 도구 체인
- GDB
- ASan
- UBSan
- Valgrind / Memcheck
- `objdump`
- `readelf`
- `nm`

## 반드시 실습할 것

- [ ] 의도적으로 `use-after-free` 버그를 만들고 ASan으로 잡기
- [ ] 의도적으로 signed overflow 또는 잘못된 캐스팅을 만들어 UBSan 반응 보기
- [ ] `valgrind --leak-check=full`로 메모리 누수 보고서 읽기
- [ ] `objdump -d`, `readelf -h/-S/-s`, `nm`으로 오브젝트 파일 뜯어보기
- [ ] 정적 라이브러리 1개, 공유 라이브러리 1개 만들기
- [ ] Python에서 `ctypes` 또는 `cffi`로 호출 가능한 C 라이브러리 만들기

## 권장 미니 프로젝트

### 프로젝트 A: arena allocator
- bump allocator부터 시작
- 해제는 전체 reset만 지원
- 빠른 임시 객체 생성에 사용

### 프로젝트 B: fixed-size pool allocator
- 같은 크기의 객체를 빠르게 할당/반환
- free list 구조 이해

### 프로젝트 C: serializer / deserializer
- struct를 그대로 덤프하지 말고
- 명시적 필드 단위로 바이트 직렬화
- endianness를 직접 다룬다

### 프로젝트 D: Python 연동 C 라이브러리
- 문자열 처리기
- 간단한 parser
- checksum / binary codec
- 작은 압축/인코딩 유틸

> 이 프로젝트는 네 기존 FastAPI/Python 경험과 아주 잘 연결된다.  
> “웹 개발만 하는 사람”에서 “핫패스를 네이티브로 내릴 줄 아는 사람”으로 한 단계 올라가는 좋은 교두보다.

## 완료 조건

- 메모리 오류를 재현하고, 도구로 원인을 좁히고, 수정 내용을 설명할 수 있다.
- shared library와 static library의 차이를 설명할 수 있다.
- Python에서 C 함수 하나를 직접 호출해 보고, 인자/반환값/버퍼 수명 문제를 이해한다.
- 오브젝트 파일과 실행 파일이 “그냥 빌드 결과물”이 아니라는 감각이 생긴다.

## 이 단계에서 특히 조심할 것

- “돌아가니까 맞다”는 생각
- `memcpy`/캐스팅으로 타입을 대충 우회하기
- `struct`를 네트워크/파일 포맷으로 그대로 저장하기
- 경고를 끄고 넘어가기

---

# 토픽 3. 운영체제와 Linux 시스템 프로그래밍
_권장 기간: 6주_

## 목표
이 토픽의 목적은 운영체제를 “이론 과목”으로 끝내지 않고,  
**시스템 콜, 파일 디스크립터, 프로세스, 가상 메모리, 소켓**을 손으로 다뤄 보는 것이다.

## 핵심 개념

### 1) 프로세스와 프로그램
- 프로그램은 디스크에 있는 코드
- 프로세스는 실행 중인 인스턴스
- PID
- address space
- parent / child process

### 2) 시스템 콜과 사용자 공간 / 커널 공간
- system call이 왜 필요한가
- 라이브러리 함수와 시스템 콜의 관계
- 파일 I/O, 프로세스 생성, 메모리 매핑이 어떻게 커널로 넘어가는가

### 3) 파일 디스크립터
- `open`
- `read`
- `write`
- `close`
- 표준 입력/출력/에러
- 파이프와 소켓도 결국 FD라는 감각

### 4) 프로세스 제어
- `fork`
- `exec`
- `wait`
- signal
- `sigaction`

### 5) 메모리와 가상화
- page
- virtual memory
- `mmap`
- copy-on-write
- page cache
- 파일 매핑과 anonymous mapping

### 6) 네트워크와 이벤트
- socket
- bind/listen/accept
- blocking / non-blocking
- `select` / `poll` / `epoll`
- event-driven I/O

## 반드시 실습할 것

- [ ] `open/read/write/close`만으로 파일 복사 유틸 만들기
- [ ] `fork/exec/wait`로 외부 명령을 실행하는 mini shell 만들기
- [ ] pipe로 두 프로세스를 연결해 보기
- [ ] `mmap`으로 파일 내용을 읽는 뷰어 만들기
- [ ] echo server 만들기
- [ ] tiny HTTP server 만들기
- [ ] `epoll` 또는 최소한 `poll` 기반의 다중 연결 처리 실험하기

## 권장 미니 프로젝트

### 프로젝트 A: mini shell
기능 범위 예시:
- 명령 실행
- `cd`
- 파이프 1단계 지원
- 종료 코드 출력

### 프로젝트 B: tiny HTTP server
기능 범위 예시:
- GET 요청 처리
- 정적 문자열 응답
- 로그 출력
- 단일 스레드 → 이후 멀티스레드/이벤트 루프로 확장

### 프로젝트 C: mmap 파일 뷰어
기능 범위 예시:
- 파일 일부를 페이지 단위로 읽기
- hex/text 모드 토글
- 큰 파일을 일반 `read`와 비교

## 완료 조건

- `fork` 후에 부모/자식이 어떻게 갈라지는지 설명할 수 있다.
- `exec`가 “새 프로세스를 만드는 것”이 아니라는 점을 이해한다.
- `mmap`을 언제 쓰면 좋은지, 언제 주의해야 하는지 설명할 수 있다.
- FD가 파일뿐 아니라 pipe/socket/event source에도 쓰인다는 감각이 생긴다.
- tiny HTTP server를 직접 만든 뒤, FastAPI와 다른 추상화 수준을 비교할 수 있다.

## 추천 접근

운영체제를 배울 때는 **OSTEP → Linux man page → xv6** 순서가 좋다.

1. OSTEP으로 개념을 잡는다.
2. Linux man page로 실제 인터페이스를 확인한다.
3. xv6로 구현의 축소판을 읽는다.

이렇게 가면 “개념”과 “실전”이 서로 공중분해되지 않는다.

---

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
- “이 코드는 왜 느린가?”를 감이 아니라 데이터(`perf`, 벤치마크)로 말하기 시작한다.
- race condition을 재현하고 TSan으로 검출할 수 있다.
- lock-free를 아직 깊게 못 해도, **왜 어려운지**는 설명할 수 있다.

## 여기서의 금지 사항

- lock-free를 멋있어 보인다고 먼저 파기
- benchmark를 한 번만 돌리고 결론 내리기
- 성능 문제를 컴파일러 탓만 하기
- cache/TLB/branch 영향 없이 알고리즘 복잡도만 보기

---

# 토픽 5. Modern C++ + 캡스톤
_권장 기간: 6주_

## 목표
C로 실행 모델과 메모리 감각을 익혔다면, 이제 C++로  
**“비용을 이해한 상태에서 안전한 추상화를 쌓는 법”**을 배운다.

## 핵심 개념

### 1) C++의 핵심 철학
- C with classes로 멈추지 않기
- RAII
- value semantics
- ownership
- resource lifetime
- zero-cost abstraction의 감각

### 2) 필수 문법/개념
- constructor / destructor
- copy / move
- reference
- `std::unique_ptr`
- `std::shared_ptr`는 신중하게
- `std::vector`, `std::string`, `std::span`
- `std::optional`, `std::variant`
- template 기초
- generic programming
- exceptions와 exception safety

### 3) Modern C++ 스타일
- raw `new/delete`를 직접 다루는 코드 줄이기
- 자원 소유권을 타입으로 표현하기
- 범위를 작은 단위로 유지하기
- 표준 라이브러리를 적극 활용하기
- `clang-tidy`와 가이드라인을 습관으로 만들기

### 4) C와 C++의 연결
- C API를 C++ wrapper로 감싸기
- RAII로 파일/소켓/락/버퍼 관리
- C 라이브러리를 C++ 코드에서 안전하게 호출
- ABI 경계에서 `extern "C"` 이해하기

## 반드시 실습할 것

- [ ] C로 만든 자료구조 하나를 C++20 스타일로 다시 구현하기
- [ ] 파일 핸들 RAII wrapper 만들기
- [ ] mutex lock guard를 직접 아주 작게 흉내 내 보기
- [ ] `clang-tidy`를 붙여 코드 점검하기
- [ ] `std::vector` / `std::span` / `std::string_view` 활용하기
- [ ] move semantics가 실제로 일어나는 예제를 만들고 관찰하기

## 캡스톤 트랙 (하나 이상 선택)

### 트랙 A: Python/FastAPI 성능 개선형
가장 추천한다. 네 기존 배경과 직접 연결되기 때문이다.

예시:
- JSON/바이너리 parser
- tokenizer / text normalization
- checksum / codec
- 간단한 압축/인코딩
- 이미지/바이너리 처리의 hot path

산출물:
- C 또는 C++ 라이브러리
- Python에서 호출 가능한 바인딩
- 성능 전/후 비교 보고서
- FastAPI 데모 서버 연결

### 트랙 B: 시스템 서버형
예시:
- event-driven TCP server
- tiny HTTP server 고도화
- logging pipeline
- 파일/네트워크 I/O 중심 서비스

산출물:
- 성능 측정 결과
- 동시성 모델 설명
- 병목 분석 보고서

### 트랙 C: 컴파일러형
예시:
- lexer
- parser
- AST
- 간단한 semantic check
- LLVM IR 생성
- toy language JIT 또는 인터프리터

산출물:
- 문법 정의
- 샘플 프로그램
- 코드 생성 흐름 설명서

### 트랙 D: 운영체제형
예시:
- xv6 lab
- page table / syscall / mmap / scheduler 관련 실험
- 실험 기록과 코드 주석 정리

산출물:
- xv6 수정 코드
- 개념 설명 문서
- “커널에서 배운 점” 보고서

## 완료 조건

- RAII가 왜 C++의 핵심인지 설명할 수 있다.
- 소유권을 기준으로 값/참조/포인터 선택이 가능하다.
- raw pointer와 owning pointer를 구분해 사고할 수 있다.
- C와 C++을 섞을 때 ABI/예외/수명 문제를 의식할 수 있다.
- 최종 캡스톤 하나를 README + 벤치마크 + 회고 문서까지 포함해 완성한다.

---

## 추천 학습 루틴 (매주 반복)

### 주간 루틴
- **1일차**: 개념 읽기 + 예제 타이핑
- **2일차**: 실습 1
- **3일차**: 실습 2
- **4일차**: 디버깅/도구 사용
- **5일차**: 미니 프로젝트 진척
- **6일차**: 어셈블리/성능/로그 분석
- **7일차**: 회고 및 정리

### 매주 남길 것
- [ ] 이번 주 배운 핵심 개념 3개
- [ ] 직접 만든 코드 1개
- [ ] 잡은 버그 1개
- [ ] 측정한 성능/로그 1개
- [ ] “왜 이런 결과가 나왔는지”에 대한 짧은 기록

---

## 포트폴리오 전략

이 로드맵에서 진짜 강한 포인트는 “C/C++를 공부했다”가 아니라 아래 세 가지를 보여주는 것이다.

### 1) 디버깅 능력
- 크래시 재현
- sanitizer 출력 해석
- GDB/Valgrind 사용
- 원인 분석 문서화

### 2) 성능 분석 능력
- 벤치마크 설계
- `perf` 기반 병목 찾기
- 캐시/락/메모리 접근 패턴 설명

### 3) 시스템 추상화 이해
- 시스템 콜, FD, 프로세스, 메모리 매핑, 스레드
- C API와 C++ RAII wrapper
- Python/FastAPI와 네이티브 코드 연결

> 특히 네 배경에서는 **“Python 서비스의 특정 병목을 C/C++로 내려서 실제 성능을 올린 사례”**가 아주 강한 포트폴리오가 된다.

---

## 하지 말아야 할 것

- C와 C++을 동시에 깊게 시작하기
- 커널 소스부터 무작정 들이받기
- sanitizer 없이 메모리 프로젝트 진행하기
- lock-free부터 시작하기
- 블로그 조각 정보만 믿고 표준/공식 문서 확인을 생략하기
- “컴파일되면 맞다”라고 생각하기

---

## 최종 체크리스트

아래 항목을 대부분 만족하면, 너는 이미 “문법만 아는 개발자” 영역을 넘기 시작한 것이다.

- [ ] 포인터/배열/함수 포인터 선언을 읽고 쓸 수 있다.
- [ ] `struct` layout, padding, alignment를 설명할 수 있다.
- [ ] ASan/UBSan/TSan/Valgrind를 최소 한 번씩 써 봤다.
- [ ] GDB로 크래시를 추적해 본 적이 있다.
- [ ] 오브젝트 파일/심볼/라이브러리/링크 개념을 안다.
- [ ] `fork/exec/wait`, `mmap`, socket을 직접 사용해 봤다.
- [ ] tiny shell 또는 tiny server를 직접 만들어 봤다.
- [ ] `perf`로 병목을 찾아 본 적이 있다.
- [ ] 멀티스레드 큐/스레드 풀을 직접 구현해 봤다.
- [ ] C++20에서 RAII와 소유권을 기준으로 코드를 짤 수 있다.
- [ ] Python/FastAPI와 연결되는 C/C++ 산출물을 하나 이상 만들었다.

---

## 공식 자료 및 추천 레퍼런스

### 표준/컴파일러 상태
- GCC C 상태: <https://gcc.gnu.org/projects/c-status.html>
- GCC C++ 상태: <https://gcc.gnu.org/projects/cxx-status.html>
- Clang C 상태: <https://clang.llvm.org/c_status.html>
- Clang C++ 상태: <https://clang.llvm.org/cxx_status.html>

### 빌드/디버깅/검사
- CMake Tutorial: <https://cmake.org/cmake/help/latest/guide/tutorial/index.html>
- GDB Manual: <https://sourceware.org/gdb/current/onlinedocs/gdb.html>
- AddressSanitizer: <https://clang.llvm.org/docs/AddressSanitizer.html>
- ThreadSanitizer: <https://clang.llvm.org/docs/ThreadSanitizer.html>
- Valgrind Quick Start: <https://valgrind.org/docs/manual/quick-start.html>
- perf(1): <https://man7.org/linux/man-pages/man1/perf.1.html>

### 운영체제/시스템
- OSTEP: <https://pages.cs.wisc.edu/~remzi/OSTEP/>
- xv6: <https://pdos.csail.mit.edu/6.1810/2024/xv6.html>
- Linux man-pages index: <https://man7.org/linux/man-pages/index.html>

### 아키텍처
- Intel SDM: <https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html>
- RISC-V ISA Manual: <https://docs.riscv.org/reference/isa/unpriv/unpriv-index.html>

### C / C++
- Modern C: <https://gustedt.gitlabpages.inria.fr/modern-c/>
- A Tour of C++ (3rd edition): <https://www.stroustrup.com/tour3.html>
- C++ Core Guidelines: <https://isocpp.github.io/CppCoreGuidelines/>
- clang-tidy: <https://clang.llvm.org/extra/clang-tidy/>

### 컴파일러/언어 구현
- LLVM Kaleidoscope Tutorial: <https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/LangImpl01.html>

### 컴퓨터 시스템 전체 관점
- CS:APP (공식 페이지): <https://csapp.cs.cmu.edu/>

---

## 마지막 조언

C/C++ 학습은 “문법의 양”보다 **정신 모델의 전환**이 중요하다.

웹 개발에서는 보통  
“이 함수가 무엇을 해 주는가?”를 먼저 본다.

시스템 프로그래밍에서는  
“이 값은 어디에 살고, 누가 소유하고, 언제 파괴되며, CPU와 OS는 이것을 어떤 비용으로 실행하는가?”를 먼저 본다.

이 질문이 습관이 되면,  
너는 단순히 언어 하나를 배운 것이 아니라 **컴퓨터를 보는 시야 자체를 업그레이드한 것**이다.

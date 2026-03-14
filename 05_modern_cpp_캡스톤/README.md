# 토픽 5. Modern C++ + 캡스톤
_권장 기간: 6주_

## 목표
C로 실행 모델과 메모리 감각을 익혔다면, 이제 C++로  
**"비용을 이해한 상태에서 안전한 추상화를 쌓는 법"**을 배운다.

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
- "커널에서 배운 점" 보고서

## 완료 조건

- RAII가 왜 C++의 핵심인지 설명할 수 있다.
- 소유권을 기준으로 값/참조/포인터 선택이 가능하다.
- raw pointer와 owning pointer를 구분해 사고할 수 있다.
- C와 C++을 섞을 때 ABI/예외/수명 문제를 의식할 수 있다.
- 최종 캡스톤 하나를 README + 벤치마크 + 회고 문서까지 포함해 완성한다.

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
- [ ] "왜 이런 결과가 나왔는지"에 대한 짧은 기록

## 포트폴리오 전략

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

> 특히 네 배경에서는 **"Python 서비스의 특정 병목을 C/C++로 내려서 실제 성능을 올린 사례"**가 아주 강한 포트폴리오가 된다.

## 하지 말아야 할 것

- C와 C++을 동시에 깊게 시작하기
- 커널 소스부터 무작정 들이받기
- sanitizer 없이 메모리 프로젝트 진행하기
- lock-free부터 시작하기
- 블로그 조각 정보만 믿고 표준/공식 문서 확인을 생략하기
- "컴파일되면 맞다"라고 생각하기

## 최종 체크리스트

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

## 마지막 조언

C/C++ 학습은 "문법의 양"보다 **정신 모델의 전환**이 중요하다.

웹 개발에서는 보통  
"이 함수가 무엇을 해 주는가?"를 먼저 본다.

시스템 프로그래밍에서는  
"이 값은 어디에 살고, 누가 소유하고, 언제 파괴되며, CPU와 OS는 이것을 어떤 비용으로 실행하는가?"를 먼저 본다.

이 질문이 습관이 되면,  
너는 단순히 언어 하나를 배운 것이 아니라 **컴퓨터를 보는 시야 자체를 업그레이드한 것**이다.

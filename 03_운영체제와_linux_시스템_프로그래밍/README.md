# 토픽 3. 운영체제와 Linux 시스템 프로그래밍
_권장 기간: 6주_

## 목표
이 토픽의 목적은 운영체제를 "이론 과목"으로 끝내지 않고,  
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
- 단일 스레드 -> 이후 멀티스레드/이벤트 루프로 확장

### 프로젝트 C: mmap 파일 뷰어
기능 범위 예시:
- 파일 일부를 페이지 단위로 읽기
- hex/text 모드 토글
- 큰 파일을 일반 `read`와 비교

## 완료 조건

- `fork` 후에 부모/자식이 어떻게 갈라지는지 설명할 수 있다.
- `exec`가 "새 프로세스를 만드는 것"이 아니라는 점을 이해한다.
- `mmap`을 언제 쓰면 좋은지, 언제 주의해야 하는지 설명할 수 있다.
- FD가 파일뿐 아니라 pipe/socket/event source에도 쓰인다는 감각이 생긴다.
- tiny HTTP server를 직접 만든 뒤, FastAPI와 다른 추상화 수준을 비교할 수 있다.

## 추천 접근

운영체제를 배울 때는 **OSTEP -> Linux man page -> xv6** 순서가 좋다.

1. OSTEP으로 개념을 잡는다.
2. Linux man page로 실제 인터페이스를 확인한다.
3. xv6로 구현의 축소판을 읽는다.

이렇게 가면 "개념"과 "실전"이 서로 공중분해되지 않는다.

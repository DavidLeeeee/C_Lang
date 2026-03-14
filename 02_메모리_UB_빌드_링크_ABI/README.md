# 토픽 2. 메모리, UB, 빌드/링크, ABI
_권장 기간: 6주_

## 목표
C를 배우는 진짜 이유 중 하나는 **"왜 어떤 버그는 돌아가는 것처럼 보이는데 틀렸는지"**를 이해하는 데 있다.  
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
> "웹 개발만 하는 사람"에서 "핫패스를 네이티브로 내릴 줄 아는 사람"으로 한 단계 올라가는 좋은 교두보다.

## 완료 조건

- 메모리 오류를 재현하고, 도구로 원인을 좁히고, 수정 내용을 설명할 수 있다.
- shared library와 static library의 차이를 설명할 수 있다.
- Python에서 C 함수 하나를 직접 호출해 보고, 인자/반환값/버퍼 수명 문제를 이해한다.
- 오브젝트 파일과 실행 파일이 "그냥 빌드 결과물"이 아니라는 감각이 생긴다.

## 이 단계에서 특히 조심할 것

- "돌아가니까 맞다"는 생각
- `memcpy`/캐스팅으로 타입을 대충 우회하기
- `struct`를 네트워크/파일 포맷으로 그대로 저장하기
- 경고를 끄고 넘어가기

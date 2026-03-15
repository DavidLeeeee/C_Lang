# 01 시작 가이드

토픽 1은 문법 암기가 아니라 **메모리 관점에서 C를 보기 시작하는 단계**다.  
처음에는 아래 3개만 순서대로 해 보면 된다.

## 추천 순서

1. `exercises/01_array_pointer.c`
2. `exercises/02_struct_layout.c`
3. `exercises/03_storage_duration.c`

## 실행 방법

WSL 또는 Linux에서 아래처럼 실행한다.

```bash
cd /mnt/d/DEV/developer/Study/Language/C/01_c_실행_모델과_특별한_문법/exercises
gcc -std=c11 -Wall -Wextra -pedantic 01_array_pointer.c -o 01_array_pointer
./01_array_pointer
```

다른 파일도 같은 방식으로 실행하면 된다.

## 첫 주 목표

- 배열과 포인터의 차이를 말로 설명하기
- `struct` padding이 왜 생기는지 확인하기
- 지역 변수와 `static` 지역 변수의 lifetime 차이 이해하기

## 실습할 때 볼 포인트

- 출력값만 보지 말고 "왜 그렇게 나오는가"를 설명해 본다.
- 예상한 결과를 먼저 적고 실행한다.
- 실험 후에는 `Todo.md`에 짧게 기록한다.

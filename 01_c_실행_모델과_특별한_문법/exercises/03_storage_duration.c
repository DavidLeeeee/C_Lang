#include <stdio.h>

int global_counter = 100;
static int file_static_counter = 1000;

static void tick(void) {
    static int function_static_counter = 0;
    int local_counter = 0;
    int auto_counter = 0;
    static int static_counter = 0;

    function_static_counter++;
    local_counter++;
    auto_counter++;
    static_counter++;
    global_counter++;
    file_static_counter++;

    printf("global_counter          = %d\n", global_counter);
    printf("file_static_counter     = %d\n", file_static_counter);
    printf("function_static_counter = %d\n", function_static_counter);
    printf("local_counter           = %d\n", local_counter);
    printf("auto_counter            = %d\n", auto_counter);
    printf("static_counter          = %d\n", static_counter);
    puts("---");
}

int main(void) {
    puts("first call");
    tick();

    puts("second call");
    tick();

    puts("third call");
    tick();

    puts("\nQuestions:");
    puts("1. 왜 local_counter는 항상 1인가?");
    puts("2. 왜 function_static_counter는 호출 사이에 값이 유지되는가?");
    puts("3. file static과 global의 차이는 lifetime이 아니라 무엇인가?");

    return 0;
}

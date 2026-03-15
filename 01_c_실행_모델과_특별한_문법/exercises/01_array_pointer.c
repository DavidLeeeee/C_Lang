#include <stdio.h>

static void inspect_array_parameter(int arr_param[], size_t count) {
    printf("[inspect_array_parameter]\n");
    printf("sizeof(arr_param) = %zu\n", sizeof(arr_param));
    printf("count             = %zu\n", count);
    printf("arr_param         = %p\n", (void *)arr_param);
    printf("arr_param + 1     = %p\n", (void *)(arr_param + 1));
}

int main(void) {
    int arr[5] = {10, 20, 30, 40, 50};
    int *ptr = arr;

    printf("[main]\n");
    printf("sizeof(arr)       = %zu\n", sizeof(arr));
    printf("sizeof(ptr)       = %zu\n", sizeof(ptr));
    printf("&arr[0]           = %p\n", (void *)&arr[0]);
    printf("arr               = %p\n", (void *)arr);
    printf("ptr               = %p\n", (void *)ptr);
    printf("arr + 1           = %p\n", (void *)(arr + 1));
    printf("ptr + 1           = %p\n", (void *)(ptr + 1));
    printf("*(arr + 2)        = %d\n", *(arr + 2));
    printf("ptr[2]            = %d\n", ptr[2]);

    inspect_array_parameter(arr, sizeof(arr) / sizeof(arr[0]));
    // 함수 내부로 들어가는 순간 배열은 포인터로 바뀐다.
    // 그래서 sizeof(arr)와 sizeof(arr_param)가 다르다.
    // 그래서 함수 내부에서는 배열의 길이를 구할 수 없다.
    // 그래서 함수 인자로 넘기는 순간 배열은 포인터로 바뀌는데, 이 포인터는 배열의 첫 원소의 주소를 가리킨다.

    puts("\nQuestions:");
    puts("1. 왜 sizeof(arr)와 sizeof(arr_param)가 다른가?");
    puts("2. arr와 ptr의 출력 주소는 비슷한데 왜 같은 개념이 아닌가?");
    puts("3. 함수 인자로 넘기는 순간 배열은 무엇으로 바뀌는가?");

    return 0;
}

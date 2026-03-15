#include <stddef.h>
#include <stdio.h>

struct A {
    char c;
    int i;
    char d;
};

struct B {
    int i;
    char c;
    char d;
};

struct C {
    char a;
    double b;
    short c;
};

static void print_layouts(void) {
    printf("struct A: sizeof=%zu\n", sizeof(struct A));
    printf("  offsetof(c) = %zu\n", offsetof(struct A, c));
    printf("  offsetof(i) = %zu\n", offsetof(struct A, i));
    printf("  offsetof(d) = %zu\n", offsetof(struct A, d));

    printf("\nstruct B: sizeof=%zu\n", sizeof(struct B));
    printf("  offsetof(i) = %zu\n", offsetof(struct B, i));
    printf("  offsetof(c) = %zu\n", offsetof(struct B, c));
    printf("  offsetof(d) = %zu\n", offsetof(struct B, d));

    printf("\nstruct C: sizeof=%zu\n", sizeof(struct C));
    printf("  offsetof(a) = %zu\n", offsetof(struct C, a));
    printf("  offsetof(b) = %zu\n", offsetof(struct C, b));
    printf("  offsetof(c) = %zu\n", offsetof(struct C, c));
}

int main(void) {
    print_layouts();

    puts("\nQuestions:");
    puts("1. 왜 멤버 순서만 바꿨는데 sizeof가 달라질 수 있는가?");
    puts("2. padding은 어디에 들어가는가?");
    puts("3. alignment 요구사항이 struct layout에 어떤 영향을 주는가?");

    return 0;
}

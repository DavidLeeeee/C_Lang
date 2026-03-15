#include <stdio.h>

static void unsafe_copy_demo(void) {
    char small_buf[5];
    const char *src = "hello";

    puts("[unsafe_copy_demo]");
    puts("small_buf has room for 5 bytes.");
    puts("src is \"hello\" which needs 6 bytes including \\0.");
    puts("If you uncomment strcpy below, it writes past the end of small_buf.");

    /*
    strcpy(small_buf, src);
    printf("small_buf = %s\n", small_buf);
    */

    puts("Result: buffer overflow risk because strcpy does not know destination size.");
    puts("Reason: function sees a pointer, not the true array capacity.");
    puts("");
}

static void safe_copy_demo(void) {
    char small_buf[5];
    const char *src = "hello";

    puts("[safe_copy_demo]");
    snprintf(small_buf, sizeof(small_buf), "%s", src);
    printf("small_buf = %s\n", small_buf);
    puts("Result: truncated but bounded write.");
    puts("");
}

static void inspect_parameter(char buf[]) {
    puts("[inspect_parameter]");
    printf("sizeof(buf) inside function = %zu\n", sizeof(buf));
    puts("This is pointer size, not the caller's real array size.");
    puts("");
}

int main(void) {
    char local_buf[5] = {0};

    puts("String function danger demo");
    puts("===========================");
    printf("sizeof(local_buf) in main = %zu\n\n", sizeof(local_buf));

    inspect_parameter(local_buf);
    unsafe_copy_demo();
    safe_copy_demo();

    puts("Questions:");
    puts("1. Why can't strcpy check the real destination capacity?");
    puts("2. Why does sizeof(buf) change when the array is passed to a function?");
    puts("3. Why is a terminating null byte important for C strings?");
    puts("4. Why is snprintf safer than strcpy here?");

    return 0;
}

#include <stdio.h>
#include <string.h>

static void overflow_demo(void) {
    char small_buf[5];
    const char *src = "hello";

    puts("[overflow_demo]");
    puts("small_buf capacity: 5 bytes");
    puts("src length with null terminator: 6 bytes");
    puts("About to call strcpy(small_buf, src)...");

    strcpy(small_buf, src);

    printf("small_buf = %s\n", small_buf);
}

int main(void) {
    puts("This program intentionally triggers a buffer overflow.");
    puts("Run it with AddressSanitizer enabled.");
    puts("");

    overflow_demo();

    return 0;
}

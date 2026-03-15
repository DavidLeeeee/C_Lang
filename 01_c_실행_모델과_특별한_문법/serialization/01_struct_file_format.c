#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

struct UserRecord {
    char grade;
    int age;
};

static void print_bytes(const unsigned char *data, size_t len, const char *label) {
    printf("%s (%zu바이트):\n", label, len);
    for (size_t i = 0; i < len; ++i) {
        printf("  [%zu] 0x%02X\n", i, data[i]);
    }
    puts("");
}

static void write_file(const char *path, const unsigned char *data, size_t len) {
    FILE *fp = fopen(path, "wb");
    if (fp == NULL) {
        perror("파일 열기 실패");
        return;
    }

    fwrite(data, 1, len, fp);
    fclose(fp);
}

int main(void) {
    struct UserRecord user = {'A', 20};
    unsigned char raw_bytes[sizeof(user)] = {0};
    unsigned char safe_bytes[5] = {0};

    memcpy(raw_bytes, &user, sizeof(user));

    safe_bytes[0] = (unsigned char)user.grade;
    safe_bytes[1] = (unsigned char)((user.age >> 24) & 0xFF);
    safe_bytes[2] = (unsigned char)((user.age >> 16) & 0xFF);
    safe_bytes[3] = (unsigned char)((user.age >> 8) & 0xFF);
    safe_bytes[4] = (unsigned char)(user.age & 0xFF);

    puts("구조체를 그대로 저장하는 방식 vs 필드 단위 직렬화 예제");
    puts("====================================================");
    printf("sizeof(struct UserRecord) = %zu\n", sizeof(struct UserRecord));
    printf("offsetof(grade) = %zu\n", offsetof(struct UserRecord, grade));
    printf("offsetof(age)   = %zu\n", offsetof(struct UserRecord, age));
    puts("");

    puts("구조체 메모리 배치를 그대로 복사한 바이트를 확인합니다.");
    print_bytes(raw_bytes, sizeof(raw_bytes), "raw struct bytes");

    puts("필드 단위로 직접 직렬화한 바이트를 확인합니다.");
    print_bytes(safe_bytes, sizeof(safe_bytes), "serialized bytes");

    puts("차이점:");
    puts("- raw struct bytes에는 padding이 끼어들 수 있습니다.");
    puts("- serialized bytes는 저장 형식을 직접 통제합니다.");
    puts("- 파일 포맷/네트워크 포맷은 보통 직접 직렬화하는 쪽이 안전합니다.");
    puts("");

    write_file("user_raw.bin", raw_bytes, sizeof(raw_bytes));
    write_file("user_safe.bin", safe_bytes, sizeof(safe_bytes));

    puts("생성 파일:");
    puts("- user_raw.bin   : 구조체 메모리 모습을 그대로 저장한 파일");
    puts("- user_safe.bin  : grade 1바이트 + age 4바이트(big-endian)로 저장한 파일");
    puts("");

    puts("질문:");
    puts("1. 왜 raw 파일 크기와 safe 파일 크기가 다른가?");
    puts("2. 왜 raw 방식은 다른 플랫폼에서 위험할 수 있는가?");
    puts("3. 왜 serialized bytes는 파일 포맷으로 더 적합한가?");

    return 0;
}

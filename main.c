#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// char* strrev(char* s) {
//     if (!s || !*s)
//         return s;
//     char* b = s;
//     char* e = s + strlen(s) - 1;
//     while (b < e) {
//         char t = *b;
//         *b++ = *e;
//         *e-- = t;
//     }
//     return s;
// }

static char n_str[1024];
bool is_all_odd_digits(uint64_t* n);
uint64_t find_sum(uint64_t n);

int main(int argc, char* argv[]) {
    clock_t t = clock();
    uint64_t i;
    uint64_t start = 1;
    uint64_t sum = 0;
    float timecount;
    char* p_end;

    // resume
    if (argc == 2) {
        start = strtoull(argv[1], &p_end, 10);

        if (*p_end) {
            printf("failed\n");
            return 1;
        }

        printf("starting from %llu...\n", start);

        uint64_t sum_start = find_sum(start);
        if (!sum_start) {
            printf("oops\n");
            return 1;
        }

        printf("for start at %llu, found sum_start of %llu\n\n", start, sum_start);
        // sum = sum_start - start - start - 1;
        // start -= 1;
        sum = sum_start - (start) - (start - 1);
        i = start;
    }

    for (i = start; i < ULONG_MAX; i += 2) {
        sum += i + i - 1;
        if (sum % 2 == 0 || i % 2 == 0)
            continue;
        if (!is_all_odd_digits(&i))
            continue;
        if (is_all_odd_digits(&sum)) {
            clock_t diff_t = clock() - t;
            timecount = ((float)diff_t) / CLOCKS_PER_SEC;
            printf("%fs valid: %llu\n", timecount, i);
        }
    }

    return 0;
}

bool is_all_odd_digits(uint64_t* n) {
    sprintf(n_str, "%llu", *n);

    if (strchr(n_str, '2') || strchr(n_str, '4') || strchr(n_str, '6') || strchr(n_str, '8') || strchr(n_str, '0')) {
        return false;
    }

    int len = strlen(n_str);
    for (int j = len - 1; j >= 0; j--) {
        char last_digit_as_char = n_str[j];
        int last_digit = atoi(&last_digit_as_char);
        bool is_even = last_digit % 2 == 0;
        if (is_even)
            return false;
    }
    return true;
}

uint64_t find_sum(uint64_t n) {
    uint64_t sum = 0;
    uint32_t i;
    for (i = 1; i <= n; i++) {
        sum += i;
        if (i == n) {
            return sum;
        }
    }
    return 0;
}
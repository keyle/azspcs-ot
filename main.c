#include "u256.h"
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static char n_str[1024];
bool is_all_odd_digits(__uint128_t* n);
__uint128_t find_sum(__uint128_t n);

int main(int argc, char* argv[]) {
    clock_t t = clock();
    __uint128_t i;
    __uint128_t start = 1;
    __uint128_t sum = 0;
    float timecount;
    char* p_end;

    // ability to resume at n
    if (argc == 2) {
        start = strtoull(argv[1], &p_end, 10);

        if (*p_end) {
            printf("failed\n");
            return 1;
        }

        printf("starting from...");
        pu128(start);
        printf("\n");

        __uint128_t sum_start = find_sum(start);
        if (!sum_start) {
            printf("oops\n");
            return 1;
        }

        printf("for start at ");
        pu128(start);
        printf(" found sum_start of ");
        pu128(sum_start);
        printf("\n\n");
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
            printf("%fs valid: ", timecount);
            pu128(i);
            printf("\t sum ");
            pu128(sum);
            printf(" \n");
        }
    }

    return 0;
}

bool is_all_odd_digits(__uint128_t* n) {
    // sprintf(n_str, "%llu", *n);
    puf128(*n, n_str);

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

__uint128_t find_sum(__uint128_t n) {
    __uint128_t sum = 0;
    __uint128_t i;
    for (i = 1; i <= n; i++) {
        sum += i;
        if (i == n) {
            return sum;
        }
    }
    return 0;
}
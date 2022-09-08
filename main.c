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
bool is_all_odd_digits(uint64_t n);

int main() {
    clock_t t = clock();
    uint64_t i = 1;
    uint64_t sum = 0;
    float timecount;

    for (i = 1; i < ULONG_MAX; i++) {
        sum += i;
        if (sum % 2 == 0 || i % 2 == 0)
            continue;
        if (!is_all_odd_digits(i))
            continue;
        if (is_all_odd_digits(sum)) {
            clock_t diff_t = clock() - t;
            timecount = ((float)diff_t) / CLOCKS_PER_SEC;
            printf("%fs valid: %llu\n", timecount, i);
        }
    }

    return 0;
}

bool is_all_odd_digits(uint64_t n) {
    sprintf(n_str, "%llu", n);
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

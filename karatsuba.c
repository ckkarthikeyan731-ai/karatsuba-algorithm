#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Reverse string in-place
void reverse_str(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

// Custom max
int max_int(int a, int b) {
    return (a > b) ? a : b;
}

// Remove leading zeros
char* remove_leading_zeros(char* str) {
    int i = 0;
    while (str[i] == '0' && str[i + 1] != '\0') i++;
    memmove(str, str + i, strlen(str) - i + 1);
    return str;
}

// Add two string numbers
char* add_strings(const char* a, const char* b) {
    int len1 = strlen(a), len2 = strlen(b);
    char* result = malloc(len1 + len2 + 1);
    int i = len1 - 1, j = len2 - 1, k = 0, carry = 0;

    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';
        result[k++] = (sum % 10) + '0';
        carry = sum / 10;
    }
    result[k] = '\0';
    reverse_str(result);
    return remove_leading_zeros(result);
}

// Subtract two string numbers (a >= b)
char* subtract_strings(const char* a, const char* b) {
    int len1 = strlen(a), len2 = strlen(b);
    char* result = malloc(len1 + 1);
    int i = len1 - 1, j = len2 - 1, k = 0, borrow = 0;

    while (i >= 0 || j >= 0 || borrow) {
        int diff = borrow;
        if (i >= 0) diff += a[i--] - '0';
        if (j >= 0) diff -= b[j--] - '0';

        if (diff < 0) {
            diff += 10;
            borrow = -1;
        } else {
            borrow = 0;
        }
        result[k++] = (diff % 10) + '0';
    }
    result[k] = '\0';
    reverse_str(result);
    return remove_leading_zeros(result);
}

// Pad string to given length with leading zeros
char* pad_string(const char* str, int len) {
    char* padded = malloc(len + 1);
    int str_len = strlen(str);
    memset(padded, '0', len - str_len);
    strcpy(padded + (len - str_len), str);
    return padded;
}

// Karatsuba Algorithm - ERROR FREE
char* karatsuba_multiply(const char* x, const char* y) {
    int n = strlen(x), m = strlen(y);

    // Base case: small numbers
    if (n < 10 || m < 10) {
        long long a = atoll(x), b = atoll(y);
        char* result = malloc(50);
        sprintf(result, "%lld", a * b);
        return result;
    }

    // Pad to same length
    int len = max_int(n, m);
    if (len % 2 == 1) len++;

    char* a = pad_string(x, len);
    char* b = pad_string(y, len);

    int half = len / 2;

    // Split into high and low parts
    char a0[half + 1], a1[half + 1], b0[half + 1], b1[half + 1];
    strncpy(a0, a, half); a0[half] = '\0';
    strncpy(a1, a + half, half); a1[half] = '\0';
    strncpy(b0, b, half); b0[half] = '\0';
    strncpy(b1, b + half, half); b1[half] = '\0';

    // Three multiplications
    char* z2 = karatsuba_multiply(a1, b1);  // A1 * B1
    char* z0 = karatsuba_multiply(a0, b0);  // A0 * B0

    char* sum1 = add_strings(a0, a1);
    char* sum2 = add_strings(b0, b1);
    char* z1 = karatsuba_multiply(sum1, sum2);  // (A0+A1) * (B0+B1)

    // Compute middle term: z1 - z2 - z0
    char* temp = add_strings(z2, z0);
    char* zmid = subtract_strings(z1, temp);

    // Shift and add: z2 * 10^(2*half) + zmid * 10^half + z0
    char* high_shifted = malloc(strlen(z2) + 2 * half + 1);
    strcpy(high_shifted, z2);
    memset(high_shifted + strlen(z2), '0', 2 * half);
    high_shifted[strlen(z2) + 2 * half] = '\0';

    char* mid_shifted = malloc(strlen(zmid) + half + 1);
    strcpy(mid_shifted, zmid);
    memset(mid_shifted + strlen(zmid), '0', half);
    mid_shifted[strlen(zmid) + half] = '\0';

    char* result = add_strings(high_shifted, mid_shifted);
    result = add_strings(result, z0);

    // Cleanup
    free(a); free(b); free(sum1); free(sum2);
    free(z0); free(z1); free(z2); free(temp); free(zmid);
    free(high_shifted); free(mid_shifted);

    return remove_leading_zeros(result);
}

int main() {
    const char* num1 = "1234";
    const char* num2 = "5678";

    printf("=== KARATSUBA MULTIPLICATION ===\n");
    printf("Multiplying: %s * %s\n", num1, num2);  // Changed × to *

    char* karatsuba_result = karatsuba_multiply(num1, num2);
    printf("Karatsuba result: %s\n", karatsuba_result);

    // Built-in verification
    long long expected = atoll(num1) * atoll(num2);
    printf("Built-in result: %lld\n", expected);

    free(karatsuba_result);
    return 0;
}

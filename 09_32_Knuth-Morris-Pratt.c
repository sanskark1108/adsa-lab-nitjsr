#include <stdio.h>
#include <string.h>

// Build longest prefix suffix (LPS) array
void computeLPS(char* pattern, int m, int lps[]) {
    int len = 0;
    lps[0] = 0;
    for (int i = 1; i < m;) {
        if (pattern[i] == pattern[len])
            lps[i++] = ++len;
        else if (len)
            len = lps[len - 1];
        else
            lps[i++] = 0;
    }
}

// KMP pattern matching
void KMP(char* text, char* pattern) {
    int n = strlen(text), m = strlen(pattern);
    int lps[m], i = 0, j = 0;

    computeLPS(pattern, m, lps);

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++; j++;
        }
        if (j == m) {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j) j = lps[j - 1];
            else i++;
        }
    }
}

int main() {
    char text[] = "ABABDABACDABABCABAB";
    char pattern[] = "ABABCABAB";
    KMP(text, pattern);
    return 0;
}

#include <stdio.h>
#include <string.h>
#define CHAR_SIZE 256

// Preprocess bad character heuristic
void badCharHeuristic(char *pattern, int size, int badChar[]) {
    for (int i = 0; i < CHAR_SIZE; i++)
        badChar[i] = -1;
    for (int i = 0; i < size; i++)
        badChar[(unsigned char)pattern[i]] = i;
}

// Boyer-Moore search
void BoyerMoore(char *text, char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    int badChar[CHAR_SIZE];

    badCharHeuristic(pattern, m, badChar);

    int s = 0; // shift of the pattern
    while (s <= n - m) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[s + j])
            j--;

        if (j < 0) {
            printf("Pattern found at index %d\n", s);
            s += (s + m < n) ? m - badChar[(unsigned char)text[s + m]] : 1;
        } else {
            s += (j - badChar[(unsigned char)text[s + j]] > 1) ? j - badChar[(unsigned char)text[s + j]] : 1;
        }
    }
}

int main() {
    char text[] = "HERE IS A SIMPLE EXAMPLE";
    char pattern[] = "EXAMPLE";
    BoyerMoore(text, pattern);
    return 0;
}

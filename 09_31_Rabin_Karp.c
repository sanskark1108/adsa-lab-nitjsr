#include <stdio.h>
#include <string.h>

#define d 256  // number of characters in input alphabet
#define q 101  // a prime number

void rabinKarp(char* text, char* pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    int p = 0, t = 0, h = 1;

    // The value of h would be "pow(d, m-1)%q"
    for (int i = 0; i < m - 1; i++)
        h = (h * d) % q;

    // Calculate initial hash values
    for (int i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // Slide the pattern over text
    for (int i = 0; i <= n - m; i++) {
        if (p == t) {
            int match = 1;
            for (int j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    match = 0;
                    break;
                }
            }
            if (match)
                printf("Pattern found at index %d\n", i);
        }

        // Calculate hash for next window
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;
            if (t < 0) t += q;
        }
    }
}

int main() {
    char text[] = "ABCCDDAEFG";
    char pattern[] = "CDD";
    rabinKarp(text, pattern);
    return 0;
}

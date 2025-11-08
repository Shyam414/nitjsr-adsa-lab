#include <stdio.h>
#include <string.h>

void computeLPS(char pattern[], int m, int lps[]) {
    int length = 0, i = 1;
    lps[0] = 0;
    while (i < m) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0)
                length = lps[length - 1];
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void KMP(char pattern[], char text[]) {
    int m = strlen(pattern);
    int n = strlen(text);
    int lps[m];
    computeLPS(pattern, m, lps);

    int i = 0, j = 0;
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++; j++;
        }
        if (j == m) {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
}

int main() {
    char text[100], pattern[100];
    printf("Enter text: ");
    scanf("%s", text);
    printf("Enter pattern: ");
    scanf("%s", pattern);

    KMP(pattern, text);

    return 0;
}

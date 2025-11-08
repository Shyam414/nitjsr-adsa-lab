#include <stdio.h>
#include <string.h>
#define NO_OF_CHARS 256

void badCharHeuristic(char pattern[], int m, int badchar[]) {
    for (int i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;
    for (int i = 0; i < m; i++)
        badchar[(int)pattern[i]] = i;
}

void BoyerMoore(char text[], char pattern[]) {
    int n = strlen(text);
    int m = strlen(pattern);
    int badchar[NO_OF_CHARS];
    badCharHeuristic(pattern, m, badchar);

    int s = 0;
    while (s <= (n - m)) {
        int j = m - 1;
        while (j >= 0 && pattern[j] == text[s + j])
            j--;
        if (j < 0) {
            printf("Pattern occurs at index %d\n", s);
            s += (s + m < n) ? m - badchar[text[s + m]] : 1;
        } else {
            s += (j - badchar[text[s + j]] > 1) ? j - badchar[text[s + j]] : 1;
        }
    }
}

int main() {
    char text[100], pattern[100];
    printf("Enter text: ");
    scanf("%s", text);
    printf("Enter pattern: ");
    scanf("%s", pattern);

    BoyerMoore(text, pattern);

    return 0;
}

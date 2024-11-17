// 10. Compare the performance of Rabin-Karp, Knuth-Morris-Pratt and naive string-matching algorithms.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Naive String Matching
int naive_search(char *text, char *pattern) {
    int m = strlen(pattern);
    int n = strlen(text);
    int count = 0;
    for (int i = 0; i <= n - m; i++) {
        int j = 0;
        while (j < m && text[i + j] == pattern[j]) {
            j++;
        }
        if (j == m) count++;
    }
    return count;
}

// Rabin-Karp Algorithm
int rabin_karp_search(char *text, char *pattern) {
    int m = strlen(pattern);
    int n = strlen(text);
    int d = 256; // Number of characters in the input alphabet
    int q = 101; // A prime number
    int h = 1;
    int p = 0; // Hash value for pattern
    int t = 0; // Hash value for text

    for (int i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }

    for (int i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    int count = 0;
    for (int i = 0; i <= n - m; i++) {
        if (p == t) {
            int j = 0;
            while (j < m && text[i + j] == pattern[j]) {
                j++;
            }
            if (j == m) count++;
        }

        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;
            if (t < 0) t += q;
        }
    }
    return count;
}

// Knuth-Morris-Pratt (KMP) Algorithm
void computeLPSArray(char *pattern, int m, int *lps) {
    int len = 0;
    int i = 1;
    lps[0] = 0;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int kmp_search(char *text, char *pattern) {
    int m = strlen(pattern);
    int n = strlen(text);
    int lps[m];
    computeLPSArray(pattern, m, lps);

    int i = 0;
    int j = 0;
    int count = 0;

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            count++;
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    return count;
}

int main() {
    // Case 1: "abcdefg", "abc"
    char text1[] = "abcdefg";
    char pattern1[] = "abc";
    
    // Case 2: "loremipsumdolorsitamet", "ipsum"
    char text2[] = "loremipsumdolorsitamet";
    char pattern2[] = "ipsum";
    
    // Case 3: Large text, "random"
    char text3[10000];
    for (int i = 0; i < 10000; i++) {
        text3[i] = 'a' + (i % 26);  // Fill with repeating letters a-z
    }
    text3[9999] = '\0';
    char pattern3[] = "random";
    
    // Case 4: Large text, "longtext"
    char text4[5000];
    for (int i = 0; i < 5000; i++) {
        text4[i] = 'a' + (i % 26);  // Fill with repeating letters a-z
    }
    text4[4999] = '\0';
    char pattern4[] = "longtext";
    
    // Case 5: "abababababababababababab", "abab"
    char text5[] = "abababababababababababab";
    char pattern5[] = "abab";

    clock_t start, end;
    int iterations = 10000;  // Running each test case 10,000 times to accumulate time

    // Run all test cases
    char *texts[] = {text1, text2, text3, text4, text5};
    char *patterns[] = {pattern1, pattern2, pattern3, pattern4, pattern5};
    
    for (int i = 0; i < 5; i++) {
        printf("Test Case %d:\n", i + 1);
        
        // Naive Search
        start = clock();
        for (int j = 0; j < iterations; j++) {
            naive_search(texts[i], patterns[i]);
        }
        end = clock();
        printf("Naive Execution Time: %.5f ms\n", ((double)(end - start)) / CLOCKS_PER_SEC * 1000);

        // Rabin-Karp Search
        start = clock();
        for (int j = 0; j < iterations; j++) {
            rabin_karp_search(texts[i], patterns[i]);
        }
        end = clock();
        printf("Rabin-Karp Execution Time: %.5f ms\n", ((double)(end - start)) / CLOCKS_PER_SEC * 1000);

        // KMP Search
        start = clock();
        for (int j = 0; j < iterations; j++) {
            kmp_search(texts[i], patterns[i]);
        }
        end = clock();
        printf("KMP Execution Time: %.5f ms\n\n", ((double)(end - start)) / CLOCKS_PER_SEC * 1000);
    }

    return 0;
}
/**
 * Implementation of the Knuth Morris Pratt algorithm for competitive programming.
 * Based on Steve Halim's implementation in Competitive Programming 3rd edition.
 *
 * The algorith is used to find all the occurrences of searched_string (length m)
 * in long_string (length n) in time O(m + n), as oposed to the O(m*n) of the
 * naive algorithm.
 */

#include <bits/stdc++.h>

using namespace std;

int MAX_N = 1000;

/**
 * Creates a Partial Match Table (reset table) for the given string value "s".
 * Input:   searched_string - the string to preprocess.
 *          m - the length of searched_string.
 * Output:  the corresponding reset table.
 *
 * Details:
 * The reset table is based on preprocessing the searched_string to find sub-
 * strings which are also prefixes of the searched_string. If comparisson fails
 * at the end of such substring, we can resume the search, skipping the matching
 * prefix.
 */
vector<int> pmt (char* searched_string, int m) {
    vector<int> pmt;        // the reset table.
    int i = 0, j = -1;      // i -> "substring" index, j -> "prefix" index.
    pmt.push_back(-1);      // init val of -1 -> makes i advance and j stay.
                            // the same when necessary (on i++; j++; instructions).
    while (i < m) {
        while (j >= 0 && searched_string[i] != searched_string[j]) {
            j = pmt[j];     // reset j. Note that if j=0 => pmt[j] = -1. This
                            // will break loop, and next instruction will make j=0.
        }
        // if j = -1 or characters match
        i++; j++;           // advance both pointers.
        pmt.push_back(j);   // write corresponding val to reset table.
    }
    return(pmt);
}

/**
 * Searches for ocurrences of searched_string in long_string.
 * Input:   long_string - the string in which to search.
 *          searched_string - the searched string.
 *          pmt - the reset table for searched_string.
 *          n - the length of long_string.
 *          m - the length of searched_string.
 *
 * Details:
 * KMP is similar to the naive approach, differing in the use of a reset table.
 * It will start by comparing both strings character by character. If two chars
 * don't match, the reset table will give us the index of the searched_string
 * in which we can resume the comparisson without re-comparing characters which
 * we can already know that match, thus the performance improvement.
 */
void kmp(char* long_string, char* searched_string, vector<int> pmt, int n, int m) {
    int i = 0, j = 0;       // i -> long_string index, j -> searched_string index.

    while (i < n) {
        while (j >= 0 && long_string[i] != searched_string[j]) {
            j = pmt[j];     // reset j.
        }
        // if j = -1 or characters match.
        i++; j++;           // advance both pointers.
        if (j == m - 1) {   // match!
            printf("Match at index %d\n", i - j); // modify to suit problem.
            j = pmt[j];     // reset j for next possible match.
        }
    }
}

// Usage example
int main() {
    int n, m;
    scanf("%d%d", &n, &m);      // for example n=14, m=8

    char a[MAX_N], b[MAX_N];
    scanf("%s%s", a, b);        // for example a="hoholaholshola", b="holahols"

    kmp(a, b, pmt(b,m), n, m);
}

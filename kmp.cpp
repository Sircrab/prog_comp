#include <bits/stdc++.h>

using namespace std;

int MAX_N = 1000;

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

void kmp(char* long_string, char* searched_string, vector<int> pmt, int n, int m) {
    int i = 0, j = 0;       // i -> long_string index, j -> searched_string index.

    while (i < n) {
        while (j >= 0 && long_string[i] != searched_string[j]) {
            j = pmt[j];     // reset j.
        }
        // if j = -1 or characters match.
        i++; j++;           // advance both pointers.
        if (j == m) {   // match!
            printf("Match at index %d\n", i - j); // modify to suit problem.
            j = pmt[j];     // reset j for next possible match.
        }
    }
}

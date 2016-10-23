#include <bits/stdc++.h>

using namespace std;

vector<int> pmt(const string& pattern) {
    vector<int> pmt;
    int i = 0, j = -1;
    pmt.push_back(-1);
    while (i < pattern.size()) {
        while (j >= 0 && pattern[i] != pattern[j]) {
            j = pmt[j];
        }
        i++; j++;
        pmt.push_back(j);
    }
    return pmt;
}

void kmp(
  const string& word,
  const string& pattern,
  const vector<int>& pmt) {
    int i = 0, j = 0;
    while (i < word.size()) {
        while (j >= 0 && word[i] != pattern[j]) {
            j = pmt[j];
        }
        i++; j++;
        if (j == pattern.size()) {
            printf("Match at index %d\n", i - j); // modify to suit problem.
            j = pmt[j];
        }
    }
}

int main(int argc, char const *argv[])
{
  string a, b; cin >> a >> b;
  kmp(a, b, pmt(b));
  return 0;
}

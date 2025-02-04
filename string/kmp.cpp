// pref[i]: the maximum len that prefix match surfix in the substring s[0...i]
// pref[i] < n: meaningless if we said the whole string's prefix = string's surfix
vector<int> kmp(string &s) {
  vector<int> pref(n);
  int j = 0;
  for (int i = 1; i < n; i++) { // pref[0] = 0: because we not match whole string, so we start from 1
    while (j > 0 && s[i] != s[j]) j = pref[j - 1];
    pref[i] = s[i] == s[j] ? ++j : 0;
  }
  return pref;
}

int next[MAX][26];
for (int k = 0; k <= SZ(s); k++)
    for (int c = 0; c < 26; c++) {
        if (s[k] == (c + 'a')) next[k][c] = k + 1;
        else next[k][c] = k > 0 ? next[pref[k - 1]][c] : 0;
    }

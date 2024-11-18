struct PS2D {
    vector<vector<long long>> pref;
    PS2D (vector<vector<long long>> &arr) {
        int n = arr.size();
        int m = arr[0].size();
        pref.assign(n + 1, vector<long long>(m + 1));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                pref[i][j] = arr[i - 1][j - 1];
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + arr[i - 1][j - 1];
            }
        }
    }
    // pass in 0-based index
    long long query(int x1, int y1, int x2, int y2) {
        x1++; y1++; x2++; y2++;
        return pref[x2][y2] - pref[x1 - 1][y2] - pref[x2][y1 - 1] + pref[x1 - 1][y1 - 1];
    }
}

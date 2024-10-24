// stir[n][k]: number of way arrange k distinct objects into n same boxes (if n boxes are distinct then = stir[n][k]*n!)

long long stir[1001][1001], mod = 1e9 + 7;
auto init = [] {
    stir[0][0] = 1;
    for (int i = 1; i <= 1000; i++)
        for (int j = 1; j <= i; j++)
            stir[i][j] = (stir[i - 1][j - 1] + stir[i - 1][j] * j) % mod;
    return 0;
}();


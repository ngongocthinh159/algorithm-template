#define ll long long

long long expo(long long a, long long pow, long long m) {
    if (pow == 0) return 1;
    if (pow == 1) return a;

    long long tmp = expo(a, pow/2, m);
    tmp = (tmp * tmp) % m;
    if (pow&1) return (tmp * a) % m;
    else return tmp;
}

int getRandomNumber(int l, int r) {
    return rand()%(r - l + 1) + l;
}

struct SH {
    long long base = 33;
    long long m = 1e9 + 9; 
    int n;
    string s;
    vector<long long> prefixHash;
    vector<long long> basePow;
    vector<long long> iBasePow;
    
    SH(string queryStr) {
        s = queryStr;
        n = s.size();
        prefixHash.resize(n + 1);
        basePow.resize(n);
        iBasePow.resize(n);
        preCompute();
    }

    void preCompute() {
        basePow[0] = 1;
        for (int i = 1; i < n; i++) {
            basePow[i] = (basePow[i - 1] * base) % m;
        }

        iBasePow[0] = 1;
        if (n >= 2) {
            iBasePow[1] = expo(base, m - 2, m);
            for (int i = 2; i < n; i++) {
                iBasePow[i] = (iBasePow[i - 1] * iBasePow[1]) % m;
            }
        }

        for (int i = 1; i <= n; i++) {
            prefixHash[i] = (prefixHash[i - 1] + ((s[i - 1] - 'a' + 1) * basePow[i - 1]) % m) % m;
        }
    }

    long long hash_in_range(int l, int r) {
        long long tmp = (prefixHash[r + 1] - prefixHash[l]) % m;
        if (tmp < 0) tmp = (tmp + m) % m;
        return (tmp * iBasePow[l]) % m; 
    }
};

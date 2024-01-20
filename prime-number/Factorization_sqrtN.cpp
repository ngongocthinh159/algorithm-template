
// O(sqrt(N))
vector<long long> findFactors(long long n) {
    vector<long long> factors;
    for (long long p = 1; p * p <= n; p++) {
        if (n % p == 0) {
            factors.push_back(p);
            long long q = n / p;
            if (q != p) factors.push_back(q); // Check case: N = p*p
        }
    }
    return factors;
}
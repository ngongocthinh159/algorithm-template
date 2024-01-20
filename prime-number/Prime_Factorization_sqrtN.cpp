// O(sqrt(N))
vector<pair<long long, long long>> primeFactorization(long long n) {
    vector<pair<long long, long long>> res;     // factor : cnt
    for (long long i = 2; i <= sqrt(n); i == 2 ? i++ : i += 2) {
        if (n % i == 0) {
            long long cnt = 0;
            while (n % i == 0) {
                cnt++;
                n /= i;
            }
            res.push_back({i, cnt});
        }
    }
    if (n > 1) res.push_back({n, 1});      // n is prime itself
    return res;
}
struct PF {
    vector<long long> spf;
    vector<bool> isPrime;
    int maxN;

    PF(long long maxN) {
        this->maxN = maxN;
        this->spf = vector<long long>(maxN + 1);
        this->isPrime = vector<bool>(maxN + 1, true);
        spf_pre_compute(maxN);
    }

    // Sieve modified version to find smallest prime factor of [0 -> N]
    // O(n*log(log(n))), n max ~ 10^7 ok
    void spf_pre_compute(long long n) {  // Check prime from 2 -> N
        for (long long i = 0; i <= n; i++) {
            spf[i] = i;
        }
        for (long long i = 2; i <= sqrt(n); i++) {
            if (spf[i] == i) {
                for (long long j = i * i; j <= n; j += i) {  // iterate from i*i not i*2
                    spf[j] = min(spf[j], i);
                    isPrime[j] = false;
                }
            }
        }
    }

    vector<bool> getIsPrime() {
        return this->isPrime;
    }

    vector<long long> getSPF() {
        return this->spf;
    }

    // O(log(n))
    // Cnt number of divisors (divisible by n)
    long long factorCnt(long long n) {
        long long res = 1;
        while (n != 1) {
            long long factor = spf[n];
            long long cnt = 0;
            while (n % factor == 0) {
                cnt++;
                n /= factor;
            }
            res = res * (cnt + 1);  // Each power: can choost [0 -> power]
        }
        return res;
    }

    // O(log(n))
    // Get sum of all divisors (divisible by n)
    long long sumDivisors(long long n) {
        long long ans = 1;
        while (n != 1) {
            long long factor = spf[n];
            long long power = 0;
            long long factorPow = factor;  // factor^(power+1)
            while (n % factor == 0) {
                power++;
                factorPow = factorPow * factor;
                n /= factor;
            }
            ans = ans * ((factorPow - 1) / (factor - 1));  // Tong cap so nhan
        }
        return ans;
    }

    // O(log(n))
    vector<pair<long long, long long>> primeFactorize(long long n) {
        vector<pair<long long, long long>> res;  // factor : cnt
        while (n != 1) {
            long long factor = spf[n];
            long long cnt = 0;
            while (n % factor == 0) {
                cnt++;
                n /= factor;
            }
            res.push_back({factor, cnt});
        }
        return res;
    }
};

/**
 * Usage
    int mxN = 1e7;
    PF pf(mxN);

    for (int i = 10; i <= 40; i++) {
        cout << i << " = ";
        for (auto p : pf.primeFactorize(i)) {
            cout << p.first << "^" << p.second << " * ";
        }
        cout << "\n";
    }

    cout << pf.sumDivisors(64 * (pow(3, 3)));
    cout << pf.factorCnt(64 * (pow(3, 3)));
*/
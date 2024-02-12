struct PFOption {
    long long mxN;
    bool pre_cal_SPF;
    bool pre_cal_phi1ToN;
    PFOption() {
        this->mxN = 0;
        this->pre_cal_SPF = true;
        this->pre_cal_phi1ToN = false;
    }
    PFOption(long long mxN, bool pre_cal_SPF = true, bool pre_cal_phi1ToN = false) {
        this->mxN = mxN;
        this->pre_cal_SPF = pre_cal_SPF;
        this->pre_cal_phi1ToN = pre_cal_phi1ToN;
    }
};
struct PF {
    vector<bool> isPrime;   // isPrime[N]
    vector<long long> spf;  // smallest prime factor of N
    vector<long long> phi;  // phi of N
    PFOption options;       // options to Sieve pre compute 

    PF(PFOption options) {
        this->options = options;
        if (options.pre_cal_SPF) {
            this->isPrime = vector<bool>(options.mxN + 1, true);
            this->spf.resize(options.mxN + 1);
            pre_compute_spf();
        }
        if (options.pre_cal_phi1ToN) {
            this->phi.resize(options.mxN + 1);
            pre_compute_phi1ToN();
        }
    }

    // Sieve modified version to find smallest prime factor of [0 -> N]
    // O(n*log(log(n))), n max ~ 10^7 ok
    void pre_compute_spf() {  // Check prime from 2 -> N
        int n = options.mxN;

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

    // Sieve modified version to find phi [0 -> N]
    // O(n*log(n)), n max ~ 10^7 ok
    void pre_compute_phi1ToN() {
        int n = options.mxN;

        for (long long i = 0; i <= n; i++) {
            phi[i] = i;
        }
        for (long long i = 2; i <= n; i++) {
            if (phi[i] == i) {
                for (long long j = 2 * i; j <= n; j += i) {  // iterate from i*2
                    phi[j] = (phi[j] / i * (i - 1));
                }
            }
        }
    }

    vector<bool> getIsPrimeArray() {
        assert(options.pre_cal_SPF == true);
        return this->isPrime;
    }

    vector<long long> getSPFArray() {
        assert(options.pre_cal_SPF == true);
        return this->spf;
    }

    vector<long long> getPrecalPhiArray() {
        assert(options.pre_cal_phi1ToN == true);
        return this->phi;
    }

    // O(log(n))
    // Cnt number of divisors (divisible by n)
    // assert(options.pre_cal_SPF == true);
    // assert(n <= options.mxN);
    long long cntDivisors(long long n) {
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
    // assert(options.pre_cal_SPF == true);
    // assert(n <= options.mxN);
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

    // O(1)
    // assert(options.pre_cal_phi1ToN == true);
    // assert(n <= options.mxN);
    long long getPrecalPhi(long long n) {
        return phi[n];
    }

    // O(log(n))
    // Count number of X from [1, N] such that gcd(X,N) = 1 or Numbers of coprime number with N
    // assert(options.pre_cal_SPF == true);
    // assert(n <= options.mxN);
    long long calPhiLogN(long long n) {
        long long res = n;
        while (n != 1) {
            long long factor = spf[n];
            while (n % factor == 0) {
                n /= factor;
            }
            res = (res / factor * (factor - 1));
        }
        return res;
    }

    // O(log(n))
    // assert(options.pre_cal_SPF == true);
    // assert(n <= options.mxN);
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
    PF pf(PFOption(mxN, true, true));

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
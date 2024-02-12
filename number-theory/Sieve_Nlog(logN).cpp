// O(n*log(log(n))), n max ~ 10^7 ok
vector<bool> sieve(long long n) {  // Check prime from 2 -> N
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (long long i = 2; i <= sqrt(n); i++) {
        if (isPrime[i]) {
            for (long long j = i * i; j <= n; j += i) {
                isPrime[j] = false;  // iterate from i*i not i*2
            }
        }
    }
    return isPrime;
}
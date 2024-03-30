struct Combinatoric {
    ll mxN;
    vector<ll> fact;
    vector<ll> ifact;
    const int mod = 1e9 + 7;
    Combinatoric(ll mxN) {
        this->mxN = mxN;
        fact.resize(mxN+1);
        ifact.resize(mxN+1);
        pre_compute();
    }
    // O(n): pre_compute factorial and inverse factorial of mxN
    void pre_compute() {
        fact[0] = 1;
        for (ll i = 1; i <= this->mxN; i++) {
            fact[i] = mod_mul(i, fact[i-1], this->mod);
        }
        ifact[this->mxN] = mminvprime(fact[this->mxN], this->mod);
        for (ll i = this->mxN - 1; i >= 0; i--) {
            ifact[i] = mod_mul(ifact[i + 1], i + 1, this->mod);
        }
    }
    vector<ll> &getFactArray() {
        return this->fact;
    }
    vector<ll> &getIFactArray() {
        return this->ifact;
    }

    // C(n,r): number of ways to choose r items among n unique items
    // require: pre_compute of fact[mxN] and ifact[mxN] (factorial and inverse factorial)
    // require: r <= n 
    // O(1)
    ll combination1(ll n, ll r) {
        assert(n <= this->mxN);
        assert(r <= n);

        return mod_mul(fact[n], mod_mul(ifact[r], ifact[n - r], this->mod), this->mod);
    }
};
// C(n,r): in O(r + log(mod)) each time
// Use when call C(n,r) a few times or n is to large (r is still acceptable)
ll combination_Or(ll n, ll r, ll mod) {
    assert(r <= n);

    ll numerator = 1;
    ll denominator = 1;
    for (ll i = n; i >= n - r + 1; i--) {
        numerator = mod_mul(numerator, i, mod);
    }
    for (ll i = 1; i <= r; i++) {
        denominator = mod_mul(denominator, i, mod);
    }
    ll i_denominator = mminvprime(denominator, mod);
    return mod_mul(numerator, i_denominator, mod);
}

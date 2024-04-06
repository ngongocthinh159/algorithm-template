// Always call initialize_for_hashing() ONE time to intialize base_pow and i_base_pow arrays
// mxPow is the max pow needed: normally is max(s.len) - 1 ( last char has base^(n-1) )
// if not use random base then default base = 31
const int mod1 = (int) 1e9 + 7;
const int mod2 = (int) 1e9 + 9;
int base = 71;
vector<ll> random_bases = {31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89};
int prime_count = 2;
vector<vector<ll>> base_pow;
vector<vector<ll>> i_base_pow;
int gen_base() {
    int randomIdx = getRandomNumber(0, (int) random_bases.size() - 1);
    return random_bases[randomIdx];
}
// gen base and calculate basePows and iBasePows 
void initialize_for_hashing(int mxPow, bool randomBase = true) {
    assert(base_pow.size() == 0); // assure this function is called ONE
    assert(i_base_pow.size() == 0);

    if (randomBase) base = gen_base();
    int mxN = mxPow;

    base_pow.resize(prime_count);
    i_base_pow.resize(prime_count);
    
    base_pow[0].push_back(1);
    i_base_pow[0].push_back(1);
    if (mxPow >= 1) i_base_pow[0].push_back(expo(base, mod1 - 2, mod1));

    base_pow[1].push_back(1);
    i_base_pow[1].push_back(1);
    if (mxPow >= 1) i_base_pow[1].push_back(expo(base, mod2 - 2, mod2));
    
    for (int i = 1; i <= mxN; i++) {
        base_pow[0].push_back((base_pow[0].back() * base) % mod1);
        if (i >= 2) i_base_pow[0].push_back((i_base_pow[0].back() * i_base_pow[0][1]) % mod1);

        base_pow[1].push_back((base_pow[1].back() * base) % mod2);
        if (i >= 2) i_base_pow[1].push_back((i_base_pow[1].back() * i_base_pow[1][1]) % mod2);
    }
}
struct SH {
    ll n;
    vector<ll> prefix_hash_1;
    vector<ll> prefix_hash_2;
    
    SH(string &s) {
        // Generate prefix hash for current SH        
        n = s.size();
        
        prefix_hash_1.push_back(0);
        prefix_hash_2.push_back(0);

        for (int i = 1; i <= n; i++) {
            // ll mapped_num = s[i - 1] - 'a' + 1; // 1-based index
            // assert(mapped_num < base);
            
            // Prefix hash for mod1
            prefix_hash_1.push_back((prefix_hash_1[i - 1] + (((1LL*s[i - 1] - 'a' + 1)*base_pow[0][i - 1]) % mod1)) % mod1);
            
            // Prefix hash for mod2
            prefix_hash_2.push_back((prefix_hash_2[i - 1] + (((1LL*s[i - 1] - 'a' + 1)*base_pow[1][i - 1]) % mod2)) % mod2);
        }
    }

    // O(1)
    // Base 0: Calculate hash of a range
    inline pair<ll, ll> hash_in_range(const int l, const int r) const {
        pair<ll, ll> res;
        
        // Hash of range [l, r] for mod1
        ll hash1 = (prefix_hash_1[r + 1] - prefix_hash_1[l]) % mod1;
        if (hash1 < 0) hash1 = (hash1 + mod1) % mod1;
        hash1 = (hash1 * i_base_pow[0][l]) % mod1;
        res.first = hash1;

        // Hash of range [l, r] for mod2
        ll hash2 = (prefix_hash_2[r + 1] - prefix_hash_2[l]) % mod2;
        if (hash2 < 0) hash2 = (hash2 + mod2) % mod2;
        hash2 = (hash2 * i_base_pow[1][l]) % mod2;
        res.second = hash2;

        return res;
    }

    inline pair<ll, ll> operator() (const int l, const int r) const {
        return hash_in_range(l, r);
    }
};
// O(1)
// sh2 must be a SH object of the reversed string
bool is_palindrome(ll l, ll r, SH &sh1, SH &sh2) {
    ll l2 = sh1.n - (r + 1);
    ll r2 = sh1.n - (l + 1);
    return sh1.hash_in_range(l, r) == sh2.hash_in_range(l2, r2);
}







// Usage
// void pre_compute() {
//     int mxStringSize = 1e5 + 5;
//     initialize_for_hashing(mxStringSize, false);
// }
// void solve() {
//     SH hashS(s);
//     pair<ll, ll> res = hashS(l, r);
// }
//
// "Must" Adjust global mxn (max base pow need: normally max(string.size()) + 1)
// Adjust should random base for every compile or use default global base is 31
// Adjust list of random bases: each base > largest unique mapped values. Base can not be prime
// Adjust list of mods: each mod must be prime and should ~= 10^9 (normally two primes is ok, if collision use three primes)
// Adjust mapped values in map_to_ll function: each different char or int must be mapped into a unique ll
ll globalMxN = 1e6 + 5;
bool randomBase = true;
vector<int> random_bases = {31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89};
ll globalBase = 31;
const vector<ll> primes = {1000000009, 1000000007};

vector<vector<ll>> base_pow;
vector<vector<ll>> i_base_pow;
bool isRandomBaseGenerated = false;
bool isBasePowPrecomputed = false;
int gen_base() {
    int randomIdx = getRandomNumber(0, (int) random_bases.size() - 1);
    return random_bases[randomIdx];
}
void pre_compute_base_pow() {
    isBasePowPrecomputed = true;

    int prime_count = primes.size();
    base_pow = vector<vector<ll>>(prime_count, vector<ll>(globalMxN + 1));
    i_base_pow = vector<vector<ll>>(prime_count, vector<ll>(globalMxN + 1));

    for (int j = 0; j < primes.size(); j++) {
        base_pow[j][0] = 1;
        for (int i = 1; i <= globalMxN; i++) {
            base_pow[j][i] = (base_pow[j][i - 1] * globalBase) % primes[j]; 
        }
        
        i_base_pow[j][0] = 1;
        i_base_pow[j][1] = expo(globalBase, primes[j] - 2, primes[j]);
        for (int i = 2; i <= globalMxN; i++) {
            i_base_pow[j][i] = (i_base_pow[j][i - 1] * i_base_pow[j][1]) % primes[j];
        }
    }
}
struct SH {
    ll n;
    string s;
    vector<vector<ll>> prefix_hash;
    
    SH(string queryString) {
        assert(primes.size() > 0);
        assert(queryString.size() > 0);
        assert((int) s.size() <= globalMxN);

        if (randomBase && !isRandomBaseGenerated) {
            globalBase = gen_base();
            isRandomBaseGenerated = true;
        }

        if (!isBasePowPrecomputed) {
            pre_compute_base_pow();
            isBasePowPrecomputed = true;
        }

        // Generate prefix hash for current SH        
        s = queryString;
        n = s.size();
        pre_compute_prefix_hash();
    }

    void pre_compute_prefix_hash() {
        ll prime_count = primes.size();
        prefix_hash = vector<vector<ll>>(prime_count, vector<ll>(n + 1));

        for (int j = 0; j < primes.size(); j++) {
            for (int i = 1; i <= n; i++) {
                ll mapped_number = map_to_ll(s[i - 1]);
                prefix_hash[j][i] = (prefix_hash[j][i - 1] + ((mapped_number*base_pow[j][i - 1]) % primes[j])) % primes[j];
            }
        }
    }

    // Mapping from a character of S to a number
    // Each unique character must be mapped into a unique number (same for array of integers)
    // The smallest mapped number should be 1 (not 0)
    ll map_to_ll(char &c) {
        return (c - 'a' + 1);
    }

    // O(1)
    // Base 0: Calculate hash of a range
    vector<ll> hash_in_range(ll l, ll r) {
        vector<ll> res;
        for (int i = 0; i < primes.size(); i++) {
            ll tmp = (prefix_hash[i][r + 1] - prefix_hash[i][l]) % primes[i];
            if (tmp < 0) tmp = (tmp + primes[i]) % primes[i];
            tmp = (tmp * i_base_pow[i][l]) % primes[i];
            res.push_back(tmp);
        }
        return res;
    }
};
// O(1)
// sh2 must be a SH object of the reversed string
bool is_palindrome(ll l, ll r, SH &sh1, SH &sh2) {
    ll size = sh1.s.size();
    ll l2 = size - (r + 1);
    ll r2 = size - (l + 1);
    return sh1.hash_in_range(l, r) == sh2.hash_in_range(l2, r2);
}




// usage
// SH hashS(s);
// SH hashP(p);
// hashS.hash_in_range(l1, r1) == hashP.hash_in_range(l2, r2);
// is_palindrome(l, r, hashS, hashP);


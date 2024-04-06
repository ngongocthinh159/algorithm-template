// Random base at each start
int gen_base(const int before, const int after) {
    int base = getRandomNumber(before + 1, after);
    return base % 2 == 0 ? base - 1 : base;
}

struct PolyHash {
    // -------- Static variables --------
    static const int mod = (int)1e9 + 123;  // prime mod of polynomial hashing
    static vector<int> pow1;                // powers of base modulo mod
    static vector<ull> pow2;                // powers of base modulo 2^64
    static int base;                        // base (point of hashing)

    // --------- Static functons --------
    static inline int diff(int a, int b) {
        // Diff between `a` and `b` modulo mod (0 <= a < mod, 0 <= b < mod)
        return (a -= b) < 0 ? a + mod : a;
    }

    // -------------- Variables of class -------------
    vector<int> pref1;  // Hash on prefix modulo mod
    vector<ull> pref2;  // Hash on prefix modulo 2^64

    // Cunstructor from string:
    PolyHash(const string& s) {
        assert(base < mod);
        const int n = s.size();  // Firstly calculated needed power of base:
        while ((int)pow1.size() <= n) {
            pow1.push_back(1LL * pow1.back() * base % mod);
            pow2.push_back(pow2.back() * base);
        }

        // Initilize prefix hash for each mod: pref[k] = prefix hash of first k elements
        pref1 = vector<int>(s.size() + 1u, 0);
        pref2 = vector<ull>(s.size() + 1u, 0);
        for (int i = 0; i < n; ++i) {  // Fill arrays with polynomial hashes on prefix
            assert(base > s[i]);
            pref1[i + 1] = (pref1[i] + 1LL * s[i] * pow1[i]) % mod;
            pref2[i + 1] = pref2[i] + s[i] * pow2[i];  // C++ auto % 2^64 for ull
        }
    }

    // Polynomial hash of subsequence [pos, pos+len)
    // If mxPow != 0, value automatically multiply on base in needed power. Finally base ^ mxPow
    // pos: is index in the string
    // mxPow: max length of all the strings, specify when call this function
    inline pair<int, ull> operator()(const int pos, const int len, const int mxPow) const {
        int hash1 = pref1[pos + len] - pref1[pos];
        ull hash2 = pref2[pos + len] - pref2[pos];
        if (hash1 < 0) hash1 += mod;
        if (mxPow != 0) {
            hash1 = 1LL * hash1 * pow1[mxPow - (pos + len - 1)] % mod;
            hash2 *= pow2[mxPow - (pos + len - 1)];
        }
        return make_pair(hash1, hash2);
    }
};

// Init static variables of PolyHash class:
int PolyHash::base((int)1e9 + 7);
vector<int> PolyHash::pow1{1};
vector<ull> PolyHash::pow2{1};

const int mxPow = max((int)s1.size(), (int)s2.size()); // phai khai bao khi tinh hash, mxPow la max(s.len)
PolyHash::base = gen_base(256, PolyHash::base); // gen random base [256->1e9 + 7]



/**
 * Use:
    const int mxPow = max((int)s1.size(), (int)s2.size()); // phai khai bao khi tinh hash, mxPow la max(s.len)
    PolyHash::base = gen_base(256, PolyHash::base); // gen random base [256->1e9 + 7]

    PolyHash h1(s1), h2(s2);
    
    const auto need = h2(0, (int)s2.size(), mxPow);
    for (int l = 0; l + (int)s2.size() <= s1.size(); l++) {
        if (h1(l, (int)s2.size(), mxPow) == need) cout << l << " "; // tinh hash h1(l, len, mxPow)
    }
*/
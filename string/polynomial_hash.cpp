// Random base at each start
int gen_base(const int before, const int after) {
    int base = getRandomNumber(before + 1, after);
    return base % 2 == 0 ? base - 1 : base;
}

struct PolyHash {
    // -------- Static variables --------
    static const ull mod = (ull(1) << 61) - 1; // prime mod of hashing
    static int base;                           // odd base of hashing
    static std::vector<ull> pow;               // powers of base modulo mod;
 
    // -------- Static functions --------
    static inline ull add(ull a, ull b) {
        // Calculate (a + b) % mod, 0 <= a < mod, 0 <= b < mod
        return (a += b) < mod ? a : a - mod;
    }
 
    static inline ull sub(ull a, ull b) {
        // Calculate (a - b) % mod, 0 <= a < mod, 0 <= b < mod
        return (a -= b) < mod ? a : a + mod;
    }
 
    static inline ull mul(ull a, ull b){
        // Calculate (a * b) % mod, 0 <= a < mod, 0 <= b < mod
        ull l1 = (uint32_t)a, h1 = a >> 32, l2 = (uint32_t)b, h2 = b >> 32;
        ull l = l1*l2, m = l1*h2 + l2*h1, h = h1*h2;
        ull ret = (l & mod) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
        ret = (ret & mod) + (ret >> 61);
        ret = (ret & mod) + (ret >> 61);
        return ret-1;
    }
 
    // -------- Variables of class --------
    std::vector<ull> pref; // polynomial hash on prefix
 
    // Constructor from string:
    PolyHash(const std::string& s) 
        : pref(s.size()+1u, 0) 
    {
        // Pre-calculate powers of base:
        while (pow.size() <= s.size()) {
            pow.push_back(mul(pow.back(), base));
        }
        // Calculate polinomial hash on prefix:
        for (int i = 0; i < (int)s.size(); ++i) {
            pref[i+1] = add(mul(pref[i], base), s[i]);
        }
    }
 
    // Get hash from [pos, pos+len-1] segment of string
    inline ull operator()(const int pos, const int len) const {
        return sub(pref[pos+len], mul(pref[pos], pow[len]));
    }
 
};
 
// Init static variables of class PolyHash:
int PolyHash::base((int)1e9+7);
std::vector<ull> PolyHash::pow{1};




/**
PolyHash::base = gen_base(256, 2e9);
PolyHash hash_s(s);
hash_s(l, len);
*/
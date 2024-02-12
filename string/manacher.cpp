// "$" + s + "^": handle edge case when out of bound to compare

// first i = 1 => initialize r and l out of bound: 0 and 2
// l l + 1 ... l + k ... center ... center + m ... i ... r - 1 r
//      => [l+1, r-1] always in valid bound (palindrome with furthest r index)
//      get max of (r-i, p[l + r - i]): len from i to valid r-1, and len of left asymetric palindrom
//      
//      After get max => Explore current palindrom window to both left and right (while still valid)
//
//      Update bound r and l if new bound exceed previous r
struct Manacher {
    string s; // aabb
    vector<int> P; // #a#a#b#b#
    Manacher(string s) {
        this->s = s;
        preprocess();
    }

    void preprocess() {
        string t = "";
        for (auto c : this->s) {
            t += '#';
            t += c;
        }
        t += "#";
        this->P = manacher_odd(t);
    }

    vector<int> getPArray() {
        return this->P;
    }

    // 0-based index
    // Odd: cenIdx
    // Even (only cenIdx >= 1): cenIdx && cenIdx - 1 
    int getLongest(int cenIdx, bool odd) {
        int idx;
        if (odd) idx = 1 + 2*cenIdx;
        else idx = 1 + 2*cenIdx - 1;
        return this->P[idx] - 1;
    }
    
    // 0-based index
    bool isPalindrome(int l, int r) {
        return (r-l+1) <= getLongest((l+r+1)/2, l%2==r%2);
    }

    vector<int> manacher_odd(string s) {
        int n = s.size();
        s = "$" + s + "^";
        vector<int> p(n + 2);
        int l = 0, r = 2;   
        for (int i = 1; i <= n; i++) {
            p[i] = max(0, min(r - i, p[l + r - i]));    
            while (s[i - p[i]] == s[i + p[i]]) {
                p[i]++;
            }
            if (i + p[i] > r) {
                l = i - p[i]; r = i + p[i];
            }
        }
        return vector<int>(p.begin() + 1, p.end() - 1);
    }
};

/**
 * Usage:
 *  int countSubstrings(string s) {
        Manacher m(s);
        int ans = 0;
        for (int i = 0; i < s.size(); i++) {
            ans += ceil((double) m.getLongest(i, true)/2);
            if (i>=1) ans += m.getLongest(i, false)/2;
        }
        return ans;
    }
*/
struct Manacher {
    string s;
    int n;
    vector<int> p; // p[i]: center i-th has palindrome bound [k,j] then p[i] = j - i + 1 = i - k + 1 (len of one side from center)
    Manacher(string &s) {
        this->s = s;
        n = s.size();
        _pre_process();
    }
    void _pre_process() {
        // transform orginal "ABA" => "#A#B#A#"
        string t;
        for (auto c : s) t += '#', t += c;
        t += '#';
        p = _manacher_odd(t); // p array is actually counted for transformed string
    }
    vector<int> _manacher_odd(string &str) {
        int n = str.size();
        string t = '^' + str + '$'; // "$" + s + "^": handle edge case when out of bound to compare
        vector<int> p(n + 2);
        for (int i = 1, l = 1, r = 1; i <= n; i++) {
            if (i <= r) p[i] = min(p[l + r - i], r - i + 1);
            while (t[i + p[i]] == t[i - p[i]]) ++p[i];
            if (i + p[i] - 1 > r) l = i - p[i] + 1,  r = i + p[i] - 1;
        }
        return vector<int>(p.begin() + 1, p.end() - 1);
    }

    int get_longest(int centerIdx, bool odd = true) {
        if (!odd) assert(centerIdx >= 1);
        
        int pidx = odd ? 2*centerIdx + 1 : 2*centerIdx; // convert from original to tranformed
        return p[pidx] - 1;
    }

    bool is_palindrome(int l, int r) {
        int centerIdx = (l + r + 1)/2;
        return get_longest(centerIdx, l%2==r%2) >= (r - l + 1);
    }

    // p[i]: center i-th has palindrome bound [k,j] then p[i] = j - i + 1 = i - k + 1 (len of one side from center)
    int get_p_at(int centerIdx, bool odd = true) {
        int pidx = odd ? 2*centerIdx + 1 : 2*centerIdx;
        return p[pidx]/2;
    }
};

/**
 * Usage:
 *  int countSubstrings(string s) {
        Manacher mana(s);
        for (int i = 0; i < n; i++) {
            mana.get_longest(i);
            if (i >= 1) mana.get_longest(i, false);
            mana.get_p_at(i);
        }
        mana.is_palindrome(0, n - 1);
    }
*/
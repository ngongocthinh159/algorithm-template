
struct SuffixArray {
    string s;
    int n;
    int alphabet;
    vector<int> _p, _lcp, _idx_to_pidx;
    vector<vector<int>> rmq;
    bool query_lcp_ij = false;

    SuffixArray(string &str, bool query_lcp_ij = false, int alphabet = 256) {
        s = str;
        n =  s.size();
        this->alphabet = alphabet;
        _p = suffix_array_construction(s);
        _lcp = lcp_construction(s, _p);

        if (query_lcp_ij) {
            this->query_lcp_ij = true;
            int LOG = __lg(n) + 1;
            rmq.assign(LOG + 1, vector<int>(_lcp.size()));
            for (int i = 0; i < _lcp.size(); i++) rmq[0][i] = _lcp[i];
            for (int j = 1; j <= LOG; j++)
                for (int i = 0; i + (1 << j) - 1 < _lcp.size(); i++)
                    rmq[j][i] = min(rmq[j - 1][i], rmq[j - 1][i + (1 << (j - 1))]);
        }
    }

    vector<int> sort_cyclic_shifts(string const& s) {
        int n = s.size();

        // h = 0, sorted n cycle strings by comparing 2^0 = 1 (the first) character
        vector<int> p(n), c(n), cnt(max(alphabet, n), 0);
        for (int i = 0; i < n; i++)
            cnt[s[i]]++;
        for (int i = 1; i < alphabet; i++)
            cnt[i] += cnt[i-1];
        for (int i = 0; i < n; i++)
            p[--cnt[s[i]]] = i;
        c[p[0]] = 0;
        int classes = 1;
        for (int i = 1; i < n; i++) {
            if (s[p[i]] != s[p[i-1]])
                classes++;
            c[p[i]] = classes - 1;
        }

        // h = 1, 2,.. sorted n cycle strings by comparing 2^1,2,3.. first characters
        vector<int> pn(n), cn(n);
        for (int h = 0; (1 << h) < n; ++h) {
            for (int i = 0; i < n; i++) {
                pn[i] = p[i] - (1 << h);
                if (pn[i] < 0)
                    pn[i] += n;
            }
            fill(cnt.begin(), cnt.begin() + classes, 0);
            for (int i = 0; i < n; i++)
                cnt[c[pn[i]]]++;
            for (int i = 1; i < classes; i++)
                cnt[i] += cnt[i-1];
            for (int i = n-1; i >= 0; i--)
                p[--cnt[c[pn[i]]]] = pn[i];
            cn[p[0]] = 0;
            classes = 1;
            for (int i = 1; i < n; i++) {
                pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
                pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
                if (cur != prev)
                    ++classes;
                cn[p[i]] = classes - 1;
            }
            c.swap(cn);
        }
        return p;
    }

    vector<int> suffix_array_construction(string s) {
        s += (char) 0;
        vector<int> sorted_shifts = sort_cyclic_shifts(s);
        sorted_shifts.erase(sorted_shifts.begin());
        return sorted_shifts;
    }

    vector<int> lcp_construction(string const& s, vector<int> const& p) {
        // Kasai algorithm for lcp construction
        _idx_to_pidx.resize(n);
        for (int i = 0; i < n; i++)
            _idx_to_pidx[_p[i]] = i;

        int n = s.size();
        int k = 0;
        vector<int> lcp(n-1, 0);
        for (int i = 0; i < n; i++) {
            if (_idx_to_pidx[i] == n - 1) {
                k = 0;
                continue;
            }
            int j = p[_idx_to_pidx[i] + 1];
            while (i + k < n && j + k < n && s[i+k] == s[j+k])
                k++;
            lcp[_idx_to_pidx[i]] = k;
            if (k)
                k--;
        }
        return lcp;
    }

    const vector<int>& get_p_array() {
        return _p;
    }

    const vector<int>& get_lcp_array() {
        return _lcp;
    }

    const vector<int>& get_idx_to_pidx_array() {
        return _idx_to_pidx;
    }

    int _query_rmq(int l, int r) {
        int bit = 32 - __builtin_clz(r - l + 1) - 1;
        return min(rmq[bit][l], rmq[bit][r - (1 << bit) + 1]);
    }

    // query largest common prefix of 2 suffixes starting at index i and j in original string
    int query_lcp_suffix(int i, int j) {
        assert(i < n);
        assert(j < n);
        assert(query_lcp_ij == true);

        if (i == j) return n - i;
        int l = _idx_to_pidx[i], r = _idx_to_pidx[j];
        if (l > r) swap(l, r);
        r--;
        return _query_rmq(l, r);
    }

    // query largest common prefix of 2 suffixes at index i and j after sorted in p array
    int query_lcp_p_array(int i, int j) {
        assert(i < n);
        assert(j < n);
        assert(i <= j);
        assert(query_lcp_ij == true);

        if (i == j) return n - _p[i];
        j--;
        return _query_rmq(i, j);
    }

    // compare two sub-strings in the original string O(1)
    int compare_substr(int l1, int r1, int l2, int r2) {
        assert(query_lcp_ij == true);

        int len1 = r1 - l1 + 1;
        int len2 = r2 - l2 + 1;
        int pidx1 = _idx_to_pidx[l1];
        int pidx2 = _idx_to_pidx[l2];
        if (pidx1 > pidx2) swap(pidx1, pidx2);
        int common_len = query_lcp_p_array(pidx1, pidx2);
        common_len = min(common_len, min(len1, len2));

        int compare_idx1 = l1 + common_len;
        int compare_idx2 = l2 + common_len;
        if (compare_idx1 <= r1 && compare_idx2 <= r2) {
            if (s[compare_idx1] < s[compare_idx2]) return -1;
            return 1;
        } 
        else if (compare_idx1 <= r1) return 1;
        else if (compare_idx2 <= r2) return -1;
        return 0;
    }

        int _compare_with_suffix(string &t, int suffix_idx) {
        int i = 0, j = suffix_idx;
        while (i < t.size() && j < n && t[i] == s[j]) i++, j++;

        if (i < t.size() && j < n) {
            if (t[i] < s[j]) return -1;
            return 1;
        }
        if (i < t.size()) return 1;
        if (j < n) return -1;
        return 0;
    }
    // search an arbitrary str M in the original str O(m*logn)
    // return [l, r] in p array => str occurs at position [p[l], p[l + 1], ..., p[r]]
    // return [-1, -1] if str do not occur
    pair<int,int> search_str(string &t) {
        int lower_bound = -1, upper_bound = -1;
        {
            int l = -1, r = n;
            while (r - l > 1) {
                int m = l + (r - l)/2;
                if (_compare_with_suffix(t, _p[m]) <= 0)
                    r = m;
                else
                    l = m;
            }
            if (r != n) lower_bound = r;
        }
        if (lower_bound == -1) return {-1, -1};

        {
            int l = -1, r = n;
            while (r - l > 1) {
                int m = l + (r - l)/2;
                if (_compare_with_suffix(t, _p[m]) == -1)
                    r = m;
                else
                    l = m;
            }
            upper_bound = r;
        }
        if (lower_bound == upper_bound) return {-1, -1};

        return {lower_bound, --upper_bound};
    }

    void _print() {
        const char* headers[] = {"Index", "Suffix", "P", "LCP"};
        printf("%-5s %-20s %-5s %-5s\n", headers[0], headers[1], headers[2], headers[3]);
        for (int i = 0; i < n; i++) {
            if (i < n - 1)
                printf("%-5d %-20s %-5d %-5d\n", i, s.substr(_p[i]).c_str(), _p[i], _lcp[i]);
            else    
                printf("%-5d %-20s %-5d\n", i, s.substr(_p[i]).c_str(), _p[i]);
        }
        fflush(stdout);
    }
};

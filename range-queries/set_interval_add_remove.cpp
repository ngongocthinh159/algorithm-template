// all query must be half-open interval: [l, r)
class RangeDS {
public:
    set<pair<int,int>> S;

    RangeDS() {}
    
    void addRange(int left, int right) {
        auto l = S.upper_bound({left, INT_MAX}); // try l is the first range intersect with added range (l or l - 1) 
        auto r = S.upper_bound({right, INT_MAX}); // try r is the first not intersect range => if there is at least one intersect then r - 1 is the last
        if (l != S.begin()) {
            l--;
            if (l->second < left) l++; // check for l - 1, if l - 1 not valid => l is the candidate for starting of intersect ranges
        }
        if (l != r) { // right now: l is the first intersect, r is the first not intersect => l should != r to have at least 1 intersect range
            left = min(l->first, left);
            right = max((--r)->second, right);
            S.erase(l, ++r);
        }
        S.insert({left, right});
    }
    
    bool queryRange(int left, int right) {
        bool res;
        auto l = S.upper_bound({left, INT_MAX});
        if (l == S.begin() || (--l)->second < right) return false;
        return true;
    }
    
    void removeRange(int left, int right) {
        auto l = S.upper_bound({left, INT_MAX});
        auto r = S.upper_bound({right, INT_MAX});
        if (l != S.begin()) {
            l--;
            if (l->second < left) l++;
        }
        if (l != r) {
            int l1 = min(left, l->first);
            int r1 = max(right, (--r)->second);

            S.erase(l, ++r);

            if (l1 < left) S.insert({l1, left});
            if (r1 > right) S.insert({right, r1});
        }
    }
};

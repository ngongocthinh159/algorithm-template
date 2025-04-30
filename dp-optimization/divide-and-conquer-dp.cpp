#include <bits/stdc++.h>
using namespace std;

int m, n;
vector<long long> dp, ndp;

// Conditions for application:
// + Should be partition dp, each partition produce a cost C(l, r)
// + Cost function C(l, r) should statisfy the Quadrangle Inequality (so that closest optimal point to the left opt(r) is non-decreasing when r increase)

// + Can imagine dp[i][j] as the optimal solution if we only have i partitions and consider first j elements
//      then we can think each dp[i] is a row/layer in a DP table, for each row we need find answer for dp[i][j in 0 -> n - 1]
//      then for each j we need find opt(j) as the optimal relaxation index closest/furthest to j
//      If  we can test that cost function for a segment C(l, r) is QI then the opt(j) will stay or increase when j increase
//      => for each j we do not need go from 0 but opt(j - 1) to find the optimal relaxation point
//      => opt(j - 1) <= opt(j) <= opt(j + 1)  (for one row dp[i])

// Reduce: O(m * n^2) -> O(m * n * logn)

// General template for d&c dp
long long C(int i, int j); // implement cost function

void compute(int l, int r, int optl, int optr) {
    if (l > r)
        return;

    int mid = (l + r) >> 1; // for interval (l -> r) we calculate ndp[mid] and opt(mid) first
    pair<long long, int> best = {LLONG_MAX, -1};

    for (int k = optl; k <= min(mid, optr); k++) {
        best = min(best, {(k ? dp[k - 1] : 0) + C(k, mid), k}); // relax from in range [optl, optr] not from 0
    }

    ndp[mid] = best.first;
    int opt = best.second;

    compute(l, mid - 1, optl, opt); // all ndp[0 -> l] should have opt point <= opt(mid)
    compute(mid + 1, r, opt, optr); // all ndp[mid + 1 -> r] should have opt point >= opt(mid)
}

long long solve() {
    dp.assign(n,0);
    ndp.assign(n,0);

    for (int i = 0; i < n; i++)
        dp[i] = C(0, i); // initialize the first layer

    for (int i = 1; i < m; i++) {
        compute(0, n - 1, 0, n - 1); // compute each layer to ndp
        swap(dp, ndp);
    }

    return dp[n - 1];
}

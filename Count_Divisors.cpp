#include <bits/stdc++.h>
using namespace std;

#define ll long long
// Count all divisable numbers from 1 -> N
// Ex: 8 has 4 divisors: 1, 2, 4, 8
// Time complexity: O(n*log(n))
// Time = n + n / 2 + n / 3 + n / 4 + ... = n * (1 + 1/2 + 1/3 + ...)
// Harmonic series => Time = n * log(n)
ll* countDivisors(ll n) {
    ll cnt[n + 1];
    memset(cnt, 0, sizeof(cnt));
    for (ll i = 1; i <= n; i++) {
        for (ll j = i; j <= n; j += i) {
            cnt[j]++;
        }
    }

    // Print result
    for (ll i = 0; i <= n; i++) {
        cout << i << " has " << cnt[i] << " divisors include self\n";
    }

    return cnt;
}

int main() {
   countDivisors(100);
}
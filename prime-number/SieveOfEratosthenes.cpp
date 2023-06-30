#include <bits/stdc++.h>
using namespace std;

/* Given a number n, get all primes <= n. For example, if the given number is 10, output 2, 3, 5, 7.
   If prime[i] == true => i is prime number
*/
#define ll long long
bool* SieveOfEratosthenes(ll N) { // Check prime from 2 -> N
    static bool prime[N + 1];
    memset(prime, true, sizeof(prime));
    for (ll i = 2; i * i <= N; i++) {
        if (!prime[i]) continue;

        for (ll j = i*i; j <= N; j+=i) {
            prime[j] = false;
        }
    }
    return prime;
}

/* Main()  function */
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    solve();
}

void solve() {
    const ll N = 1e7; // Check prime from 2 -> 10^7
    bool* prime = SieveOfEratosthenes(N);
    for (ll i = 2; i <= N; i++) {
        if (prime[i]) cout << i << " is a prime number\n";
        else cout << i << " is not a prime number\n";
    }
}

/* Main() Ends Here */
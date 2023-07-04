#include <bits/stdc++.h>
using namespace std;

#define ll long long
// Worst case: loop run for log(sqrt(n)) times. For ex: 11, 121,...
void primeFactorization(ll n) { 
    // Divide by 2 first until cannot
    while (n%2 == 0) {
        cout << 2 << " ";
        n /= 2;
    }

    // All remaining factors must be odd number start with 3
    // Prime factor can not greater than its square root
    for (ll j = 3; j*j <= n; j += 2) {
        while (n % j == 0) {
            cout << j << " ";
            n /= j;
        }
    }

    // Handle cases if after all operation, n is still a prime and n > 2
    if (n > 2) cout << n << " ";
}

int main() {
    primeFactorization(8); // Find prime factor of 100
}
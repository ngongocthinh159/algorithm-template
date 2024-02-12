#include <bits/stdc++.h>
using namespace std;

#define ll long long
/* 
    Euler’s Totient function Φ(n) for an input n is the count of numbers in {1, 2, 3, …, n-1} 
    that are  co-prime to n, i.e., the numbers whose GCD (Greatest Common Divisor) with n is 1.


    Approach using Euler’s product formula:
    Value of Φ(n) = n * (product of (1 – 1/p) for all prime factors p of n).
    For example value of Φ(6) = 6 * (1-1/2) * (1 – 1/3) = 2. (as 2 and 3 is prime factors of 6).
    Then the first things is to get all prime factors of n, then product the result follow the formula
    *** Note: a*(1 - 1/p) = a - a/p. Below is the implementation using a - a/p to avoid float number calculation
 */
ll phi(ll n) {
    ll res = n;
    bool isFirst = true;

    // Divide by 2 first until cannot
    while (n%2 == 0) {
        // cout << 2 << " ";
        if (isFirst) {res -= res/2; isFirst = false;}
        n /= 2;
    }

    // All remaining factors must be odd number start with 3
    // Prime factor can not greater than its square root
    for (ll j = 3; j*j <= n; j += 2) {
        isFirst = true;
        while (n % j == 0) {
            // cout << j << " ";
            if (isFirst) {res -= res/j; isFirst = false;}
            n /= j;
        }
    }

    // Handle cases if after all operation, n is still a prime and n > 2 (n is the last prime factor now)
    if (n > 2) {
        // cout << n << " ";
        res -= res/n;
    }
    
    return (ll) res;
}

int main() {
    int n;
     
    for(n = 1; n <= 10; n++) {
        cout << "Phi" << "("
             << n << ")" << " = "
             << phi(n) <<endl;
    }
}
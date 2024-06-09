#include <bits/stdc++.h>
using namespace std;

#define ll long long
// Count all divisable numbers from 1 -> N
// Ex: 8 has 4 divisors: 1, 2, 4, 8
// Time complexity: O(n*log(n))
// Time = n + n / 2 + n / 3 + n / 4 + ... = n * (1 + 1/2 + 1/3 + ...)
// Harmonic series => Time = n * log(n)

// Upper bound for number of divisors of number N in range [1, N]: O(n^(1/3))
// Actual maximum number of divisors for n-digit number: https://oeis.org/A066150
// For a number around 10^9 : 1344 divisors is maximum
// For a number around 1o^18: 103680 divisors is maximum
// The smallest and largest n-digit integers that have the maximal number of divisors: https://oeis.org/A066151, https://oeis.org/A069650
const int mxn = 1e6 + 5;
int number_of_divisors[mxn + 1]; // include itself
void countDivisors() {
    for (int i = 1; i <= mxn; i++) {
        for (int j = i; j <= mxn; j += i) {
            number_of_divisors[j]++;
        }
    }

    // Print result
    for (int i = 0; i <= mxn; i++) {
        cout << i << " has " << number_of_divisors[i] << " divisors include itself\n";
    }
}

ll sum_of_divisors[mxn + 1]; // include itseld
void sumDivisors() {
    for (int i = 1; i <= mxn; i++) {
        for (int j = i; j <= mxn; j += i) {
            sum_of_divisors[j] += i;
        }
    }

    // Print result
    for (int i = 0; i <= mxn; i++) {
        cout << "sum of all divisors include itself till " << i << ": " << sum_of_divisors[i] << "\n";
    }
}

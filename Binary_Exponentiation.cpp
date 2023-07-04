#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll pow_mod(ll x, ll n, ll m) {
    if (n == 0) return 1;

    ll tmp = pow_mod(x, n/2, m);
    if (n%2 == 0) return (tmp*tmp)%m;
    else return (((tmp*tmp)%m)*x)%m;
}
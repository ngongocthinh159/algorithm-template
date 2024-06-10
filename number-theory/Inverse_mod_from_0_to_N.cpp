#define ll long long
const int MOD = 1e9 + 7;

const int mxn = 1e5 + 5;
ll inv[mxn + 1];
void pre_compute() {
    inv[0] = inv[1] = 1;
	for (int i = 2; i <= mxn; i++) {
		inv[i] = ((MOD - MOD / i) * inv[MOD % i] % MOD) % MOD;
	}
}

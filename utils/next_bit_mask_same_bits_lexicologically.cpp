// There's a neat little trick to find the lexicographically next bit mask with the same number of bits as a given one, which you can use here:

inline int next_bit_perm(int v) {
    int t = v | (v - 1);
    return (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(v) + 1));
}
// ...
// handle 0 bits separately
for (int k = 1; k <= n; ++k) {
    for (int w = (1<<k)-1; w < (1<<n); w = next_bit_perm(w)) {
        // do whatever you want with w
    }
}

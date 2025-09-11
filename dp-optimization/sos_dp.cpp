/*
    Given an integer array: [a0, a1, ..., an-1]   (N elements)
    For each mask, calculate the function F(mask) = Sum of a[i], with i is submask of mask
        For ex: F(3) = F(101) = a[2] + a[0]

    SOS dp:
	dp[mask][i]: the subset sum of all indexes that has binary presentation are submask of mask, but those indexes must only different by the first i-th LSB (0 based => first i + 1 LSB bits)

	For ex: S(101 1010, 3) will get from {101 1010, 101 0010, 101 1000, 101 0000}
		=> Only differ only first 4 LSB bits (the prefix is the same)

    Consider that ith bit of mask is 0: In this case no subset can differ from mask in the ith bit 
    as it would mean that the numbers will have a 1 at ith bit where mask has a 0 which would mean 
    that it is not a subset of mask. Thus the numbers in this set can now only differ in the first
    i-1 bits.  
        => S(mask,i) = S(mask, i-1).

    Consider that ith bit of mask is 1: Now the numbers belonging to S(mask, i) can be divided into two non intersecting sets. 
        + One containing numbers with i-th bit as 1 and differing from "mask" in the first i - 1  LSB bits.
        + Second containing numbers with i-th bit as 0 and differing from "mask | (1 << i)" in first i - 1 LSB bits.
        => S(mask, i) = S(mask, i - 1) ∪ S(mask | (1 << i), i - 1).
*/

//iterative version
for(int mask = 0; mask < (1<<N); ++mask){
	dp[mask][-1] = A[mask];	//handle base case separately (leaf states)
	for(int i = 0;i < N; ++i){
		if(mask & (1<<i))
			dp[mask][i] = dp[mask][i-1] + dp[mask^(1<<i)][i-1];
		else
			dp[mask][i] = dp[mask][i-1];
	}
	F[mask] = dp[mask][N-1];
}


//memory optimized, super easy to code.
for (int i = 0; i < (1<<N); ++i) // when i = -1 (only -1 LSB bit (0 bits) differ => F[i] = A[i])
	F[i] = A[i];
for (int i = 0; i < N; ++i) for (int mask = 0; mask < (1<<N); ++mask) {
	if(mask & (1<<i))
		F[mask] += F[mask^(1<<i)];
}

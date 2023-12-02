/*
    This template solve problem:
    https://leetcode.com/problems/frequency-of-the-most-frequent-element
*/

#include <bits/stdc++.h>
using namespace std;

int maxFrequency(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end());
    int l = 0, r = 0;   // Initilize l = 0, r = 0
    long long sum = 0;  // Initialize sum of range [l,r] (but not yet [l,r]), calculate sum [l, r] each loop
    int res = 1;
    
    // Each loop:
    // Start loop => Add r to range
    // Then check if current range is valid => If not valid remove l until valid
    // End of loop => We always have valid window (get Result from each window)
    // Increase r for next checking
    while (r < nums.size()) {
        sum += nums[r]; // Add r to range

        while (l < r && sum + k < (r - l + 1)*nums[r]) {
            sum -= nums[l++];
        }

        res = max(res, r - l + 1);
        r++;
    }
    return res;
}
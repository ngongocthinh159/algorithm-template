/*
    Example template for: https://leetcode.com/problems/merge-intervals/
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        // With interval problem: Always sort the interval based on starting time
        sort(intervals.begin(), intervals.end(), [](const vector<int>& i1, const vector<int>& i2) {
            if (i1[0] < i2[0]) return true;
            return false;
        });

        vector<vector<int>> res;

        // Always have variable to track to previous interval
        int curStart = intervals[0][0];
        int curEnd = intervals[0][1];

        // Start traverse each interval (from 1)
        // Compare each interval with previous interval (that why we set intialize interval is index 0 and traverse from 1)
        // If the comparison satisfied some conditions (overlap, non-overlap,..) 
        // => Update the prev interval variables accordingly
        for (int i = 1; i < intervals.size(); i++) {
            int startTime = intervals[i][0];
            int endTime = intervals[i][1];

            // Overlap -> update the max end point
            if (startTime <= curEnd) {
                curEnd = max(curEnd, endTime);

            // Not overlap -> push the last inverval the res
            // Start new interval from the current interval
            } else {
                res.push_back({curStart, curEnd});
                curStart = startTime;
                curEnd = endTime;
            }
        }
        res.push_back({curStart, curEnd});
        return res;
    }
}
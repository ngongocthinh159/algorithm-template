#include <bits/stdc++.h>
using namespace std;

/* Main()  function */
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

// Monotonic stack non-decreasing order (equal value can be on the stack)
// For finding next/previous greater element
void MonotonicStack(vector<int>& nums) {
    stack<int> s; // Increasing stack => Finding next/previous greater element
    vector<int> firstSmallerLeft(nums.size()); // First index has smaller value in the left
    vector<int> firstSmallerRight(nums.size()); // First index has smaller value in the right
 
    for (int i = 0; i < nums.size(); i++) {
        // While current < top => pop top (because we maintain increasing stack)
        // Top element is popped out from the stack => First smaller on the right of top is the current element
        while (s.size() > 0 && nums[i] < nums[s.top()]) {
            firstSmallerRight[s.top()] = i; // Set first smaller on the right of top is the current index
            s.pop();
        }

        // Handle the pushed element (current element)
        // An element is pushed onto the stack 
        // => The element just below it, is the first smaller on the left of the element
        // And if the stack is current empty => The current element do not have the left smaller
        if (s.size() > 0) {
            if (nums[i] == nums[s.top()]) { // If cur num = top => first smaller of cur = first smaller of top
                firstSmallerLeft[i] = firstSmallerLeft[s.top()];
            } else {
                firstSmallerLeft[i] = s.top(); // cur num != top => first smaller of cur = top
            }
        } else {
            firstSmallerLeft[i] = -1; // do not have left smaller
        }

        s.push(i); // Push cur onto the stack
    }

    // All the elements still on the stack do not have right smaller
    while (s.size() > 0) {
        firstSmallerRight[s.top()] = nums.size();
        s.pop();
    }
}

/* Main() Ends Here */
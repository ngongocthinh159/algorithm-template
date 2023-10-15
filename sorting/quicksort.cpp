/*
  Solution for: 
*/

#include <bits/stdc++.h>
using namespace std;

// Quick sort random pivot procedure:
// We have an array: 0, 2, 1, 4, 3,  outRane
//                  low                high
// NOTE: high always out range

// IDEA: choose a randomized pivot, for each loop try to get the pivot the right position
// such as all the value in the left side of pivot smaller than pivot, and also the right side...

// We start sort the array in [low, high) (not include high)
// 1. Get RANDOM: choose a random pivot: index between [low, high)
// Then swap the the value of pivot with the value at index low (swap pivot to first value)

// 2. PARTITIONING: Initilize 2 vars: i = low, j = high
// We will try to swap value between range [low+1, high-1] (because low is pivot, high is out of range)
// Increase i while value at i <= pivot (we try to find number > pivot to swap to right side)
// Decrease j while value at j > pivot (we try to find number <= pivot to swap to left side)
// if after increase/decrease i/j, we still see that i < j:
// => We can swap value of i, j (because we sure that value at i will be right side of value at j)
// Repeat swapping i, j until j < i
// After done swapping between i and j until j < i:
// - Now we know the fact that all the value from [j+1,high) or [i, high) must always > pivot (due to we let j traverse only when j > pivot , or j <= pivot we swap to get j > pivot)
// - We also know the fact that all the value from [low+1,i-1] or [low+1,j] must always <= pivot (due to we let i traverse only when i <= pivot, or i > pivot we swap to get i <= pivot)
// So the last position of j always <= pivot, then we can swap pivot with this position:
// Last step: swap value of pivot and j
// Return the index of the pivot (which is j after swapping)

// Repeat Partitioning in range [low, pivot) and [pivot+1, high)

// Time complexity: 
// Best case: O(nlogn), each level traverse O(n) and we have log2(n) level (n/2^k = 1 => k = log2(n))
// Worst case: array already sorted => unbalance tree, with n level, each level O(n) => O(n^2)

class QuickSort_IndexImplementation {
private:
    int quick_sort_random(vector<int>& nums, int low, int high) {
        // Get random pivot index
        int min = 0;
        int max = high - low - 1;
        int random = rand()%(max + 1 - min) + min;
        int pivot = low + random;

        // Swap value of low index and pivot index
        // => Pivot go to index 0
        swap(nums[low], nums[pivot]);

        // Start partition
        return partition(nums, low, high);
    }

    int partition(vector<int>& nums, int low, int high) {
        int i = low, j = high;
        while (i < j) {
            do {
                i++;
            } while (i < high && nums[i] <= nums[low]);

            do {
                j--;
            } while (j >= low && nums[j] > nums[low]);

            // Swap i-j
            if (i < j) {
                swap(nums[i], nums[j]);
            }
        }

        // Swap pivot-j
        swap(nums[low], nums[j]);

        return j;   // J now as the pivot index (after swap)
    }
public:
    void quick_sort(vector<int>& nums, int low, int high) {
        if (low < high) {
            int pivotIndex = this->quick_sort_random(nums, low, high);
            quick_sort(nums, low, pivotIndex);
            quick_sort(nums, pivotIndex + 1, high);
        }
    }
};

class QuickSort_IteratorImplementation {
private:
    vector<int>::iterator quick_sort_random(vector<int>::iterator low, vector<int>::iterator high) {
        // Get random pivot index
        int min = 0;
        int max = high - low - 1;
        int random = rand()%(max + 1 - min) + min;
        vector<int>::iterator pivotIter = low + random;

        // Swap value of 0 index and pivot index
        // => Pivot go to index 0
        int tmp = *low;
        *low = *pivotIter;
        *pivotIter = tmp;

        // Start partition
        return partition(low, high);
    }

    vector<int>::iterator partition(vector<int>::iterator low, vector<int>::iterator high) {
        auto i = low, j = high;
        while (i < j) {
            do {
                i++;
            } while (i < high && *i <= *low);

            do {
                j--;
            } while (j >= low && *j > *low);

            // Swap i-j
            if (i < j) {
                int tmp = *i;
                *i = *j;
                *j = tmp;
            }
        }

        // Swap pivot-j
        int tmp = *j;
        *j = *low;
        *low = tmp;

        return j;   // J now as the pivot index (after swap)
    }
public:
    void quick_sort(vector<int>::iterator low, vector<int>::iterator high) {
        if (high - low > 0) {
            auto pivotIter = this->quick_sort_random(low, high);
            quick_sort(low, pivotIter);
            quick_sort(pivotIter + 1, high);
        }
    }
};

int main() {
    vector<int> nums = {0, 2, 1, 4, 3};
    QuickSort_IndexImplementation sortObject;
    sortObject.quick_sort(nums, 0, nums.size());
    cout << "Sort with index implementation: ";
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i] << " ";
    }
    cout << "\n";

    QuickSort_IteratorImplementation sortObject2;
    sortObject2.quick_sort(nums.begin(), nums.end());
    cout << "Sort with iterator implementation: ";
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i] << " ";
    }

    return 0;
}








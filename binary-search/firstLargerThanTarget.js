const nums = [0, 1, 1, 2, 4, 5];

/**
 *
 * @param {*} nums
 * @param {*} target
 * @returns return the first index that has number[index] > target.
 * If there are no numbers > target return -1
 */
var firstLargerThanTarget = (nums, target) => {
  let l = 0;
  let r = nums.length - 1;

  while (l <= r) {
    const m = Math.floor(l + (r - l) / 2);

    // With this comparison, l is always in the valid partition => Need to return index of l after all
    if (nums[m] <= target) {
      l = m + 1; // l is always in the partition that have numbers > target
    } else {
      r = m - 1;
    }
  }

  // If there is no number > target ==> l is out of bound index (last index + 1)
  // => Check for l is out of bound otherwise return l
  return l === nums.length ? -1 : l;
};

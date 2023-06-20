const nums = [0, 1, 1, 2, 4, 5];

/**
 *
 * @param {*} nums
 * @param {*} target
 * @returns return the last index that has number[index] < target.
 * If there are no numbers < target return -1
 */
var lastSmallerThanTarget = (nums, target) => {
  let l = 0;
  let r = nums.length - 1;

  while (l <= r) {
    const m = Math.floor(l + (r - l) / 2);

    // With this comparison, r is always in the valid partition => Need to return index of r after all
    if (nums[m] >= target) {
      r = m - 1; // r is always in the partition that have numbers < target
    } else {
      l = m + 1;
    }
  }

  // If there is no number < target ==> r is out of bound index (r = -1)
  // => Check for r is out of bound otherwise return r
  return r === -1 ? -1 : r;
};

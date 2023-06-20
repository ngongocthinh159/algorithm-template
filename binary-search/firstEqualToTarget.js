const nums = [0, 1, 1, 2, 4, 5];

/**
 *
 * @param {*} nums
 * @param {*} target
 * @returns return the first index that number[index] is equal to target
 * If there are no numbers equal to target return -1
 */
var firstIndexEqualToTarget = (nums, target) => {
  let l = 0;
  let r = nums.length - 1;

  while (l <= r) {
    const m = Math.floor(l + (r - l) / 2);

    // With this comparison, l is always in the valid partition => Need to return index of l after all
    if (nums[m] < target) {
      l = m + 1; // l is always in the partition that have numbers >= target
    } else {
      r = m - 1;
    }
  }

  // If there are no numbers equal to target => return -1
  // If there is at least one number >= target => Check that number at l is greater than or equal to target
  // If the number at l > target => return -1 (we need to find the first number equal here)
  // If the number at l === target => return l
  return l === nums.length ? -1 : nums[l] === target ? l : -1;
};

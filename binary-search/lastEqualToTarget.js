const nums = [0, 1, 1, 2, 4, 5];

/**
 * 
 * @param {*} nums 
 * @param {*} target 
 * @returns return the last index that number of that index is equal to target
 * If there are no numbers equal to target return -1
 */
var lastIndexEqualToTarget = (nums, target) => {
  let l = 0;
  let r = nums.length - 1;

  while (l <= r) {
    const m = Math.floor(l + (r - l) / 2);

    // With this comparison, r is always in the valid partition => Need to return index of r after all
    if (nums[m] > target) {
      r = m - 1; // r is always in the partition that have numbers <= target
    } else {
      l = m + 1;
    }
  }

  // If there are no numbers equal to target => return -1
  // If there is at least one number >= target => Check that number at r is greater than or equal to target
  // If the number at r < target => return -1 (we need to find the last number equal here)
  // If the number at r === target => return r
  return r === -1 ? -1 : nums[r] === target ? r : -1;
};

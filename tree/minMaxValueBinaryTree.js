/**
 * 
 * @param {*} root 
 * @returns Min/Max value of a binary tree
 */

var minValue = (root) => {
  if (!root) return Number.POSITIVE_INFINITY;
  return Math.min(minValue(root.left), minValue(root.right), root.val);
};

var maxValue = (root) => {
  if (!root) return Number.NEGATIVE_INFINITY;
  return Math.max(maxValue(root.left), maxValue(root.right), root.val);
};

/**
 *
 * @param {*} arr
 * @param {*} length // Limited length, if length > arr.length ==> choose arr.length
 * @param {*} res
 * @param {*} curPermutation
 * @param {*} addedIndices // Check for added indices
 * @param {*} addedPermutations // Check for duplicated permutations
 * @returns Generate all permutations with limited length and all the permutations will not be duplicated
 */
const generatePermutationsLimitLength = (
  arr,
  length,
  res,
  curPermutation,
  addedIndices,
  addedPermutations
) => {
  if (addedIndices.size === Math.min(length, arr.length)) {
    const newArray = [...curPermutation];
    const newArrayString = newArray.join(',');
    if (!addedPermutations.has(newArrayString)) {
      addedPermutations.add(newArrayString);
      res.push(newArray);
    }
    return;
  }

  for (let i = 0; i < arr.length; i++) {
    if (!addedIndices.has(i)) {
      addedIndices.add(i);
      curPermutation.push(arr[i]);
      generatePermutationsLimitLength(
        arr,
        length,
        res,
        curPermutation,
        addedIndices,
        addedPermutations
      );

      // Back track
      addedIndices.delete(i);
      curPermutation.pop();
    }
  }
};

var arr = [0, 1, 2, 3, 3];
var res = [];

generatePermutationsLimitLength(arr, 3, res, [], new Set(), new Set()); // arr, limited permutation length, result array
console.log(res);

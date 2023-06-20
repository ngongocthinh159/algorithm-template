var generateSubset = (arr, res, i, curSub) => {
  if (i === arr.length) {
    res.push([...curSub]);
    return;
  }

  curSub.push(arr[i]);
  generateSubset(arr, res, i + 1, curSub);
  curSub.pop();

  generateSubset(arr, res, i + 1, curSub);
};

var arr = [0, 1, 2, 3, 3, 4];
var res = [];

generateSubset(arr, res, 0, []); // arr, result array, current index
console.log(res);

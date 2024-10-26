class Node {
  constructor(val) {
    this.val = val;
    this.left = null;
    this.right = null;
  }
}

const root = new Node(5);
root.left = new Node(2);
root.left.left = new Node(1);
root.left.right = new Node(3);
root.right = new Node(8);
root.right.left = new Node(6);
root.right.right = new Node(9);

// Tree
//       5
//   2       8
// 1   3   6   9

var postorderRecursive = (root) => {
  if (!root) return;

  postorderRecursive(root.left);
  postorderRecursive(root.right);
  console.log(root.val);
};

var postorderIterative = function (root) {
  if (!root) return [];

  // Post-order traversal left first then right = Reverse(Pre-order traversal right first then left)
  const stack = [root];
  const res = [];

  while (stack.length > 0) {
    const cur = stack.pop();
    res.unshift(cur.val); // Reverse the pop out values

    // Right push to the stack after left => Go right first (Last in first out)
    if (cur.left) stack.push(cur.left);
    if (cur.right) stack.push(cur.right);
  }

  console.log(res);

  return res;
};

postorderRecursive(root);
console.log();
postorderIterative(root);

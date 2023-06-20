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

var inorderRecursive = (root) => {
  if (!root) return;

  inorder(root.left);
  console.log(root.val);
  inorder(root.right);
};

var inorderIterative = (root) => {
  if (!root) return [];
  const stack = [root];

  while (stack.length > 0) {
    let cur = stack[stack.length - 1];

    while (cur.left) {
      stack.push(cur.left);
      cur = cur.left;
    }

    let returnFromLeft = null;
    do {
      returnFromLeft = stack.pop();
      console.log(returnFromLeft.val);
    } while (stack.length > 0 && !returnFromLeft.right);

    if (returnFromLeft.right) stack.push(returnFromLeft.right);
  }
};

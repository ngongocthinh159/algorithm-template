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

var preorderRecursive = (root) => {
  if (!root) return;

  console.log(root.val);
  preorderRecursive(root.left);
  preorderRecursive(root.right);
};

var preorderIterative = (root) => {
  const stack = [root];

  while (stack.length > 0) {
    const cur = stack.pop();
    console.log(cur.val);

    // Left push to the stack after right => Go left first (Last in first out)
    if (cur.right) {
      stack.push(cur.right);
    }

    if (cur.left) {
      stack.push(cur.left);
    }
  }
};

preorderRecursive(root);
console.log();
preorderIterative(root);

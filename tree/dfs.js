class Node {
  constructor(val) {
    this.val = val;
    this.left = null;
    this.right = null;
  }
}

const root = new Node('a');
root.left = new Node('b');
root.right = new Node('c');
root.left.left = new Node('d');
root.left.right = new Node('e');
root.right.right = new Node('f');

const DFSIterative = (root) => {
  if (root === null) return [];

  const stack = [];
  stack.push(root);
  const res = [];

  while (stack.length > 0) {
    const cur = stack.pop();
    res.push(cur.val);

    if (cur.right) stack.push(cur.right);
    if (cur.left) stack.push(cur.left);
  }

  return res;
};

const DFSRecursive = (root) => {
  if (!root) return [];

  const leftValues = DFSRecursive(root.left);
  const rightValues = DFSRecursive(root.right);

  return [root.val, ...leftValues, ...rightValues];
};

console.log(DFSIterative(root));
console.log(DFSRecursive(root));

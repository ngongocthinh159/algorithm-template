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

const BFSIterative = (root) => {
  if (root === null) return [];

  const queue = [];
  queue.push(root);
  const res = [];

  while (queue.length > 0) {
    const cur = queue.pop();
    res.push(cur.val);
    
    if (cur.left) queue.unshift(cur.left);
    if (cur.right) queue.unshift(cur.right);
  }

  return res;
};

console.log(BFSIterative(root));

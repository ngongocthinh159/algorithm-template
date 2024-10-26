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

  inorderRecursive(root.left);
  console.log(root.val);
  inorderRecursive(root.right);
};

var inorderIterative = (root) => {
  // Dont need Set to check for visited node but very tricky to implement
  if (!root) return [];

  const stack = [];
  let p = root;
  const res = [];

  while (stack.length > 0 || p) {
    if (p) {
      stack.push(p);
      p = p.left;
    } else {
      const cur = stack.pop();
      res.push(cur.val);
      p = cur.right;
    }
  }

  console.log(res);

  return res;
};

// More intuitive, but need Set to check for visited node, easy to implement
var inorderIterativeWithSet = (root) => {
  if (!root) return [];

  const stack = [root];
  const set = new Set();
  const res = [];

  while (stack.length > 0) {
    const cur = stack[stack.length - 1];

    if (cur.left && !set.has(cur.left)) {
      stack.push(cur.left);
    } else {
      const popout = stack.pop();
      set.add(popout);
      res.push(popout.val);

      if (popout.right && !set.has(popout.right)) {
        stack.push(popout.right);
      }
    }
  }

  console.log(res);

  return res;
};

inorderRecursive(root);
console.log();
inorderIterativeWithSet(root);

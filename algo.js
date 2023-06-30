var colorSolver = () => {
  let cases = parseInt(readline());

  while (cases--) {
    const length = parseInt(readline());
    const arr = readline()
      .split(' ')
      .map((s) => parseInt(s));

    // arr.sort((a, b) => {
    //   return a - b;
    // });

    print(arr);
  }
};

colorSolver();

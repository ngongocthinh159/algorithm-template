#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> nums = {1, 2, 3, 3, 3, 4, 5, 6};
    auto pair = equal_range(nums.begin(), nums.end(), -1);
    cout << pair.first - nums.begin() << " " << pair.second - nums.begin() << "\n";
    if (pair.first != pair.second) {
        cout << "not found\n";
    } else {

    }
    return 0;
}

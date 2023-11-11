#include <bits/stdc++.h>
using namespace std;

string decimalToBinaryConversion(int n);
string decimalToBinaryConversion_Devision(int n);

int main() {
    cout << decimalToBinaryConversion(1441) << "\n";
    cout << decimalToBinaryConversion_Devision(1441) << "\n";

    return 0;
}

// Bit manipulation (checking LSB => Then remove LSB => Repeat)
string decimalToBinaryConversion(int n) {
    // Check the LSB (least significant bit) of N is 1 or 0
    string res = "";
    while (n != 0) {
        if (n & 1) { // If LSB is 1 => This return true
            res+='1';
        } else {
            res+='0';
        }
        n>>=1;
    }
    // Reverse res
    string tmp = "";
    for (int i = res.size() - 1; i >= 0; i--) {
        tmp += res[i];
    }
    return tmp;
}

// Read more why always take remainder after division:
// https://math.stackexchange.com/questions/2463620/why-does-the-method-of-converting-from-decimal-binary-by-taking-remainder-work
string decimalToBinaryConversion_Devision(int n) {
    vector<int> v(32, 0);
    int i = 0;
    while (n != 0) {
        v[i] = n%2;
        n /= 2;
        i++;
    }
    string res = "";
    for (int j = i - 1; j >= 0; j--) {
        res += to_string(v[j]);
    }
    return res;
}
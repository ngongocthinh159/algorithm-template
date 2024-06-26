/*
    Leetcode
    239. Sliding Window Maximum
    You are given an array of integers nums, there is a sliding window of 
    size k which is moving from the very left of the array to the very right.
    You can only see the k numbers in the window. Each time the sliding window 
    moves right by one position. Return the max sliding window.

    Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
    Output: [3,3,5,5,6,7]

    Explanation: 
    Window position                Max
    ---------------               -----
    [1  3  -1] -3  5  3  6  7      3
    1 [3  -1  -3] 5  3  6  7       3
    1  3 [-1  -3  5] 3  6  7       5
    1  3  -1 [-3  5  3] 6  7       5
    1  3  -1  -3 [5  3  6] 7       6
    1  3  -1  -3  5 [3  6  7]      7
*/

#include <bits/stdc++.h>
using namespace std;

/* clang-format off */

/* TYPES  */
#define ll long long
#define pii pair<int, int>
#define pll pair<long long, long long>
#define vi vector<int>
#define vll vector<long long>
#define mii map<int, int>
#define si set<int>
#define sc set<char>

/* FUNCTIONS */
#define f(i,s,e) for(long long int i=(s);i<(e);i++)
#define cf(i,s,e) for(long long int i=(s);i<=(e);i++)
#define rf(i,e,s) for(long long int i=(e);i>=(s);i--)
#define fe(a, b) for (auto&(a) : (b))
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define eb emplace_back

/* PRINTS */
template <class T>
void print_v(vector<T> &v) { cout << "{"; for (auto x : v) cout << x << ","; cout << "\b}"; }

/* UTILS */
#define MOD 1000000007
#define PI 3.1415926535897932384626433832795
double EPS = 1e-9;
int INF = 1000000005;
long long INFF = 1000000000000000005LL;
ll directions[8][2] = {{-1,0},{0,1},{1,0},{0,-1},{-1,1},{1,1},{1,-1},{-1,-1}}; // UP-RIGHT-BOTTOM-DOWN || NORTH-EAST-SOUTH-WEST, From dir[4] Right of Up then clock wise
#define read(type) readInt<type>()
ll min(ll a,int b) { if (a<b) return a; return b; }
ll min(int a,ll b) { if (a<b) return a; return b; }
ll max(ll a,int b) { if (a>b) return a; return b; }
ll max(int a,ll b) { if (a>b) return a; return b; }
ll gcd(ll a,ll b) { if (b==0) return a; return gcd(b, a%b); } // Greatest common divisor (Uoc chung lon nhat): O(log(min(a,b))
ll lcm(ll a,ll b) { return a/gcd(a,b)*b; } // Lowest common mutiple (Boi chung nho nhat): O(log(min(a,b))
string to_upper(string a) { for (int i=0;i<(int)a.size();++i) if (a[i]>='a' && a[i]<='z') a[i]-='a'-'A'; return a; }
string to_lower(string a) { for (int i=0;i<(int)a.size();++i) if (a[i]>='A' && a[i]<='Z') a[i]+='a'-'A'; return a; }
string int_to_string(ll a) { char x[100]; sprintf(x, "%lld", a); string s = x; return s; }
ll string_to_int(string a) { char x[100]; ll res; strcpy(x, a.c_str()); sscanf(x, "%lld", &res); return res; }
bool prime(ll a) { if (a==1) return 0; for (int i=2;i<=round(sqrt(a));++i) if (a%i==0) return 0; return 1; }
ll mod(ll x) { return (((x%MOD) + MOD) % MOD); }
ll addMod(ll a, ll b) { return mod(mod(a) + mod(b)); }
ll subMod(ll a, ll b) { return mod(mod(a) - mod(b)); }
ll mulMod(ll a, ll b) { return mod(mod(a) * mod(b)); }
ll powMod(ll x, ll n) { if (n == 0) return 1%MOD; ll u = powMod(mod(x),n/2); u = (u*u)%MOD; if (n%2 == 1) u = (u*(mod(x)))%MOD; return u; } // (x^n)%MOD
ll powMod(ll x, ll n, ll mod) { if (n == 0) return 1%mod; ll tmp = powMod(x,n/2,mod); if (n%2==0) return (tmp*tmp)%mod; else return (((tmp*tmp)%mod)*(x%mod))%mod; } // Custom mod number
ll inverseMod(ll a) { if (gcd(a, MOD) != 1) return -1; return powMod(mod(a), MOD-2); } // Return -1 if ((1/a)%MOD) not exist (a and MOD not coprime)
ll divMod(ll a, ll b) { ll tmp = inverseMod(b); if (tmp == -1) return -1; return (((mod(a))*inverseMod(mod(b)))%MOD); } // Return -1 if ((1/b)%MOD) not exist (b and MOD not coprime)
void yes() { cout<<"YES\n"; }
void no() { cout<<"NO\n"; }
void OPEN() {
    freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
}

/*  All Required define Pre-Processors and typedef Constants */
typedef long int int32;
typedef unsigned long int uint32;
typedef long long int int64;
typedef unsigned long long int  uint64;

/* clang-format on */
vector<int> maxSlidingWindow(vector<int>& nums, int k);

/* Main()  function */
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    vector<int> nums = {1,3,-1,-3,5,3,6,7};
    int k = 3;
    
    vector<int> ans = maxSlidingWindow(nums, k);
    fe(val,ans)
        cout << val << " ";
}

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<pair<int,int>> q; // Maximum monotonic queue
    vector<int> ans;

    for (int i = 0; i < nums.size(); i++) {
        // - Remove unused left most elements if possible cuz if we take the largest element 
        // in the current window, the largest value is at least will be equal to the current 
        // visited element (nums[i] is the current visited element)
        // - So if any left most element <= nums[i], then it will be removed from the queue
        while (q.size() > 0 && q.back().first <= nums[i]) q.pop_back(); 
        q.push_back({nums[i], i});

        // Remove largest element no longer in the window range by comparing index of the
        // largest front pushed element of the queue and the out of bound range index
        while (q.size() > 0 && q.front().second <= i-k) q.pop_front();
        if (i >= k - 1) ans.push_back(q.front().first);
    }

    return ans;
}

/* Main() Ends Here */
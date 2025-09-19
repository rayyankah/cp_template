///cf - two arrays
void solve()
{
  compute_factorials();
  int n,m;
  cin >>n>>m;
  cout<<ncr(n+2*m-1, 2*m)<<nl;
}







////gcd extreme
#include <bits/stdc++.h>
using namespace std;
 
#define vll long long
#define vi int
#define ll long long
#define fast                          \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)
 
const int MOD = 1000000007;
const int N = 1e6 + 10;
 
vi factorial[N], inv[N], phi[N], f[N];
long long sum[N];
int divisors[N][100]; 
int divisor_sizes[N]; 
int binExp(int a, int b, int mod) {
    int res = 1;
    a %= mod;
    while (b > 0) {
        if (b & 1) {
            res = (res * a) % mod;
        }
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}
 
void precompute_phi() {
    for (int i = 1; i < N; i++) {
        phi[i] = i;
    }
    for (int i = 2; i < N; i++) {
        if (phi[i] == i) {  // i is a prime number
            for (int j = i; j < N; j += i) {
                phi[j] -= phi[j] / i;
            }
        }
    }
}
 
void precompute_divisors() {
    for (int i = 1; i < N; i++) {
        for (int j = i; j < N; j += i) {
            divisors[j][divisor_sizes[j]++] = i;  // Add divisors using manual index
        }
    }
}
 
void compute_factorials() {
    factorial[0] = 1;
    for (int i = 1; i < N; i++) {
        factorial[i] = (factorial[i - 1] * i) % MOD;
    }
    inv[N - 1] = binExp(factorial[N - 1], MOD - 2, MOD);
    for (int i = N - 2; i >= 0; i--) {
        inv[i] = (inv[i + 1] * (i + 1)) % MOD;
    }
}
 
void compute_sum() {
    for (int i = 1; i < N; i++) {
        f[i] = phi[i];
    }
 
    for (int i = 2; i < N; i++) {
        for (int j = i * 2; j < N; j += i) {
            f[j] += (i * phi[j / i]); 
        }
    }
 
    sum[1] = 0;
    for (int i = 2; i < N; i++) {
        sum[i] = sum[i - 1] + f[i];
    }
}
 
void solve() {
    int n;
    cin >> n;
    if (n == 0) exit(0);
    cout << sum[n] << '\n';
}
 
int main() {
    fast;
    precompute_phi();
    precompute_divisors();
    compute_sum();
 
    int t = 20000;
    while (t--) {
        solve();
    }
 
    return 0;
}



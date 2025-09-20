///cf - two arrays
void solve()
{
  compute_factorials();
  int n,m;
  cin >>n>>m;
  cout<<ncr(n+2*m-1, 2*m)<<nl;
}


//subgrid-1
void solve() {
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }
    for (int l = 0; l < k; l++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (grid[i-1][j-1] != 'A' + l) {
                    dp_up[i][j] = 0;
                    dp_left[i][j] = 0;
                    dp_square[i][j] = 0;
                    // cout << 0 << " ";
                    continue;
                }
                dp_up[i][j] = dp_up[i-1][j]+1;
                dp_left[i][j] = dp_left[i][j-1]+1;

                
                dp_square[i][j] = min({
                    dp_up[i-1][j],
                    dp_left[i][j-1],
                    dp_square[i-1][j-1]
                }) + 1;

                res[l] += dp_square[i][j];
                // cout << dp_left[i][j] << " ";
            }
            // cout << endl;
        }
    }
    for (int i = 0; i < k; i++) {
        cout << res[i] << " ";
    }
    cout << endl;

}

//subgrid -2
 
const int N = 3005;
string grid[N];
int dp[N][N];
long long result[30];
void solve() {
    
    int n,m;
    cin >> n >> m;
    for(int i=0;i<n;i++) 
        cin >> grid[i];
    for(int i=1;i<=n;i++) {
        vector<pair<int,int>> monotone;
        long long rects = 0;
        for(int j=1;j<=n;j++){
            dp[i][j] = 1;
            if( i > 1 and grid[i-1][j-1] == grid[i-2][j-1] ) 
                dp[i][j] += dp[i-1][j];
            
            if ( j > 1 and grid[i-1][j-1] != grid[i-1][j-2] ) {
                monotone.clear();
                rects = 0;
            }
            int cnt = 1;
            while(monotone.size() and monotone.back().first >= dp[i][j] ){
                cnt += monotone.back().second;
                rects -= 1LL * monotone.back().first * monotone.back().second;
                monotone.pop_back();
            }
            monotone.push_back({dp[i][j],cnt});
            rects += 1LL * dp[i][j] * cnt;
            result[grid[i-1][j-1]-'A'] += rects;
        }
    }
    for(int i=0;i<m;i++) cout<< result[i]<<endl;
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



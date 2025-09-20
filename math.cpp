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
 






//cf- trees
ll dp[40][40];



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, h; cin >> n >> h;

    for (int i = 0; i <= n; ++i) dp[0][i] = 1;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int k = 0; k < i; ++k)
                dp[i][j] += dp[k][j - 1] * dp[i - k - 1][j - 1];
        }
    }
    cout << dp[n][n] - dp[n][h - 1] << endl;
    return 0;
}






//catalan
vi catalan(N);
void compute_catalan()
{
    catalan[0] = 1;
    catalan[1] = 1;
    for(int i=2; i<N; i++){
        for(int j=0; j<i; j++){
            catalan[i] = (catalan[i] + (catalan[j]*catalan[i-j-1])%MOD)%MOD;    
        }
    }
}


//cf-count gcd
signed main(){
        ios_base::sync_with_stdio(false); cin.tie(NULL);
        int tt = 1; cin >> tt;
        while( tt-- ){
                int n,m; cin >> n >> m;
                vector<int> v(n);
                for( auto &z : v ) cin >> z;
                bool anso = 0;
                for( int i = 1 ; i < n ; i++ ) if( v[i-1] % v[i] ) anso = 1;
                if( anso ){
                        cout << 0 << '\n';
                        continue;
                }
                int x = v[0] , ans = 1;
                vector<int> fact;
                for( int i = 2 ; ( i * i ) <= x ; i++ ){
                        if( !( x % i ) ) fact.push_back(i);
                        while( !( x % i ) ) x /= i;
                }
                if( x != 1 ) fact.push_back(x);
                for( int i = 1 ; i < n ; i++ ){
                        x = v[i-1] / v[i];
                        int cnt = 0 , mx = m / v[i];
                        vector<int> pr;
                        for( auto z : fact ) if( !( x % z ) ) pr.push_back(z);
                        for( int mask = 0 ; mask < ( 1 << pr.size() ) ; mask++ ){
                                int mul = 1;
                                for( int i = 0 ; i < pr.size() ; i++ ) if( mask & ( 1 << i ) ) mul *= pr[i];
                                if( __builtin_popcount(mask) & 1 ) cnt -= ( mx / mul );
                                else cnt += ( mx / mul );
                        }
                        ans *= cnt , ans %= mod;
                }
                cout << ans << '\n';
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

//pankac
{
int a[1001],tar[1001],i,j,k,n,t,temp,temp1;
a[1]=tar[1]=1;
for(i=1; i<=1000; i++)
{
for(j=2; j<=i; j++)
{
temp=tar[j];
tar[j]=tar[j-1]+temp1;
if(tar[j]>=1000000007)
tar[j]=tar[j]%1000000007;
temp1=temp;
}
temp1=tar[1];
a[i]=tar[1]=tar[i];
}
scanf(“%d”,&t);
while(t)
{
scanf(“%d”,&n);
printf(“%d\n”,a[n]);
t–;
}









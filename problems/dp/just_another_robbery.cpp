//just another robbery
const int N = 1e6 + 10;
vi factorial(N);
vi inv(N);
void compute_factorials()
{
    factorial[0] = 1;
    for (int i = 1; i < N; i++)
    {
        factorial[i] = (factorial[i - 1] * i) % MOD;
    }
    inv[N - 1] = binExp(factorial[N - 1], MOD - 2);
    for (int i = N - 2; i >= 0; i--)
    {
        inv[i] = (inv[i + 1] * (i + 1)) % MOD;
    }
}
int ncr(int n, int r)
{
    if (r > n || r < 0)
        return 0;
 
    return (binMul(factorial[n], binMul(inv[r], inv[n - r], MOD), MOD));
}

//================ Code starts here ================
void solve(int t)
{
    double p;
    int n;
    cin >> p>>n;
    vi values(n);
    vector<double>prob(n);
    rep(i,0,n){
        cin >> values[i]>>prob[i];
    }
    double dp[n+1][10001];
    double ans =0;

    memset(dp,0,sizeof(dp));
    dp[n][0]=1.0;
    rep(i,1,10001)dp[n][i]=0.0;
    repb(i,n-1,0){
        rep(j,0,10001){
            dp[i][j]=dp[i+1][j];
            if(j-values[i]>=0){
                dp[i][j]=max(dp[i][j], dp[i+1][j-values[i]]*(1-prob[i]));//probablity of not getting caught
            }

        }

    }
    repb(i,10000,0){
        if((1-dp[0][i])<=p){
            ans =i;
            break;
        }
    }
    cout<<"Case "<<t<<": ";
    cout<<ans<<nl;
}

signed main()
{
    fast;

    int t = 1;
    cin >> t;
    for(int i=1; i<=t; i++){
        solve(i);
    }
}

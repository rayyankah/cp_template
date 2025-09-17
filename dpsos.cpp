//cf -->compatible numbers

const int BITS = 22;                
const int MAXMASK = (1 << BITS);    

vi a;
vi freq(MAXMASK);
vi dp(MAXMASK);

//================ Code starts here ================
void solve()
{
    int n; 
    cin >> n;
    a.resize(n);
    rep(i,0,n) cin >> a[i];

    // reset
    fill(freq.begin(), freq.end(), 0);
    fill(dp.begin(), dp.end(), -1);
    rep(i,0,n) freq[a[i]]++;

    rep(mask,0,MAXMASK){
        if(freq[mask] > 0) dp[mask] = mask;
    }
    rep(bit,0,BITS){
        rep(mask,0,MAXMASK){
            if(mask & (1<<bit)){
                dp[mask] = max(dp[mask], dp[mask ^ (1<<bit)]);
            }
        }
    }
    rep(i,0,n){
        int complement = ((MAXMASK-1) ^ a[i]);
        cout << dp[complement] << " ";
    }
    cout << nl;
}

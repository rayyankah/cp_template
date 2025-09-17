//cakes code
const int maxN = 100005;
int a[maxN], seg[4*maxN];
int volume[maxN];
int unique_sorted[maxN];
int m;
void build(int idx, int l, int r){
    if(l==r){
        seg[idx]=a[l];
        return;
    }
    int mid = l+(r-l)/2;
    build(2*idx+1, l,mid);//left child
    build(2*idx+2, mid+1,r);//right child
    seg[idx]=max(seg[2*idx+1],seg[2*idx+2]);
    return;
}
int query(int idx, int l, int r, int ql, int qr){
    if(l>=ql && r<=qr){
        return seg[idx];//completely inside
    }
    if(l>qr || r<ql){
        return INT_MIN;//completely outside
    }
    int mid = l+(r-l)/2;
    int left = query(2*idx+1, l,mid, ql, qr);
    int right = query(2*idx+2, mid+1,r, ql, qr);
    return max(left,right);
}
void pointUpdate(int idx,int l, int r, int node, int val){
    if(l==r){
        seg[idx]=max(seg[idx],val);
        return;
    }
    int mid = l+(r-l)/2;
    if(node<=mid && node>=l){
        pointUpdate(2*idx+1, l, mid, node, val);
    }
    else{
        pointUpdate(2*idx+2, mid+1, r, node, val);
    }
    seg[idx]=(max(seg[2*idx+1], seg[2*idx+2]));
    return;
} 
int getRank(int val){
    return (int)(lower_bound(unique_sorted+1, unique_sorted+m+1, val)-unique_sorted);
}
//================ Code starts here ================
void solve()
{
  int n;
  cin >>n;
  rep(i,0,n){
    int r,h;
      cin >>r>>h;
    volume[i]=r*r*h;
  }
  set<int>s;
  rep(i,0,n){
    s.insert(volume[i]);
  }
  m=0;
  for(auto &x:s){
    unique_sorted[++m]=x;
  }
  build(0,1,m);
  vi dp;
  rep(i,0,n){
    int vol = volume[i];
    int rank = getRank(vol);
    int best =0;
    if(rank>1){
        best = query(0,1,m,1,rank-1);//finding dp[j]such that j<i  and v[j]<v[i]
 
    }
    int curr = best+vol;
    dp.pb(curr);
    pointUpdate(0,1,m,rank,curr);//updating dp[i] to segment tree
 
  }
  long double PI = acos(-1);//cos(Pi)=-1;
  int mx = INT_MIN;
  rep(i,0,dp.size()){
    mx = max(mx, dp[i]);
  }
  cout<<precise(10)<<(long double)mx*PI<<nl;
}
 








//footman -horseman cf ceasar
int n1, n2, k1, k2;
ll dp[101][101][11][11];
ll mod = 100000000;
ll go(int t1, int t2, int c1, int c2) {
    if (t1+t2 == n1+n2) return 1;
    if (~dp[t1][t2][c1][c2]) return dp[t1][t2][c1][c2];
    ll ch1 = 0, ch2 = 0;
    if (t1+1 <= n1 && c1+1 <= k1) ch1 = go(t1+1, t2, c1+1, 0);
    if (t2+1 <= n2 && c2+1 <= k2) ch2 = go(t1, t2+1, 0, c2+1);
    return dp[t1][t2][c1][c2] = (ch1+ch2)%mod;
}
void testcases(){
    cin >> n1 >> n2 >> k1 >> k2;
    memset(dp, -1, sizeof(dp));
    cout << go(0, 0, 0, 0) << endl;
}




//ada and subsequece
void solve()
{
      int N, M;
    cin >> N >> M;
    vector<int> cost(26);
    for (int i = 0; i < 26; i++)
        cin >> cost[i];
    string A, B;
    cin >> A >> B;
    vector<vector<ll>> dp(N + 1, vector<ll>(M + 1, 0));
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            if (A[i - 1] == B[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + cost[A[i - 1] - 'a'];
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    // Base cases: dp[0][0] = 0, and dp[i][0] = 0 for all i, dp[0][j] = 0 for all j
    cout << dp[N][M] << nl;
}






//maximum product
void solve()
{
    ll a, b;
    cin >> a >> b;
    string s = to_string(b);
    int len = s.length();
    ll max_prod = 0;
    ll ans = b;
    auto calc_prod = [](string t) -> ll {
        ll p = 1;
        for (char c : t) {
            p *= (c - '0');
        }
        return p;
    };
    auto has_zero = [](ll n) -> bool {
        string str = to_string(n);
        for (char c : str) {
            if (c == '0') return true;
        }
        return false;
    };
    if (!has_zero(b)) {
        max_prod = calc_prod(s);
        ans = b;
    }
    // Special case for leading 1
    if (len > 1 && s[0] == '1') {
        string t(len - 1, '9');
        ll num = stoll(t);
        if (num >= a) {
            ll prod = calc_prod(t);
            if (prod > max_prod) {
                max_prod = prod;
                ans = num;
            }
        }
    }
    // General cases
    for (int i = 0; i < len; i++) {
        if (s[i] > '1') {
            string t = s;
            t[i]--;
            for (int j = i + 1; j < len; j++) {
                t[j] = '9';
            }
            ll num = stoll(t);
            if (num >= a && num <= b) {
                ll prod = calc_prod(t);
                if (prod > max_prod) {
                    max_prod = prod;
                    ans = num;
                }
            }
        }
    }
    cout << ans << nl;
}





//coins exhibition cf


#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#define int   long long
#define ll long long
#define down cout<<'\n';
#define debug cout<<" cucuucucuuu",down
#define modwwe  int t;cin>>t; while(t--)
#define bit(i,j) (i>>j&1)
#define sobit(a) __builtin_popcountll(a)
#define task2 "top1apio"
#define task "test"
#define fin(x) freopen(x".inp","r",stdin)
#define fou(x) freopen(x".out","w",stdout)
#define pb push_back
#define mask(k) (1ll<<k)
#define checktime   cerr << (double)clock() / CLOCKS_PER_SEC * 1000  << " ms";
using namespace std;
#define getchar_unlocked getchar
mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());
using i128 = __int128;
int rand(int l, int r)
{
    return uniform_int_distribution<int>(l, r)(rd);
}
void phongbeo();
const ll inf = 1e17;
const int mod2 = 1e9+7;
//const ll base=67;
int  n, m, s1, s2, s4, s3, sf, k, s5, s6, s7, s8, s9, mx2, res, dem2 = 0, dem = 0, s33, dem3, dem4, mid, l2,
                                                                r2, center;
int  i, s10, s12, k1, k2, k3, s11, lim, w, l, r, dem5, dem6, dem7, dem9, now, root, q, en;
int el = 19;
main()
{
    ///top1apio
    if (fopen(task2".inp", "r"))
    {
        fin(task2);
        fou(task2);
    }

    ///top1apio
    if (fopen(task".inp", "r"))
    {
        fin(task);
        fou(task);
    }

    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
    //   cin>>s1;
    //ll t;cin >> t;while (t--)
    phongbeo(),down
}
struct ib
{
    int a,b;
};
vector<ib> v[800003];
vector<int> vc;
int dp[2][800003];
int gg[2];
int last[2];
int a[800003],b[800003],c[800003],d[800003];
int add(int x,int y)
{
    if(x+y>=mod2)x-=mod2;
    if(x+y<0)x+=mod2;
    return x+y;
}
int ipow(int x, int p)
{
    int  ret = 1, piv = x;
    while(p)
    {
        if(p&1) ret *= piv;
        piv *= piv;
        ret %= mod2;
        piv %= mod2;
        p >>= 1;
    }
    return ret;
}
void phongbeo()
{
    cin>>k>>n>>m;
    vc.pb(0);
    for(int i=1; i<=n; i++)
        cin>>a[i]>>b[i],vc.pb(a[i]),vc.pb(b[i]);
    for(int i=1; i<=m; i++)
        cin>>c[i]>>d[i],vc.pb(c[i]),vc.pb(d[i]);
    vc.pb(k);
    sort(vc.begin(),vc.end());
    vc.erase(unique(vc.begin(),vc.end()),vc.end());
    for(int i=1; i<=n; i++)
    {
        a[i]=lower_bound(vc.begin(),vc.end(),a[i])-vc.begin()+1;
        b[i]=lower_bound(vc.begin(),vc.end(),b[i])-vc.begin()+1;
        v[b[i]].pb({0,a[i]});
    }
    for(int i=1; i<=m; i++)
    {
        c[i]=lower_bound(vc.begin(),vc.end(),c[i])-vc.begin()+1;
        d[i]=lower_bound(vc.begin(),vc.end(),d[i])-vc.begin()+1;
        v[d[i]].pb({1,c[i]});
    }
    dp[0][1]=ipow(2,vc[1]-vc[0]-1);
    dp[1][1]=ipow(2,vc[1]-vc[0]-1);
    gg[0]=dp[0][1];
    gg[1]=dp[1][1];
    for(int i=2; i<=vc.size(); i++)
    {
        for(auto x:v[i]){
            if(x.b-1>last[x.a])
            {
                for(int j=last[x.a]+1; j<x.b; j++)
                gg[x.a]=add(gg[x.a],-dp[x.a][j]);
                last[x.a]=x.b-1;
            }
        }
        if(i!=vc.size())
        {
            for(int j=0; j<2; j++)
            {
                dp[1-j][i]=add(dp[1-j][i],1ll*ipow(2,vc[i]-vc[i-1]-1)*gg[j]%mod2);
                dp[j][i]=add(dp[j][i],1ll*gg[j]*(ipow(2,vc[i]-vc[i-1]-1)-1)%mod2);
            }
            for(int j=0; j<2; j++)
                gg[j]=add(gg[j],dp[j][i]);
        }
    }
    cout<<add(gg[0],gg[1]);
}

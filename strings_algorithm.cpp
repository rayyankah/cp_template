//polynomial rolling hash
ll getHash(string &key){
    ll value = 0;
    ll p = 31;
    ll p_power =1;
    for(char c : key){
        value = (value + (c - 'a' + 1) * p_power)%MOD;
        p_power = (p_power * p)%MOD;
    }
    return value;
}


//substring hash
int pref[N];
int inv_pref[N];
void compute_pref_hash(string &s, int p = 31){
    ll p_power = 1;
    inv_pref[0] = 1;
    pref[0] = (s[0] - 'a' + 1);
    for(int i=1; i<s.size(); i++){
        p_power= (binMul(p_power, p, MOD));
        pref[i] = (pref[i-1] +( s[i]-'a'+1)*p_power)%MOD;
        inv_pref[i] = binExp(p_power, MOD-2);
    }

}
ll substringHash(int l, int r, int p = 31){
    if(l==0) return pref[r];
    ll hash_value = (pref[r]-pref[l-1]);
    hash_value%=MOD;
    if(hash_value<0) hash_value+=MOD;
    hash_value = binMul(hash_value, inv_pref[l], MOD);
    return hash_value;

}


//ispallindrome
void solve()
{
   
  string s;
  //pallindrom or not using hashing
    cin >> s;
    int n = s.size();
    compute_pref_hash(s);
    int hsh1 = substringHash(0, n-1);

    string t = s;
    reverse(all(t));
    compute_pref_hash(t);
    int hsh2 = substringHash(0, n-1);
    if(hsh1==hsh2) cout<<"YES\n";
    else cout<<"NO\n";

 

  }


//lsstring
void solve()
{
    //longest commong substring
    string s1, s2;
    cin >>s1>>s2;
    int n = s1.size();
    int m = s2.size();
    int sz = min(n, m);
    vi pref1(n), pref2(m);
    compute_pref_hash(s1,pref1);
    compute_pref_hash(s2,pref2);
    int low = 0, high = sz;
    int ans =0;
    while(low<=high){
        int mid = low+(high-low)/2;
        vi hashes;
        for(int i=0; i+mid-1<n;i++){
            hashes.pb(substringHash(i,i+mid-1, pref1));

        }
        sort(all(hashes));
        bool found = false;
        for(int i=0; i+mid-1<m; i++){
            int h = substringHash(i, i+mid-1, pref2);
            int lo = 0, hi = hashes.size()-1;
            while(lo<=hi){
                int md = lo+(hi-lo)/2;
                if(hashes[md]==h){
                    found = true;
                    break;
                }
                else if(hashes[md]<h) lo = md+1;
                else hi = md-1;
            }
            if(found) break;

        }
        if(found){
            ans = mid; 
            low = mid+1;
        }
        else high = mid-1;

    }
    cout<<ans<<nl;
   
}






void solve()
{
    //least length period
    string s;
    cin >>s;
    int n = s.size();
    int ans = n;
    vi pref(n);
    compute_pref_hash(s,pref);
    
     for(int len = 1; len <=n/2; len++){
        if(n%len)continue;
        ll prefix_hash = substringHash(0,len-1,pref);
        ll suffix_hash = substringHash(n-len,n-1,pref);
        if(prefix_hash==suffix_hash){
            ans = len;
            break;
        }
     }
        cout<<ans<<nl;
}







//tree hash
void solve()
{
   //seeing if two trees identical using hashing
   int n,m;
   cin >>n>>m;
   vvi adj1(n+1);
   vvi adj2(n+1);

   rep(i,0,n-1){
    int u,v;
    cin >>u>>v;
    adj1[u].pb(v);
    adj1[v].pb(u);

   }
    rep(i,0,m-1){
     int u,v;
     cin >>u>>v;
     adj2[u].pb(v);
     adj2[v].pb(u);
    }
    vi hash1(n+1,0);
    vi hash2(m+1,0);
    vi subtree_size1(n+1,0);
    vi level1(n+1,0);
    vi subtree_size2(n+1,0);
    vi level2(n+1,0);
    function<void(int,int, vi&, vi&, vvi&, vi&)>dfs1  = [&](int node, int par, vi &level, vi& subtree_size, vvi &adj, vi &hash){
        subtree_size[node]=1;
        if(par!=-1) level[node]=level[par]+1;

        for(auto &child: adj[node]){
            if(child==par)continue;
            dfs1(child,node,level,subtree_size,adj,hash);
            subtree_size[node]+=subtree_size[child];
            //hash[node] = (hash[all_children] + d* b^p// d->subtree size, b->prime, p->level)
            hash[node]+=hash[child];
        }
        hash[node]+=(subtree_size[node]*binExp(31,level[node]))%MOD;
        hash[node]%=MOD;

    };
    level1[1]=0;
    level2[1]=0;
    dfs1(1,-1,level1,subtree_size1,adj1,hash1);
    dfs1(1,-1,level2,subtree_size2,adj2,hash2);
    if(hash1[1]==hash2[1])cout<<"YES"<<nl;
    else cout<<"NO"<<nl;
}










//longest pallindromic substring

void solve() {

    string s;
    int x;
    cin >>x;
    cin>>s;
    int n = (int)s.size();

    const long long M1 = 1000000007LL, M2 = 1000000009LL;
    const long long B1 = 911382323LL, B2 = 972663749LL;

    vector<long long> pow1(n + 1, 1), pow2(n + 1, 1);
    for (int i = 1; i <= n; ++i) {
        pow1[i] = (pow1[i - 1] * B1) % M1;
        pow2[i] = (pow2[i - 1] * B2) % M2;
    }

    auto buildPref = [&](const string& a) {
        vector<long long> p1(n + 1, 0), p2(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            p1[i + 1] = (p1[i] * B1 + (a[i] - 'a' + 1)) % M1;
            p2[i + 1] = (p2[i] * B2 + (a[i] - 'a' + 1)) % M2;
        }
        return pair<vector<long long>, vector<long long>>(move(p1), move(p2));
    };

    string t = s;
    reverse(t.begin(), t.end());

    auto pres = buildPref(s);
    auto rpres = buildPref(t);
    const vector<long long>& pre1 = pres.first;
    const vector<long long>& pre2 = pres.second;
    const vector<long long>& rpre1 = rpres.first;
    const vector<long long>& rpre2 = rpres.second;

    auto getHash = [&](const vector<long long>& p, const vector<long long>& pw, int l, int r, long long mod) {
        long long res = (p[r + 1] - (p[l] * pw[r - l + 1]) % mod);
        if (res < 0) res += mod;
        return res;
    };

    auto isPal = [&](int l, int r) {
        if (l > r) return true;
        int rl = n - 1 - r, rr = n - 1 - l;
        long long a1 = getHash(pre1, pow1, l, r, M1);
        long long a2 = getHash(pre2, pow2, l, r, M2);
        long long b1 = getHash(rpre1, pow1, rl, rr, M1);
        long long b2 = getHash(rpre2, pow2, rl, rr, M2);
        return a1 == b1 && a2 == b2;
    };

    auto oddRadius = [&](int c) {
        int lo = 0, hi = min(c, n - 1 - c), ans = 0;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (isPal(c - mid, c + mid)) { ans = mid; lo = mid + 1; }
            else hi = mid - 1;
        }
        return ans;
    };

    auto evenRadius = [&](int i) {
        int lo = 0, hi = min(i + 1, n - 1 - i), ans = 0;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            int l = i - mid + 1, r = i + mid;
            if (l <= r && isPal(l, r)) { ans = mid; lo = mid + 1; }
            else hi = mid - 1;
        }
        return ans;
    };

    int best = 0;
    for (int i = 0; i < n; ++i) {
        int o = oddRadius(i);
        int e = (i + 1 < n) ? evenRadius(i) : 0;
        best = max(best, max(2 * o + 1, 2 * e));
    }

    cout << best << "\n";
}




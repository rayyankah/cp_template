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

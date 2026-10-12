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

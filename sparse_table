void solve()
{
  int n;
  cin >>n;
    vi a(n);
    read(a);
    int m=  log2(n);
    vvi sparse_table(n,vi(m+1));
    for(int i=0; i<n; i++){
        sparse_table[i][0]=a[i];
    }
    rep(j,1,m+1){
        //0-->2^0
        //1-->2^1
        for(int i=0; i+(1<<j)-1<n; i++){
            sparse_table[i][j]=min(sparse_table[i][j-1],sparse_table[i+(1<<j-1)][j-1]);
        }
    }
    debug(sparse_table);
    int q;
    cin >>q;
    while(q--){
        int l,r;
        cin >>l>>r;
        //overlap - no problem
        int sz = r-l+1;
        int to_check = log2(sz);
        //closest power of 2
        cout<<min(sparse_table[l][to_check], sparse_table[r-(1<<to_check)+1][to_check])<<nl;
    }
}

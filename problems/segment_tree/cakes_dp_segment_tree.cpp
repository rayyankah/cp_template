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

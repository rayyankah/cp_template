#include <bits/stdc++.h>
using namespace std;
#define int long long
#define nl '\n'
#define rep(i,a,b) for(int i=a;i<b;i++)

//================ Segment Tree ================
// change ONLY: node, identity(), makeLeaf(), merge(), applyNode()
const int maxN = 200005;
int a[maxN];

struct node{
    int sum, mx;
};
node seg[4*maxN];
int lazy[4*maxN];//pending update for children (seg[idx] itself is already updated)

//doesn't affect merge -> returned when completely outside
node identity(){
    return {0, LLONG_MIN};
}

//leaf node from a single value
node makeLeaf(int val){
    return {val, val};
}

//combine left and right child
node merge(node L, node R){
    node res;
    res.sum = L.sum+R.sum;
    res.mx = max(L.mx, R.mx);
    return res;
}

//apply "add val to every element of [l,r]" on this node
void applyNode(int idx, int l, int r, int val){
    seg[idx].sum += (r-l+1)*val;
    seg[idx].mx += val;
    lazy[idx] += val;//children still need it
}

//push pending laziness to children
void push(int idx, int l, int r){
    if(lazy[idx]!=0 && l!=r){
        int mid = l+(r-l)/2;
        applyNode(2*idx+1, l, mid, lazy[idx]);
        applyNode(2*idx+2, mid+1, r, lazy[idx]);
    }
    lazy[idx]=0;
}

void build(int idx, int l, int r){
    lazy[idx]=0;
    if(l==r){
        seg[idx]=makeLeaf(a[l]);
        return;
    }
    int mid = l+(r-l)/2;
    build(2*idx+1, l, mid);//left child
    build(2*idx+2, mid+1, r);//right child
    seg[idx]=merge(seg[2*idx+1], seg[2*idx+2]);
}

//set a[pos] = val
void pointUpdate(int idx, int l, int r, int pos, int val){
    if(l==r){
        seg[idx]=makeLeaf(val);
        return;
    }
    push(idx, l, r);
    int mid = l+(r-l)/2;
    if(pos<=mid) pointUpdate(2*idx+1, l, mid, pos, val);
    else pointUpdate(2*idx+2, mid+1, r, pos, val);
    seg[idx]=merge(seg[2*idx+1], seg[2*idx+2]);
}

//add val to [ql,qr]
void rangeUpdate(int idx, int l, int r, int ql, int qr, int val){
    if(l>qr || r<ql) return;//completely outside
    if(l>=ql && r<=qr){
        applyNode(idx, l, r, val);//completely inside
        return;
    }
    push(idx, l, r);//overlapping
    int mid = l+(r-l)/2;
    rangeUpdate(2*idx+1, l, mid, ql, qr, val);
    rangeUpdate(2*idx+2, mid+1, r, ql, qr, val);
    seg[idx]=merge(seg[2*idx+1], seg[2*idx+2]);
}

node query(int idx, int l, int r, int ql, int qr){
    if(l>qr || r<ql) return identity();//completely outside
    if(l>=ql && r<=qr) return seg[idx];//completely inside
    push(idx, l, r);
    int mid = l+(r-l)/2;
    return merge(query(2*idx+1, l, mid, ql, qr),
                 query(2*idx+2, mid+1, r, ql, qr));
}

//================ Code starts here ================
void solve()
{
  int n;
  cin >>n;
  rep(i,0,n){
    cin>>a[i];
  }
  build(0,0,n-1);
  int q;
  cin >>q;
  while(q--){
    int type;
    cin >>type;
    if(type==1){//add val to [l,r]
        int l,r,val;
        cin >>l>>r>>val;
        l--,r--;//0 based
        rangeUpdate(0,0,n-1,l,r,val);
    }
    else if(type==2){//set a[pos]=val
        int pos,val;
        cin >>pos>>val;
        pos--;
        pointUpdate(0,0,n-1,pos,val);
    }
    else{//sum and max of [l,r]
        int l,r;
        cin >>l>>r;
        l--,r--;
        node ans = query(0,0,n-1,l,r);
        cout<<ans.sum<<" "<<ans.mx<<nl;
    }
  }
}

signed main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
  return 0;
}

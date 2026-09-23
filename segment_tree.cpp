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





//segment tree implementation
const int maxN = 100005;
int a[maxN], seg[4*maxN];
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
//================ Code starts here ================
void solve()
{
  int n;
  cin >>n;
  rep(i,0,n){
    cin>>a[i];
  }
  build(0,0,n-1);//build(index, l_range, r_range)
  int q;
  cin >>q;
  while(q--){
    int l,r;
    cin >>l>>r;
    l--,r--;
    cout<<query(0,0,n-1,l,r)<<nl;//search in whole space
  }
}


//cf - sereja and brackets..

const int maxN = 1000005;
char a[maxN];
struct node{
    int leftRem, rightRem, matches;
};
node seg[4*maxN];
void build(int idx, int l, int r){
    if(l==r){
        if(a[l]=='('){
            seg[idx].leftRem =1;
            seg[idx].rightRem =0;
            seg[idx].matches =0;//leaf node, only one char
        }   
        else{
            seg[idx].rightRem=1;
            seg[idx].leftRem =0;
            seg[idx].matches =0;
        }
        return;
    }
    int mid = l+(r-l)/2;
    build(2*idx+1, l, mid);
    build(2*idx+2, mid+1, r);
    int ans = min(seg[2*idx+1].leftRem,seg[2*idx+2].rightRem);
    seg[idx].matches =ans+seg[2*idx+1].matches+seg[2*idx+2].matches;//children er match o store korte hbe
    seg[idx].leftRem = (seg[2*idx+1].leftRem-ans)+seg[2*idx+2].leftRem;
    seg[idx].rightRem = (seg[2*idx+2].rightRem-ans)+seg[2*idx+1].rightRem;
    return;
}
node query(int idx, int l, int r, int ql, int qr){
    if(l>=ql && r<=qr){
        return seg[idx];
    }
    if(l>qr || r<ql){
         node dummy;
        dummy.leftRem=0;
        dummy.rightRem=0;
        dummy.matches=0;
        return dummy;
    }
    int mid = l+(r-l)/2;
    node lef = query(2*idx+1,l,mid, ql, qr);
    node rig = query(2*idx+2, mid+1, r, ql, qr);
    node ans;
    ans.matches = min(lef.leftRem,rig.rightRem);
    ans.leftRem = (lef.leftRem-ans.matches)+rig.leftRem;
    ans.rightRem = (rig.rightRem-ans.matches)+lef.rightRem;
    ans.matches +=lef.matches+rig.matches;//children er match o store korte hbe
 
    return ans;
}
//================ Code starts here ================
void solve()
{
  string s;
  cin>>s;
  rep(i,0,s.size()){
    a[i]=s[i];
  }
  build(0,0,s.size()-1);
  int q;
  cin >>q;
  while(q--){
    int l,r;
    cin >>l>>r;
    l--;
    r--;
    node ans =query(0,0,s.size()-1,l,r);
    cout<<2*(ans.matches)<<nl;
  }
}







//single point update
//single update
void pointUpdate(int idx,int l, int r, int node, int val){
    if(l==r){
        seg[idx]+=val;
        return;
    }
    int mid = l+(r-l)/2;
    if(node<=mid && node>=l){
        pointUpdate(2*idx+1, l, mid, node, val);
    }
    else{
        pointUpdate(2*idx+2, mid+1, r, node, val);
    }
    seg[idx]=seg[2*idx+1]+seg[2*idx+2];
    return;
} 





//range update (lazy propagation)
int lazy[4*maxN];
void rangeUpdate(int idx, int l, int r, int ql, int qr, int val_to_add){
    if(lazy[idx]!=0){
        seg[idx]+=(r-l+1)*lazy[idx];//update the node
        //propagate the laziness to children
        if(l!=r){
            lazy[2*idx+1]+=lazy[idx];
            lazy[2*idx+2]+=lazy[idx];
        }
        lazy[idx]=0;
    }
    if(l>qr || r<ql || l>r){
        //completely outside
        return;
    }
    if(l>=ql && r<=qr){
        //completely inside
        seg[idx]+=(r-l+1)*val_to_add;
        if(l!=r){
            //if not leaf node
            //propagate the laziness to children
            lazy[2*idx+1]+=val_to_add;
            //we can't do lazy[left]=lazy[idx] since we have already made lazy[idx]=0 above
            lazy[2*idx+2]+=val_to_add;
        }
        return;
    }
    //overlapping case
    int mid = l+(r-l)/2;
    rangeUpdate(2*idx+1, l, mid, ql, qr, val_to_add);
    rangeUpdate(2*idx+2, mid+1, r, ql, qr, val_to_add);
    seg[idx]=seg[2*idx+1]+seg[2*idx+2];//not seg[idx]+= cz children already updated
    return;
}
//query and lazy update
int querySumLazy(int ind, int l, int r, int ql, int qr){
    if(lazy[ind]!=0){
        seg[ind]+=(r-l+1)*lazy[ind];//updating the node
        //propagate the laziness to children
        if(l!=r){
            lazy[2*ind+1]+=lazy[ind];
            lazy[2*ind+2]+=lazy[ind];
        }
        lazy[ind]=0;
    }
    if(l>qr || r<ql || l>r){
        //completely outside
        return 0;//won't contribute to sum
    }
    if(l>=ql && r<=qr){
        //completely inside
        return seg[ind];
        //we don't need to go further down since we have already updated the node above
    }
    int mid = l+(r-l)/2;
    return querySumLazy(2*ind+1, l, mid, ql, qr)+querySumLazy(2*ind+2, mid+1, r, ql, qr);
}


//================ Code starts here ================
void solve()
{
  int n;
  cin >>n;
  rep(i,0,n){
    cin>>a[i];
  }
  build(0,0,n-1);//build(index, l_range, r_range)
  int q;
  cin >>q;
  while(q--){
    int type;
    cin >>type;
    if(type==1){
        int l, r, val;
        cin >>l>>r>>val;
        l--;
        r--;//0 based
        rangeUpdate(0,0,n-1,l,r,val);
    }
    //type 2
    else{
        int l,r;
        cin >>l>>r;
        l--;
        r--;//0 based
        cout<<querySumLazy(0,0,n-1,l,r)<<nl;
    }
  }

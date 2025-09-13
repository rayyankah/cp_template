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

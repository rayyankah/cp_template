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

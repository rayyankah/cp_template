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

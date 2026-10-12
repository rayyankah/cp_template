//spoj-dquery
struct query{
    int l,r,i;
};
query Q[200001];
int ans[200001];
int freq[1000001];
int ar[30001];
int cnt =0;
bool cmp(query a, query b){
    if(a.l/BLK!=b.l/BLK){
        return a.l/BLK<b.l/BLK;//starting pos kon block tar regard e sort
    }
    return a.r/BLK <b.r/BLK;
}
void add(int pos){
    freq[ar[pos]]++;
    if(freq[ar[pos]]==1)cnt++;
}
void remove(int pos){
    freq[ar[pos]]--;
    if(freq[ar[pos]]==0)cnt--;
}

//================ Code starts here ================
void solve()
{
  int n;
  cin >>n;
  rep(i,0,n){
    cin>>ar[i];
  }

  int q;
  cin>>q;
  rep(i,0,q){
    cin>>Q[i].l>>Q[i].r;
    Q[i].l--;
    Q[i].r--;//0 based
    Q[i].i= i;
  }
  sort(Q,Q+q,cmp);
  int ML=0, MR=-1;//because initially no range
  rep(i,0,q){
    int L =Q[i].l;
    int R = Q[i].r;
    //since we sorted the queries, we will move from previous range to current range
    //we will only move ML forward and MR forward or backward
    //removing
    while(ML<L){
        ML++;
        remove(ML-1);
    }
    while(MR>R){
        remove(MR);
        MR--;
    }
    //adding
    //ML will never be greater than L
    while(MR<R){
        MR++;
        add(MR);
    }
    while(ML>L){
        ML--;
        add(ML);
    }//why do we need this while loop even though L is sorted in increasing order?
    //because within same block, L can be in any order
    ans[Q[i].i]=cnt;
  }

  rep(i,0,q){
    cout<<ans[i]<<nl;
  }

}

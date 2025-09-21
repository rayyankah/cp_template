//hackerearth-->power beaker
void solve()
{
  int n,m;
  cin >>n>>m;
  m-=1;
  if(m==0){
    cout<<2<<nl;
    return;
  }
  if(n&1){
    cout<<1<<nl;
    return;
  }
  cout<<2<<nl;
}




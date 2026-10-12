///cf - two arrays
void solve()
{
  compute_factorials();
  int n,m;
  cin >>n>>m;
  cout<<ncr(n+2*m-1, 2*m)<<nl;
}

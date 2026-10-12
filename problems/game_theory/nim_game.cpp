//nim's game
void solve()
{
  int n;
  cin >>n;
  int ans =0;
  while(n--){
    int x;
    cin >>x;
    ans^=x;
  }
  if(ans==0){
    cout<<"Second"<<nl;
  }
  else{
    cout<<"First"<<nl;
  }
}

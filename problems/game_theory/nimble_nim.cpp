//Nimble NIM
void solve()
{
  int n;
  cin>>n;
  int ans =0;
  for(int i=0;i<n; i++){
    int x;
    cin >>x;
    if(x&1){
        ans^=i;
    }
    
  }
  if(ans){
    cout<<"First"<<nl;
  }
  else{
    cout<<"Second"<<nl;
  }
}

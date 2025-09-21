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



//chess
int dp[16][16];
int func(int x, int y){
    
    if(x<1 || y<1 || x>15|| y>15){
        return 1;//amr jonno winning cz je dise she invalid move dise
    }
    if(dp[x][y]!=-1){
        return dp[x][y];
    }
    int ans = func(x-1,y-2)+func(x-2,y-1)+func(x-2, y+1)+func(x+1, y-2);
    if(ans<=3){
        return dp[x][y]=1;
    }
    return dp[x][y]=0;
}
//================ Code starts here ================
void solve()
{
  int x,y;

    cin >>x>>y;
    if(func(x,y)){
        cout<<"First"<<nl;
    }
    else{
        cout<<"Second"<<nl;
    }


}




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



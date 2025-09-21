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

//misere nim
void solve()
{
    int n;
    cin >> n;
    int ans = 0;
    int numone = 0;
    int tempn = n;
    while (n--)
    {
        int x;
        cin >> x;
        if (x == 1)
            numone++;
        ans ^= x;
    }
    if (numone == tempn)
    {
        if (tempn & 1)
        {
            cout << "Second" << nl;
        }
        else
        {
            cout << "First" << nl;
        }
        return;
    }
    if (ans == 0)
    {
        cout << "Second" << nl;
    }
    else
    {
      
            cout << "First" << nl;
        
    }
}




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




//string grundy
#include <bits/stdc++.h>
using namespace std;

// ----------------- simple globals (user style) -----------------
string S;
int n;
vector<vector<int>> occ; // occ[i] = list of end indices (inclusive) of dictionary words that start at i

// Grundy table: g[l][r] for substring S[l..r)  (0 <= l < r <= n)
vector<vector<int>> g;

// helper to compute mex of small set
int mex_of(const vector<char> &seen) {
    int k = (int)seen.size();
    for (int i = 0; i < k; ++i) if (!seen[i]) return i;
    return k;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // --- read input (adjust if needed) ---
    if (!(cin >> S)) return 0;
    int m;
    cin >> m;
    vector<string> dict(m);
    for (int i = 0; i < m; ++i) cin >> dict[i];

    n = (int)S.size();
    occ.assign(n, vector<int>());

    // --- find all occurrences of each dictionary word in S ---
    // naive scanning; if you want faster, build Aho-Corasick
    for (int i = 0; i < n; ++i) {
        for (int w = 0; w < m; ++w) {
            const string &pat = dict[w];
            int L = (int)pat.size();
            if (i + L <= n && S.compare(i, L, pat) == 0) {
                occ[i].push_back(i + L - 1); // store inclusive end index
            }
        }
    }

    // --- DP initialization ---
    g.assign(n + 1, vector<int>(n + 1, 0));
    // we will compute g[l][r] for lengths from 1..n (r = l+len)

    // define an upper bound on possible Grundy values to size the 'seen' array.
    // In practice Grundy values are small, but we pick something like 512.
    const int MAXG = 512;

    for (int len = 1; len <= n; ++len) {
        for (int l = 0; l + len <= n; ++l) {
            int r = l + len;
            // collect reachable Grundy values
            // we use a boolean array to mark seen XOR values
            vector<char> seen(MAXG, 0);

            // iterate over all possible starts p inside [l, r-1]
            // and for each occurrence end e in occ[p] with e < r, add g[l][p] ^ g[e+1][r]
            for (int p = l; p < r; ++p) {
                if (occ[p].empty()) continue;
                int leftG = g[l][p];
                for (int e : occ[p]) {
                    if (e < r) {
                        int rightG = g[e + 1][r];
                        int val = leftG ^ rightG;
                        if (val < MAXG) seen[val] = 1;
                    }
                }
            }
            g[l][r] = mex_of(seen);
        }
    }

    int Gwhole = g[0][n];
    if (Gwhole == 0) {
        cout << "SECOND\n"; // second player wins
        return 0;
    } else {
        cout << "FIRST\n"; // first player wins
    }

    // If you also want to print a winning move (one possible deletion that makes XOR 0):
    // find any deletion S[i..j] that is a dictionary word and for which g[0][i] ^ g[j+1][n] == 0
    bool found = false;
    for (int i = 0; i < n && !found; ++i) {
        for (int e : occ[i]) {
            int newGr = g[0][i] ^ g[e + 1][n];
            if (newGr == 0) {
                cout << "Winning move: delete substring [" << i << "," << e << "] : '"
                     << S.substr(i, e - i + 1) << "'\n";
                found = true;
                break;
            }
        }
    }
    if (!found) {
        // theoretically shouldn't happen if Gwhole != 0
    }
    return 0;
}

//ispallindrome
void solve()
{
   
  string s;
  //pallindrom or not using hashing
    cin >> s;
    int n = s.size();
    compute_pref_hash(s);
    int hsh1 = substringHash(0, n-1);

    string t = s;
    reverse(all(t));
    compute_pref_hash(t);
    int hsh2 = substringHash(0, n-1);
    if(hsh1==hsh2) cout<<"YES\n";
    else cout<<"NO\n";

 

  }

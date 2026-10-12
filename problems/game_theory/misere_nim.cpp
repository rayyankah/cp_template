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

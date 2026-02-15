// xor range

//cf -> https://codeforces.com/contest/2036/problem/F

int xor_upto(int x)
{
    if (x < 0)
        return 0;
    if ((x & 3LL) == 0)
        return x;
    if ((x & 3LL) == 1)
        return 1;
    if ((x & 3LL) == 2)
        return x + 1;
    return 0;
}

int xor_range(int l, int r)
{
    return xor_upto(r) ^ xor_upto(l - 1);
}
//================ Code starts here ================
void solve()
{
    int l, r, ii, k;
    cin >> l >> r >> ii >> k;
    // vi bits(62, 0);
    // rep(i, 0, 62)
    // {
    //     int lmost = 0;
    //     repb(j, 61, i + 1)
    //     {
    //         if (l & (1LL << j))
    //         {
    //             lmost |= (1LL << j);
    //         }
    //     }
    //     lmost |= (1LL << i);
    //     if(lmost<l){
    //         lmost = l;
    //         lmost |= (1LL << i);
    //     }
    //     if (lmost > r)
    //     {
    //         break;
    //     }
    //     int diff = r - lmost + 1LL;
    //     int vag = (diff / (1LL << (i + 1)));
    //     int mot = (vag * (1LL << i));
    //     // debug(diff, mot, vag, i, (1LL << i), diff % (1LL << (i + 1)));
    //     mot += (min<ll>((1LL << i), (diff % (1LL << (i + 1)))));
    //     // debug(mot);
    //     if (mot & 1)
    //     {
    //         bits[i] = 1;
    //     }
    // }
    // int num = 0;
    // rep(i, 0, 62)
    // {
    //     if (bits[i])
    //     {
    //         num |= (1LL << i);
    //     }
    //     // debug(i, bits[i], num);
    // }
    // if(l==15 && r==43)
    // debug(num);

    int num = xor_range(l, r);
    debug(num);
    int temp = k;
    num ^= temp;
    while ((temp < r))
    {
        debug(temp);
        int nowtemp = (temp + (1LL << ii));
        // debug(temp, (temp | (1LL << ii)));
        num ^= nowtemp;
        debug(nowtemp);
        temp = nowtemp;
    }
    cout << num << nl;
}

int floor_div(int a, int b) // b > 0
{
    if (a >= 0)
        return a / b;
    return -(((-a) + b - 1) / b);
}

int ceil_div(int a, int b) // b > 0
{
    if (a >= 0)
        return (a + b - 1) / b;
    return -((-a) / b);
}
/*

We do this in 2 phases:
1) XOR all numbers in [l, r].
2) Remove numbers that are NOT interesting (those with x % (2^i) == k).

Those removable numbers always look like:
    x = k + m * (2^i)

So we find which m values make x stay inside [l, r]:
- first valid m:  ceil((l - k) / 2^i)
- last valid m:   floor((r - k) / 2^i)

If first > last, there is nothing to remove.

Otherwise, removable numbers are:
    k + first*2^i, k + (first+1)*2^i, ..., k + last*2^i

Their XOR can be built fast:
- XOR of m from [first, last], then shift left by i (because of *2^i)
- XOR k once more if count is odd (since k repeats once per term)

Finally:
answer = (XOR of all in [l, r]) XOR (XOR of removable numbers)

Quick example:
l=1, r=3, i=1, k=0
step=2, removable numbers are 2 (since 2 % 2 = 0).
XOR(1..3)=1^2^3=0, remove 2 => 0^2=2, which matches 1^3.
*/

void solve_fast()
{
    int l, r, ii, k;
    cin >> l >> r >> ii >> k;

    int ans = xor_range(l, r); // XOR of all numbers in [l, r]

    int step = (1LL << ii);

    // Numbers to remove: x = k + m*step in [l, r]
    int mL = ceil_div(l - k, step);
    int mR = floor_div(r - k, step);

    if (mL <= mR)
    {
        int cnt = mR - mL + 1;
        int bad = (xor_range(mL, mR) << ii);
        if (cnt & 1)
            bad ^= k;
        ans ^= bad;
    }

    cout << ans << nl;
}

signed main()
{
    fast;
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve_fast();
    }
}

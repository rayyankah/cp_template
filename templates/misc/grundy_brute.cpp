// game theory toolkit
// sprague-grundy: g(state) = mex of g(next states). position is LOST (for the player to move) iff g = 0
// several independent games: xor the grundy values. nim: xor of pile sizes
// unknown game with huge N: brute force g(n) for small n, PRINT the table, then find the pattern
// (period, parity, powers of two, n mod k ...). This is exactly how to attack "N <= 1e16" games.
int mexOf(vi v) { sort(all(v)); int m = 0; for (int x : v) { if (x == m) m++; else if (x > m) break; } return m; }
void grundyTable(int upTo)
{
    vi g(upTo + 1, 0);
    rep(n, 0, upTo + 1)
    {
        vi nxt;
        // ---- write the moves of the game here. example: take 1, 2 or 3 stones ----
        rep(k, 1, 4) if (n - k >= 0) nxt.pb(g[n - k]);
        g[n] = mexOf(nxt);
        cout << n << ": " << g[n] << (g[n] ? "  win" : "  LOSE") << nl;
    }
}
// splitting games (a move cuts a segment into two parts): g(n) = mex over moves of g(left) ^ g(right)
// misere nim (last mover LOSES): if all piles are 1, first wins iff number of piles is even; else same as normal nim
// win/lose without grundy (single game, small state): win[s] = exists move to a losing state

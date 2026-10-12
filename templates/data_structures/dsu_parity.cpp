// dsu with parity: unite(a, b, d) forces side(a) xor side(b) = d, returns false on contradiction
// reset: par[i] = i, rel[i] = 0
int par[N], rel[N]; // rel = side of v relative to its parent (0 same, 1 different)
int find(int v)
{
    if (par[v] == v) return v;
    int r = find(par[v]);
    rel[v] ^= rel[par[v]];
    return par[v] = r;
}
bool unite(int a, int b, int d) // side(a) xor side(b) must be d
{
    int ra = find(a), rb = find(b);
    if (ra == rb) return (rel[a] ^ rel[b]) == d;
    par[ra] = rb, rel[ra] = rel[a] ^ rel[b] ^ d;
    return true;
}

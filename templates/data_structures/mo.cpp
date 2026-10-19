// mo's algorithm: offline range queries in O((n + q) sqrt n) add/remove operations
// fill qs with {l, r, idx} (0-based, inclusive), write add(i) / remove(i) / answer(), call mo(qs, q)
struct Query { int l, r, idx; };
void add(int i);
void removeIdx(int i);
int answer();
vi mo(vector<Query> qs, int q)
{
    int B = 512; // block size ~ n / sqrt(q); 512 is fine for n, q ~ 2e5
    sort(all(qs), [&](const Query &a, const Query &b)
    {
        if (a.l / B != b.l / B) return a.l < b.l;
        return (a.l / B & 1) ? a.r > b.r : a.r < b.r;
    });
    vi res(q);
    int cl = 0, cr = -1;
    for (auto &x : qs)
    {
        while (cr < x.r) add(++cr);
        while (cl > x.l) add(--cl);
        while (cr > x.r) removeIdx(cr--);
        while (cl < x.l) removeIdx(cl++);
        res[x.idx] = answer();
    }
    return res;
}

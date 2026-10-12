// segment tree: range add, global max is seg[0]
// sz = size, seg.assign(4*sz, 0), lz.assign(4*sz, 0), add(0, 0, sz-1, l, r, v)
int sz;
vi seg, lz;
void add(int idx, int l, int r, int ql, int qr, int v)
{
    if (qr < l || r < ql) return;
    if (ql <= l && r <= qr)
    {
        seg[idx] += v, lz[idx] += v;
        return;
    }
    int mid = (l + r) / 2;
    add(2 * idx + 1, l, mid, ql, qr, v);
    add(2 * idx + 2, mid + 1, r, ql, qr, v);
    seg[idx] = max(seg[2 * idx + 1], seg[2 * idx + 2]) + lz[idx];
}

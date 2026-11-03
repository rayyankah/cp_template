// more geometry: convex polygon clipping (half-plane intersection by cuts), minimum enclosing circle,
// area of intersection of two circles, area of a union of axis-parallel rectangles
typedef long double ld;
struct Q { ld x, y; };
ld crossQ(Q o, Q a, Q b) { return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x); }

// keep the part of convex polygon `poly` (ccw) on the LEFT of the directed line a -> b. O(n) per cut.
// half-plane intersection of k half-planes: start from a big box and cut k times, O(k^2) total
vector<Q> cutLeft(const vector<Q> &poly, Q a, Q b, ld eps = 1e-12)
{
    vector<Q> res;
    int k = poly.size();
    rep(i, 0, k)
    {
        Q p = poly[i], q = poly[(i + 1) % k];
        ld cp = crossQ(a, b, p), cq = crossQ(a, b, q);
        if (cp >= -eps) res.pb(p);
        if ((cp > eps && cq < -eps) || (cp < -eps && cq > eps))
        {
            ld t = cp / (cp - cq);
            res.pb({p.x + (q.x - p.x) * t, p.y + (q.y - p.y) * t});
        }
    }
    return res;
}
// kernel of a simple polygon given ccw (points that see the whole polygon); empty = no kernel
vector<Q> kernel(const vector<Q> &p, ld BIG = 1e9)
{
    vector<Q> K = {{-BIG, -BIG}, {BIG, -BIG}, {BIG, BIG}, {-BIG, BIG}};
    int n = p.size();
    rep(i, 0, n) { K = cutLeft(K, p[i], p[(i + 1) % n]); if (K.empty()) break; }
    return K;
}

// minimum enclosing circle (Welzl, expected O(n)); returns {cx, cy, r}
array<ld, 3> mec(vector<Q> p, ld eps = 1e-9)
{
    mt19937 rg(712367);
    shuffle(p.begin(), p.end(), rg);
    auto in = [&](const array<ld, 3> &c, Q q) { ld dx = q.x - c[0], dy = q.y - c[1]; return dx * dx + dy * dy <= c[2] * c[2] + eps; };
    auto two = [](Q a, Q b) { return array<ld, 3>{(a.x + b.x) / 2, (a.y + b.y) / 2, hypotl(a.x - b.x, a.y - b.y) / 2}; };
    auto three = [&](Q a, Q b, Q c)
    {
        ld d = 2 * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
        if (fabsl(d) < 1e-18)               // collinear: the widest pair
        {
            array<ld, 3> r1 = two(a, b), r2 = two(a, c), r3 = two(b, c);
            if (r1[2] >= r2[2] && r1[2] >= r3[2]) return r1;
            return r2[2] >= r3[2] ? r2 : r3;
        }
        ld A = a.x * a.x + a.y * a.y, B = b.x * b.x + b.y * b.y, C = c.x * c.x + c.y * c.y;
        ld ux = (A * (b.y - c.y) + B * (c.y - a.y) + C * (a.y - b.y)) / d;
        ld uy = (A * (c.x - b.x) + B * (a.x - c.x) + C * (b.x - a.x)) / d;
        return array<ld, 3>{ux, uy, hypotl(a.x - ux, a.y - uy)};
    };
    int n = p.size();
    array<ld, 3> c = {p[0].x, p[0].y, 0};
    rep(i, 1, n) if (!in(c, p[i]))
    {
        c = {p[i].x, p[i].y, 0};
        rep(j, 0, i) if (!in(c, p[j]))
        {
            c = two(p[i], p[j]);
            rep(k, 0, j) if (!in(c, p[k])) c = three(p[i], p[j], p[k]);
        }
    }
    return c;
}

// area of the intersection of two circles
ld circleInterArea(ld x1, ld y1, ld r1, ld x2, ld y2, ld r2)
{
    ld d = hypotl(x1 - x2, y1 - y2), PI = acosl(-1);
    if (d >= r1 + r2) return 0;
    if (d <= fabsl(r1 - r2)) { ld r = min(r1, r2); return PI * r * r; }
    auto seg = [&](ld r, ld R) { ld a = acosl((d * d + r * r - R * R) / (2 * d * r)); return r * r * a - r * r * sinl(2 * a) / 2; };
    return seg(r1, r2) + seg(r2, r1);
}

// area of the union of rectangles [x1, x2] x [y1, y2] (integer coordinates), sweep + segment tree
int rectUnionArea(const vector<array<int, 4>> &rects)
{
    vi ys;
    for (auto &r : rects) ys.pb(r[1]), ys.pb(r[3]);
    sort(all(ys));
    ys.erase(unique(all(ys)), ys.end());
    int m = ys.size();
    if (m < 2) return 0;
    vi cnt(4 * m, 0), len(4 * m, 0);
    function<void(int, int, int, int, int, int)> upd = [&](int x, int l, int r, int ql, int qr, int v)
    {   // elementary intervals [ys[l], ys[r + 1]]
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) cnt[x] += v;
        else { int mid = (l + r) / 2; upd(2 * x, l, mid, ql, qr, v); upd(2 * x + 1, mid + 1, r, ql, qr, v); }
        if (cnt[x] > 0) len[x] = ys[r + 1] - ys[l];
        else if (l == r) len[x] = 0;
        else len[x] = len[2 * x] + len[2 * x + 1];
    };
    vector<array<int, 4>> ev;
    for (auto &r : rects) { ev.pb({r[0], 1, r[1], r[3]}); ev.pb({r[2], -1, r[1], r[3]}); }
    sort(all(ev));
    int area = 0, lastX = ev[0][0];
    for (auto &e : ev)
    {
        area += (e[0] - lastX) * len[1];
        lastX = e[0];
        int lo = lower_bound(all(ys), e[2]) - ys.begin(), hi = lower_bound(all(ys), e[3]) - ys.begin() - 1;
        if (lo <= hi) upd(1, 0, m - 2, lo, hi, e[1]);
    }
    return area;
}

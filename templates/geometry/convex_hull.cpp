// integer convex hull (monotone chain, ccw, no collinear points)
// inside(h, q): point in convex polygon in O(log n), boundary counts as inside
struct pt
{
    int x, y;
    pt operator-(const pt &o) const { return {x - o.x, y - o.y}; }
    bool operator<(const pt &o) const { return x < o.x || (x == o.x && y < o.y); }
};
__int128 cross(pt a, pt b) { return (__int128)a.x * b.y - (__int128)a.y * b.x; }
__int128 dot(pt a, pt b) { return (__int128)a.x * b.x + (__int128)a.y * b.y; }
vector<pt> hull(vector<pt> p) // ccw, no collinear points, starts at lowest x
{
    sort(all(p));
    p.erase(unique(all(p), [](pt a, pt b) { return a.x == b.x && a.y == b.y; }), p.end());
    if (p.size() < 3) return p;
    vector<pt> h;
    rep(it, 0, 2)
    {
        int st = h.size();
        for (auto &q : p)
        {
            while ((int)h.size() >= st + 2 && cross(h.back() - h[h.size() - 2], q - h[h.size() - 2]) <= 0) h.pop_back();
            h.pb(q);
        }
        h.pop_back();
        reverse(all(p));
    }
    return h;
}
bool inside(vector<pt> &h, pt q) // ccw convex polygon, boundary counts as inside
{
    int n = h.size();
    pt o = h[0];
    if (cross(h[1] - o, q - o) < 0 || cross(h[n - 1] - o, q - o) > 0) return false;
    int l = 1, r = n - 1;
    while (r - l > 1)
    {
        int mid = (l + r) / 2;
        if (cross(h[mid] - o, q - o) >= 0) l = mid;
        else r = mid;
    }
    if (cross(h[n - 1] - o, q - o) == 0) return dot(q - o, q - o) <= dot(h[n - 1] - o, h[n - 1] - o);
    return cross(h[l + 1] - h[l], q - h[l]) >= 0;
}

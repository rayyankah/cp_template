// minkowski sum of two ccw convex polygons in O(n + m) + point in convex polygon
// {a + b} for a in p, b in q is again convex; use it for midpoint / translation questions
struct pt
{
    int x, y;
    pt operator+(const pt &o) const { return {x + o.x, y + o.y}; }
    pt operator-(const pt &o) const { return {x - o.x, y - o.y}; }
    pt operator*(int k) const { return {x * k, y * k}; }
};
int cross(pt a, pt b) { return a.x * b.y - a.y * b.x; }
int dot(pt a, pt b) { return a.x * b.x + a.y * b.y; }
// rotate so the lowest (then leftmost) point comes first
void reorder(vector<pt> &p)
{
    int k = 0;
    rep(i, 1, (int)p.size()) if (p[i].y < p[k].y || (p[i].y == p[k].y && p[i].x < p[k].x)) k = i;
    rotate(p.begin(), p.begin() + k, p.end());
}
vector<pt> minkowski(vector<pt> p, vector<pt> q) // both ccw convex
{
    reorder(p), reorder(q);
    int n = p.size(), m = q.size();
    p.pb(p[0]), p.pb(p[1]), q.pb(q[0]), q.pb(q[1]);
    vector<pt> res;
    int i = 0, j = 0;
    while (i < n || j < m)
    {
        res.pb(p[i] + q[j]);
        int c = cross(p[i + 1] - p[i], q[j + 1] - q[j]);
        if (c >= 0 && i < n) i++;
        if (c <= 0 && j < m) j++;
    }
    vector<pt> h; // drop collinear points
    int k = res.size();
    rep(t, 0, k)
    {
        pt a = res[(t + k - 1) % k], b = res[t], c = res[(t + 1) % k];
        if (cross(b - a, c - b) != 0) h.pb(b);
    }
    reorder(h);
    return h;
}
bool inside(vector<pt> &h, pt q) // ccw convex, boundary counts
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

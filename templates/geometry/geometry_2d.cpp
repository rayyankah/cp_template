// 2d geometry kit
// P  : integer point, everything exact (|coord| <= 1e9 is safe with cross/dot in long long)
// PD : long double point, for intersection points, distances, circles
struct P
{
    int x, y;
    P operator+(const P &o) const { return {x + o.x, y + o.y}; }
    P operator-(const P &o) const { return {x - o.x, y - o.y}; }
    P operator*(int k) const { return {x * k, y * k}; }
    bool operator<(const P &o) const { return x < o.x || (x == o.x && y < o.y); }
    bool operator==(const P &o) const { return x == o.x && y == o.y; }
};
int cross(P a, P b) { return a.x * b.y - a.y * b.x; }
int cross(P a, P b, P c) { return cross(b - a, c - a); } // > 0: c is left of a->b (ccw)
int dot(P a, P b) { return a.x * b.x + a.y * b.y; }
int dist2(P a, P b) { return dot(a - b, a - b); }
int sgn(int x) { return (x > 0) - (x < 0); }

bool onSeg(P a, P b, P p) // p on segment ab (endpoints included)
{
    return cross(a, b, p) == 0 && min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
           min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}
bool segInter(P a, P b, P c, P d) // segments ab and cd share at least one point
{
    int c1 = sgn(cross(a, b, c)), c2 = sgn(cross(a, b, d));
    int c3 = sgn(cross(c, d, a)), c4 = sgn(cross(c, d, b));
    if (c1 * c2 < 0 && c3 * c4 < 0) return true; // proper crossing
    return onSeg(a, b, c) || onSeg(a, b, d) || onSeg(c, d, a) || onSeg(c, d, b);
}

int area2(const vector<P> &p) // twice the signed area (ccw > 0), shoelace
{
    int s = 0, n = p.size();
    rep(i, 0, n) s += cross(p[i], p[(i + 1) % n]);
    return s;
}
int inPoly(const vector<P> &p, P q) // any simple polygon: 0 outside, 1 inside, 2 on boundary
{
    int n = p.size(), w = 0;
    rep(i, 0, n)
    {
        P a = p[i], b = p[(i + 1) % n];
        if (onSeg(a, b, q)) return 2;
        if ((a.y <= q.y) != (b.y <= q.y))
        {
            int c = cross(a, b, q);
            if ((c > 0) == (b.y > a.y)) w ^= 1;
        }
    }
    return w;
}
int boundaryPoints(const vector<P> &p) // lattice points on the boundary
{
    int n = p.size(), b = 0;
    rep(i, 0, n) b += __gcd(llabs(p[i].x - p[(i + 1) % n].x), llabs(p[i].y - p[(i + 1) % n].y));
    return b;
}
// pick: area = inside + boundary / 2 - 1  ->  inside = (|area2| - boundary + 2) / 2

int closestPair2(vector<P> p) // smallest squared distance, n >= 2, O(n log n)
{
    sort(all(p));
    set<pi> s; // {y, x}
    int best = LLONG_MAX, j = 0;
    rep(i, 0, (int)p.size())
    {
        int d = ceil(sqrt((long double)best));
        while (j < i && p[i].x - p[j].x >= d) s.erase({p[j].y, p[j].x}), j++;
        auto lo = s.lower_bound({p[i].y - d, LLONG_MIN}), hi = s.upper_bound({p[i].y + d, LLONG_MAX});
        for (auto it = lo; it != hi; it++) best = min(best, dist2(p[i], {it->second, it->first}));
        s.insert({p[i].y, p[i].x});
    }
    return best;
}
int diameter2(const vector<P> &h) // farthest pair (squared) of a ccw convex hull, rotating calipers
{
    int n = h.size(), best = 0;
    if (n == 1) return 0;
    if (n == 2) return dist2(h[0], h[1]);
    for (int i = 0, j = 1; i < n; i++)
    {
        while (cross(h[(i + 1) % n] - h[i], h[(j + 1) % n] - h[j]) > 0) j = (j + 1) % n;
        best = max({best, dist2(h[i], h[j]), dist2(h[(i + 1) % n], h[j])});
    }
    return best;
}
bool half(P a) { return a.y < 0 || (a.y == 0 && a.x < 0); }
bool angleLess(P a, P b) // sort vectors by polar angle in [0, 2pi), exact
{
    if (half(a) != half(b)) return half(a) < half(b);
    return cross(a, b) > 0;
}

// ---------------- floating point part ----------------
typedef long double ld;
const ld EPS = 1e-9, PI = acosl(-1);
struct PD
{
    ld x, y;
    PD operator+(const PD &o) const { return {x + o.x, y + o.y}; }
    PD operator-(const PD &o) const { return {x - o.x, y - o.y}; }
    PD operator*(ld k) const { return {x * k, y * k}; }
    PD operator/(ld k) const { return {x / k, y / k}; }
};
ld cross(PD a, PD b) { return a.x * b.y - a.y * b.x; }
ld dot(PD a, PD b) { return a.x * b.x + a.y * b.y; }
ld len(PD a) { return sqrtl(dot(a, a)); }
PD rot(PD a, ld t) { return {a.x * cosl(t) - a.y * sinl(t), a.x * sinl(t) + a.y * cosl(t)}; }
PD toPD(P a) { return {(ld)a.x, (ld)a.y}; }

PD lineInter(PD a, PD b, PD c, PD d) // lines ab and cd, must not be parallel
{
    return a + (b - a) * (cross(c - a, d - c) / cross(b - a, d - c));
}
bool segInterPoint(P A, P B, P C, P D, PD &res) // true + the point if they meet in exactly one point
{
    if (!segInter(A, B, C, D)) return false;
    if (cross(B - A, D - C) == 0) // parallel: collinear overlap, a single point only if they just touch
    {
        for (P q : {A, B})
            for (P r : {C, D})
                if (q == r && !(onSeg(A, B, (q == C ? D : C)) && onSeg(C, D, (q == A ? B : A)))) { res = toPD(q); return true; }
        return false; // overlap of positive length (infinitely many points)
    }
    res = lineInter(toPD(A), toPD(B), toPD(C), toPD(D));
    return true;
}
ld distPointLine(PD p, PD a, PD b) { return fabsl(cross(b - a, p - a)) / len(b - a); }
ld distPointSeg(PD p, PD a, PD b)
{
    if (dot(p - a, b - a) < 0) return len(p - a);
    if (dot(p - b, a - b) < 0) return len(p - b);
    return distPointLine(p, a, b);
}
vector<PD> circleLine(PD c, ld r, PD a, PD b) // intersection points of circle and line ab
{
    PD d = b - a;
    PD h = a + d * (dot(c - a, d) / dot(d, d)); // foot of perpendicular
    ld s = r * r - dot(c - h, c - h);
    if (s < -EPS) return {};
    if (s < EPS) return {h};
    PD off = d * (sqrtl(s) / len(d));
    return {h - off, h + off};
}
vector<PD> circleCircle(PD c1, ld r1, PD c2, ld r2) // intersection points (none if same circle)
{
    PD d = c2 - c1;
    ld D = len(d);
    if (D < EPS || D > r1 + r2 + EPS || D < fabsl(r1 - r2) - EPS) return {};
    ld a = (r1 * r1 - r2 * r2 + D * D) / (2 * D), h2 = r1 * r1 - a * a;
    PD m = c1 + d * (a / D);
    if (h2 < EPS) return {m};
    PD off = PD{-d.y, d.x} * (sqrtl(h2) / D);
    return {m - off, m + off};
}

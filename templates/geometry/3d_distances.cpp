// 3d geometry in long double: point-segment, segment-segment, point-triangle, segment-triangle distances
// segTri(s, e, a, b, c) = 0 when the segment touches or crosses triangle abc
typedef long double ld;
struct p3
{
    ld x, y, z;
    p3 operator+(const p3 &o) const { return {x + o.x, y + o.y, z + o.z}; }
    p3 operator-(const p3 &o) const { return {x - o.x, y - o.y, z - o.z}; }
    p3 operator*(ld k) const { return {x * k, y * k, z * k}; }
};
ld dot(p3 a, p3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
p3 cross(p3 a, p3 b) { return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x}; }
ld len(p3 a) { return sqrtl(dot(a, a)); }
ld pointSeg(p3 p, p3 a, p3 b)
{
    p3 d = b - a;
    ld t = dot(p - a, d) / dot(d, d);
    t = max((ld)0, min((ld)1, t));
    return len(p - (a + d * t));
}
ld segSeg(p3 a, p3 b, p3 c, p3 d) // closest points of two segments, clamped
{
    p3 u = b - a, v = d - c, w = a - c;
    ld aa = dot(u, u), bb = dot(u, v), cc = dot(v, v), dd = dot(u, w), ee = dot(v, w);
    ld den = aa * cc - bb * bb;
    ld best = min(min(pointSeg(a, c, d), pointSeg(b, c, d)), min(pointSeg(c, a, b), pointSeg(d, a, b)));
    if (den > 1e-12)
    {
        ld s = (bb * ee - cc * dd) / den, t = (aa * ee - bb * dd) / den;
        if (s >= 0 && s <= 1 && t >= 0 && t <= 1) best = min(best, len((a + u * s) - (c + v * t)));
    }
    return best;
}
bool inTri(p3 p, p3 a, p3 b, p3 c, p3 n) // p is on the plane of abc
{
    ld s1 = dot(cross(b - a, p - a), n), s2 = dot(cross(c - b, p - b), n), s3 = dot(cross(a - c, p - c), n);
    return (s1 >= -1e-9 && s2 >= -1e-9 && s3 >= -1e-9) || (s1 <= 1e-9 && s2 <= 1e-9 && s3 <= 1e-9);
}
ld pointTri(p3 p, p3 a, p3 b, p3 c)
{
    p3 n = cross(b - a, c - a);
    ld dn = dot(p - a, n) / len(n);
    p3 q = p - n * (dot(p - a, n) / dot(n, n)); // projection onto the plane
    if (inTri(q, a, b, c, n)) return fabsl(dn);
    return min(pointSeg(p, a, b), min(pointSeg(p, b, c), pointSeg(p, c, a)));
}
ld segTri(p3 s, p3 e, p3 a, p3 b, p3 c)
{
    p3 n = cross(b - a, c - a);
    ld d0 = dot(s - a, n), d1 = dot(e - a, n);
    if ((d0 < 0 && d1 > 0) || (d0 > 0 && d1 < 0))
    {
        p3 q = s + (e - s) * (d0 / (d0 - d1));
        if (inTri(q, a, b, c, n)) return 0;
    }
    ld res = min(pointTri(s, a, b, c), pointTri(e, a, b, c));
    res = min(res, min(segSeg(s, e, a, b), min(segSeg(s, e, b, c), segSeg(s, e, c, a))));
    return res;
}

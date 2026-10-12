//shikijuki and power grid cf
int sz[N];
int parent[N];
void make(int n)
{
    parent[n] = n;
    sz[n] = 1;
}
int find(int v)
{
    if (parent[v] == v)
        return v;
    return parent[v] = find(parent[v]);
}
void Union(int a, int b)
{
    a = find(a);
    b = find(b);
    if (a != b)
    {
        if (sz[a] < sz[b])
        {
 
            swap(a, b);
        }
        parent[b] = a;
        sz[a] += sz[b];
        sz[b] = 0;
    }
}

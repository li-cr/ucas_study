#include <bits/stdc++.h>
using namespace std;
#define pb push_back
const int N = 2e5 + 5;
int n, siz[N], rt, S, mx[N], ans[N], d[N], deg[N], cnt, g[N], o[N];
bool vis[N];
vector<int> e[N];
int c[N];
void add(int x, int z)
{
    for (; x <= 2 * n; x += x & -x)
        c[x] += z;
}
int ask(int x)
{
    int res = 0;
    for (; x; x -= x & -x)
        res += c[x];
    return res;
}
void dfs1(int u, int fa)
{
    for (auto v : e[u])
        if (v != fa)
        {
            dfs1(v, u);
            g[u] = min(g[u], g[v] + 1);
        }
}
void dfs2(int u, int fa)
{
    for (auto v : e[u])
        if (v != fa)
        {
            g[v] = min(g[v], g[u] + 1);
            dfs2(v, u);
        }
}
void getroot(int u, int fa)
{
    siz[u] = 1, mx[u] = 0;
    for (auto v : e[u])
        if (!vis[v] && v != fa)
        {
            getroot(v, u);
            siz[u] += siz[v];
            mx[u] = max(mx[u], siz[v]);
        }
    mx[u] = max(mx[u], S - siz[u]);
    if (!rt || mx[u] < mx[rt])
        rt = u;
}
void getdis(int u, int fa)
{
    o[++cnt] = u;
    for (auto v : e[u])
        if (v != fa && !vis[v])
            d[v] = d[u] + 1, getdis(v, u);
}
void solve(int u, int len1, int mul)
{
    d[u] = len1;
    cnt = 0;
    getdis(u, 0);
    for (int i = 1; i <= cnt; i++)
        add(g[o[i]] - d[o[i]] + n, 2 - deg[o[i]]);
    for (int i = 1; i <= cnt; i++)
    {
        add(g[o[i]] - d[o[i]] + n, deg[o[i]] - 2);
        ans[o[i]] += ask(d[o[i]] + n) * mul;
        add(g[o[i]] - d[o[i]] + n, 2 - deg[o[i]]);
    }
    for (int i = 1; i <= cnt; i++)
        add(g[o[i]] - d[o[i]] + n, deg[o[i]] - 2);
}
void divide(int u)
{
    solve(u, 0, 1);
    vis[u] = 1;
    for (auto v : e[u])
        if (!vis[v])
        {
            solve(v, 1, -1);
            S = siz[v], rt = 0;
            getroot(v, 0);
            divide(rt);
        }
}

int main()
{
    memset(g, 0x3f, sizeof(g));
    scanf("%d", &n);
    for (int i = 1, x, y; i < n; i++)
    {
        scanf("%d%d", &x, &y);
        // x = i, y = i + 1;
        e[x].pb(y), e[y].pb(x);
        deg[x]++, deg[y]++;
    }
    for (int i = 1; i <= n; i++)
        if (deg[i] == 1)
            g[i] = 0;
    dfs1(1, 0);
    dfs2(1, 0);

    S = n, rt = 0;
    getroot(1, 0);
    divide(rt);
    for (int i = 1; i <= n; i++)
        printf("%d\n", deg[i] == 1 ? 1 : ans[i]);
    return 0;
}
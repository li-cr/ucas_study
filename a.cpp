#include <bits/stdc++.h>

const int N = 7e4 + 10;
std::vector<int> G[N];
int n, cnt, dp[N], dep[N], list[N], ans[N];

int rt, mx[N], siz[N];
bool vis[N];
int c[N << 2];
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
    for (auto v : G[u])
        if (v != fa)
        {
            dfs1(v, u);
            dp[u] = std::min(dp[u], dp[v] + 1);
        }
}
void dfs2(int u, int fa)
{
    for (auto v : G[u])
        if (v != fa)
        {
            dp[v] = std::min(dp[v], dp[u] + 1);
            dfs2(v, u);
        }
}

void getroot(int u, int fa, int S)
{
    siz[u] = 1, mx[u] = 0;
    for (auto v : G[u])
        if (!vis[v] && v != fa)
        {
            getroot(v, u, S);
            siz[u] += siz[v];
            mx[u] = std::max(mx[u], siz[v]);
        }
    mx[u] = std::max(mx[u], S - siz[u]);
    if (!rt || mx[u] < mx[rt])
        rt = u;
}

void getdis(int u, int fa)
{
    list[cnt++] = u;
    for (auto v : G[u])
    {
        if (v == fa || vis[v])
            continue;
        dep[v] = dep[u] + 1;
        getdis(v, u);
    }
}
void solve(int u, int deep_i, int va)
{
    dep[u] = deep_i;
    cnt = 0;
    getdis(u, 0);
    for (int i = 0; i < cnt; i++)
        add(dp[list[i]] - dep[list[i]] + n, 2 - G[list[i]].size());

    for (int i = 0; i < cnt; i++)
    {
        int u = list[i], deg = G[u].size();
        add(dp[u] - dep[u] + n, deg - 2);
        ans[u] += ask(dep[u] + n) * va;
        add(dp[u] - dep[u] + n, 2 - deg);
    }
    for (int i = 0; i < cnt; i++)
        add(dp[list[i]] - dep[list[i]] + n, G[list[i]].size() - 2);
}

void divide(int u)
{
    solve(u, 0, 1);
    vis[u] = 1;
    for (auto v : G[u])
    {
        if (vis[v])
            continue;
        solve(v, 1, -1);
        rt = 0;
        getroot(v, 0, siz[v]);
        divide(rt);
    }
}
int main()
{
    std::cin >> n;
    for (int i = 1, x, y; i < n; i++)
    {
        std::cin >> x >> y;
        // x = i, y = i + 1;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    for (int i = 1; i <= n; i++)
        if (G[i].size() > 1)
            dp[i] = 1e6;
    dfs1(1, 0);
    dfs2(1, 0);

    getroot(1, 0, n);
    divide(rt);
    // solve(rt, 0, 1);
    for (int i = 1; i <= n; i++)
        std::cout << (G[i].size() == 1 ? 1 : ans[i]) << "\n";
    return 0;
}
/*
6
1 2
1 3
3 4
3 5
4 6

8
1 5
1 2
1 3
2 7
4 7
7 8
3 6

*/
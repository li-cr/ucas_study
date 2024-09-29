#include <bits/stdc++.h>

using namespace std;

const int N = 7e4 + 10;

struct mt_tr
{
#define lowbit(x) (x & (-x))
    int va[N << 2], n, offset;
    mt_tr(int n, int offset) : n(n), offset(offset)
    {
    }
    void add(int i, int value)
    {
        i += offset;
        while (i <= n + offset)
            va[i] += value, i += lowbit(i);
    }
    int sum(int i)
    {
        int ans = 0;
        i += offset;
        while (i)
            ans += va[i], i -= lowbit(i);
        return ans;
    }
};

struct qsork
{
    std::vector<int> G[N];
    int deep[N], dp[N], dis[N], siz[N];
    int sz[N], mx[N];
    bool c_dis[N];
    void add(int u, int v)
    {
        G[v].push_back(u);
        G[u].push_back(v);
    }
    int find_root(int u, int fa, int cnt, int root)
    {
        mx[0] = 1e9;
        sz[u] = 1, mx[u] = 0;
        for (auto v : G[u])
        {
            if (v == fa || c_dis[v])
                continue;
            root = find_root(v, u, cnt, root);
            sz[u] += sz[v];
            mx[u] = max(mx[u], sz[v]);
        }
        mx[u] = max(mx[u], cnt - sz[u]);
        if (mx[u] <= mx[root])
            root = u;
        return root;
    }

    void calc_value(int u, int fa)
    {
        deep[u] = deep[fa] + 1;
        dis[u] = 1e9;
        siz[u] = 1;
        if (G[u].size() == 1)
            dis[u] = 0;
        for (auto x : G[u])
        {
            if (x == fa || c_dis[x])
                continue;
            calc_value(x, u);
            dis[u] = min(dis[u], dis[x]);
            siz[u] += siz[x];
        }
        dis[u]++;
    }
    int dfs2(int u, int fa)
    {
        // std::cout << u << " " << deep[u] << " " << dp[u] << "\n";
        std::cout << u << " " << deep[u] << " " << dis[u] << " " << (deep[u] >= dis[u] && deep[fa] < dis[fa]) << "\n";
        // "\n"; if () return 1;
        int ans = 0;
        for (auto x : G[u])
        {
            if (x == fa)
                continue;
            ans += dfs2(x, u);
        }
        return ans + (deep[u] >= dis[u]) * (2 - G[u].size());
    }
};

qsork tree;
mt_tr AA(N, N);
int ans[N];

void add_tree(int u, int fa, int va)
{
    for (auto v : tree.G[u])
    {
        if (v == fa || tree.c_dis[v])
            continue;
        add_tree(v, u, va);
    }
    AA.add(tree.deep[u] - tree.dis[u], (2 - tree.G[u].size()) * va);
}
void calc(int u, int fa)
{
    tree.calc_value(u, fa);
    for ()
}

int main()
{
    int n;
    cin >> n;
    for (int i = 2; i <= n; i++)
    {
        int x, y;
        cin >> x >> y;
        tree.add(x, y);
    }
    calc(tree.find_root(1, 0, n, 0), 0);
    return 0;
}

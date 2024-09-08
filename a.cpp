#include <bits/stdc++.h>

using namespace std;

const int N = 7e5 + 10;
std::vector<int> G[N];
int deep[N], dp[N], dis[N];

int dfs1(int u, int fa)
{
    deep[u] = deep[fa] + 1;
    dp[u] = 0x3f3f3f3f;
    bool lef = true;
    for (auto x : G[u])
    {
        if (x == fa)
            continue;
        dp[u] = min(dp[u], dfs1(x, u));
        lef = false;
    }
    if (lef)
        dp[u] = deep[u];
    // std::cout << u << " " << deep[u] << "  " << dp[u] << "\n";
    return dp[u];
}

int dfs2(int u, int fa)
{
    // std::cout << u << " " << deep[u] << " " << dp[u] << "\n";
    deep[u] = deep[fa] + 1;
    // std::cout << u << " " << deep[u] << " " << dis[u] << " " << (deep[u] >= dis[u] && deep[fa] < dis[fa]) << "\n";
    // if () return 1;
    int ans = 0;
    for (auto x : G[u])
    {
        if (x == fa)
            continue;
        ans += dfs2(x, u);
    }
    return ans + (deep[u] >= dis[u] && deep[fa] < dis[fa]);
}

void calcdis(int n)
{
    queue<int> q;

    for (int i = 1; i <= n; i++)
    {
        dis[i] = -1;
        if (G[i].size() == 1)
            dis[i] = 0, q.push(i);
    }
    while (q.size())
    {
        int u = q.front();
        q.pop();
        for (auto x : G[u])
            if (dis[x] == -1)
                dis[x] = dis[u] + 1, q.push(x);
    }
    // for (int i = 1; i <= n; i++)
    // std::cout << dis[i] << " ";
    // puts("");
}
int main()
{
    int n;
    cin >> n;
    deep[0] = -1;
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        G[v].push_back(u);
        G[u].push_back(v);
    }
    calcdis(n);
    for (int i = 1; i <= n; i++)
    {
        int ans = dfs2(i, 0);
        std::cout << ans;
        if (i < n)
            puts("");
    }
    return 0;
}

/*
deep[u] >= dis[u] && deep[fa] < dis[fa]
sum_u

*/
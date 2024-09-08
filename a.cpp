#include <bits/stdc++.h>

using namespace std;

const int N = 7e5 + 10;
std::vector<int> G[N];
int deep[N], dp[N], dis[N], ans[N];

int dfs2(int u, int fa)
{
    deep[u] = deep[fa] + 1;
    int ans = 0;
    for (auto x : G[u])
    {
        if (x == fa)
            continue;
        ans += dfs2(x, u);
    }
    if (deep[u] >= dis[u])
        ans += 2 - G[u].size();
    return ans;
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
}

void dfs(int rt, int fa)
{
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
    int rt = 1;
    ans[rt] = dfs2(rt, 0);
    dfs(rt, 0);
    // for (int i = 1; i <= n; i++)
    // {
    //     int ans = dfs2(i, 0);
    //     if (G[i].size() == 1)
    //         ans = 1;
    //     std::cout << ans;
    //     if (i < n)
    //         puts("");
    // }
    return 0;
}

/*
deep[u] >= dis[u] && deep[fa] < dis[fa]
sum_u

*/
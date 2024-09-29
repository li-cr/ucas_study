# 网上的作业

[A - Nearest Point](A_problem.png "https://vjudge.net/contest/653782#problem/A")

[B - A unique permutation](B_problem.png "https://vjudge.net/contest/653782#problem/B")

[C - Lost items](C_problem.png "https://vjudge.net/contest/653782#problem/C")

[D - Extra Problem](D_problem.png "https://www.luogu.com.cn/problem/P4183")

## A

```cpp
#include <bits/stdc++.h>

using namespace std;

using LL = long long;
using PII = pair<LL, LL>;
LL dis(PII &a, PII &b)
{
    return 1LL * (a.first - b.first) * (a.first - b.first) + 1LL * (a.second - b.second) * (a.second - b.second);
}
int main()
{
    LL t;
    cin >> t;
    for (int _ = 0; _ < t; _++)
    {
        std::vector<PII> a, b;
        LL n;
        cin >> n;
        for (LL i = 0; i < n; i++)
        {
            LL x, y;
            cin >> x >> y;
            a.push_back({x, y});
        }

        for (LL i = 0; i < n; i++)
        {
            LL x, y;
            cin >> x >> y;
            b.push_back({x, y});
        }
        LL ans = 2e18;
        for (LL i = 0; i < n; i++)
            for (LL j = 0; j < n; j++)
                ans = min(ans, dis(a[i], b[j]));
        if (_)
            puts("");
        printf("%.3lf", sqrt(ans));
    }
    return 0;
}
```

## B

```cpp
#include <bits/stdc++.h>

using namespace std;

std::vector<int> tmp(1000000);
void split(int l, int r, std::vector<int> &v)
{
    int length = r - l + 1;
    if (length <= 2)
        return;
    int now = l, mid = l;
    for (int i = l; i <= r; i += 2)
        tmp[now++] = v[i], mid++;
    for (int i = l + 1; i <= r; i += 2)
        tmp[now++] = v[i];
    for (int i = l; i <= r; i++)
        v[i] = tmp[i];
    split(l, mid - 1, v);
    split(mid, r, v);
}

int main()
{
    while (true)
    {
        int n;
        cin >> n;
        if (n == 0)
            break;
        std::vector<int> v;
        for (int i = 0; i < n; i++)
            v.push_back(i);
        split(0, n - 1, v);
        std::cout << n << ":";
        for (auto x : v)
            std::cout << " " << x;
        puts("");
    }
    return 0;
}
```

## C

```cpp
#include <bits/stdc++.h>

using namespace std;

using LL = long long;
using PII = pair<LL, LL>;
LL dis(PII &a, PII &b)
{
    return 1LL * (a.first - b.first) * (a.first - b.first) + 1LL * (a.second - b.second) * (a.second - b.second);
}

map<LL, std::vector<int>> sek(std::vector<int> a)
{
    map<LL, std::vector<int>> ma;
    for (int i = 0; i < 1 << a.size(); i++)
    {
        int num = 0;
        LL sum = 0;
        for (int j = 0; j < a.size(); j++)
            if ((i >> j) & 1)
                num++, sum += a[j];
        ma[sum].push_back(num);
    }
    for (auto &[x, v] : ma)
    {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
    }

    return ma;
}

int main()
{
    LL t;
    cin >> t;
    for (int _ = 0; _ < t; _++)
    {
        LL n, d;
        cin >> n >> d;
        std::vector<int> st;
        for (int i = 0; i < n / 2; i++)
        {
            int a;
            cin >> a;
            st.push_back(a);
        }
        auto l = sek(st);
        std::vector<int>().swap(st);
        for (int i = n / 2; i < n; i++)
        {
            int a;
            cin >> a;
            st.push_back(a);
        }
        auto r = sek(st);

        std::map<int, int> ans_v;
        for (auto [x, v] : l)
        {
            if (r.find(d - x) == r.end())
                continue;
            auto u = r[d - x];
            for (int i = 0; i < v.size(); i++)
                for (int j = 0; j < u.size(); j++)
                    ans_v[v[i] + u[j]] = 1;
            if (ans_v.size() >= 2)
                break;
        }

        printf("Case #%d: ", _ + 1);

        if (ans_v.size() == 0)
            printf("IMPOSSIBLE");
        else if (ans_v.size() > 1)
            printf("AMBIGIOUS");
        else
            printf("%d", (*ans_v.begin()).first);

        if (_ < t)
            puts("");
    }
    return 0;
}
```

## D

```cpp
#include <bits/stdc++.h>

const int N = 7e4 + 10;
std::vector<int> G[N];
int n, cnt, dp[N], dep[N], list[N], ans[N];

int rt, mx[N], siz[N];
bool vis[N];

int c[N << 2];
void add(int x, int z){ for (; x <= 2 * n;c[x] +=z, x += x & -x); }
int ask(int x)
{
    int res = 0;
    for (; x;res += c[x], x -= x & -x);
    return res;
}
void dfs1(int u, int fa)
{
    for (auto v : G[u])
    {
        if (v == fa) continue;
        dfs1(v, u);
        dp[u] = std::min(dp[u], dp[v] + 1);
    }
}
void dfs2(int u, int fa)
{
    for (auto v : G[u])
    {
        if (v == fa) continue;
        dp[v] = std::min(dp[v], dp[u] + 1);
        dfs2(v, u);
    }
}

void getroot(int u, int fa, int S)
{
    siz[u] = 1, mx[u] = 0;
    for (auto v : G[u])
     {
        if (vis[v] || v == fa) continue;
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
        if (v == fa || vis[v]) continue;
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
        if (vis[v]) continue;
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
        G[x].push_back(y);
        G[y].push_back(x);
    }
    for (int i = 1; i <= n; i++)
        dp[i] = G[i].size() > 1 ? 1e6 : 0;
    dfs1(1, 0);
    dfs2(1, 0);

    getroot(1, 0, n);
    divide(rt);
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
```

[A - Nearest Point](A_problem.png "https://vjudge.net/contest/653782#problem/A")
<br>
[B - A unique permutation](B_problem.png "https://vjudge.net/contest/653782#problem/B")
<br>
[C - Lost items](C_problem.png "https://vjudge.net/contest/653782#problem/C")
<br>
[D - Extra Problem](D_problem.png "https://www.luogu.com.cn/problem/P4183")
D 不会。

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

```cpp
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
```

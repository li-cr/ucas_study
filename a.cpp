#include <bits/stdc++.h>

const int N = 5e5 + 10;
using LL = long long;
// double f[N], d[N];
int a[N], c[N];

int solve()
{
    int n;
    std::cin >> n;
    std::priority_queue<int, std::vector<int>> qu;
    // int ans = 0;
    std::vector<std::pair<int, int>> v;
    v.push_back({0, 0});
    for (int i = 1; i <= n; i++)
    {
        std::cin >> a[i] >> c[i];
        v.push_back({a[i], c[i]});
    }
    sort(v.begin(), v.end());
    int L, P;
    std::cin >> L >> P;
    int ans = 0;

    for (int i = n; i >= 0; i--)
    {
        int a = v[i].first, b = v[i].second;
        while (L - P > a)
        {
            if (!qu.size())
                return -1;
            ans++;
            P += qu.top();
            qu.pop();
        }
        qu.push(b);
    }
    return ans;
}

int main()
{
    int t;
    std::cin >> t;
    while (t--)
        std::cout << solve() << "\n";
}
/*
 */
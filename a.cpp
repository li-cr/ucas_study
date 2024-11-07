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
    std::map<std::string, bool> s, a[5];
    int t;
    std::cin >> t;
    for (int _ = 1; _ <= t; _++)
    {
        int x;
        std::cin >> x;
        for (int i = 1; i <= x; i++)
        {
            std::string c;
            std::cin >> c;
            s[c] = a[_][c] = true;
        }
    }
    std::cout << "|  | q0 | d1 | d2 | d3 | Q |\n";
    std::cout << "| --- | --- | --- | --- | --- | --- |\n";

    for (auto [st, bo] : s)
    {
        std::cout << "| " << st << " | ";
        for (int i = 1; i <= t; i++)
            std::cout << a[i][st] << " | ";
        double f1 = 1, f2 = 0.75, f3 = 0.25;
        double Q = f1 * a[1][st] + f2 / 2 * (a[2][st] + a[3][st]) - f3 / 1 * (a[4][st]);
        std::cout << (Q > 0 ? Q : 0) << "| \n";
    }
}
/*
4
2
banana slug
4
banana slug Ariolimax columbianus
5
Santa Cruz mountains banana slug
4
Santa Cruz Campus Mascot
 */
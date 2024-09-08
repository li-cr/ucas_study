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
        // std::cout << std::sqrt(ans) << "\n";
        if (_)
            puts("");
        printf("%.3lf", sqrt(ans));
    }
    return 0;
}
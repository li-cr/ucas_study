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
#include <bits/stdc++.h>
const int N = 1e5 + 10;
char c[N];
std::optional<std::vector<std::pair<int, int>>> split(int l, int r)
{
    std::vector<std::pair<int, int>> ans;
    if (l >= r)
        return ans;

    bool dis[110] = {false}, wa[26] = {false};
    for (int i = l; i <= r; i++)
        dis[c[i]] = true;
    for (int i = 0; i < 26; i++)
        wa[i] = dis['a' + i] ^ dis['A' + i];

    bool f = false;
    for (int i = l; i <= r; i++)
    {
        if (!wa[c[i] - (islower(c[i]) ? 'a' : 'A')])
            continue;
        if (i - 1 - l + 1 > 1)
            ans.push_back({l, i - 1});
        f = true;
        l = i + 1;
    }
    if (l < r)
        ans.push_back({l, r});
    if (f)
        return ans;
    return std::nullopt;
}
int main()
{
    scanf("%s", c + 1);
    std::queue<std::pair<int, int>> qu;
    qu.push({1, strlen(c + 1)});
    int L = 0, R = 0;
    while (qu.size())
    {
        auto [l, r] = qu.front();
        qu.pop();
        auto list = split(l, r);
        std::cout << l << ' ' << r << "\n";
        if (!list.has_value())
        {
            if (R - L < r - l)
                R = r, L = l;
            continue;
        }
        for (auto [l, r] : list.value())
            qu.push({l, r});
    }
    c[R + 1] = '\0';
    std::cout << " --- " << L << " " << R << " --- " << "\n";
    std::cout << c + L;
    return 0;
}
/*

aaBBAAbZZZAAAUUU
*/
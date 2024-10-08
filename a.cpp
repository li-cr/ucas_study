#include <bits/stdc++.h>

const int N = 5e1 + 10;
using LL = long long;

void se(int x)
{
    std::string c = std::to_string(x) + " : ";
    std::vector<int> v;
    while (x)
    {
        v.push_back(x % 128);
        x /= 128;
    }
    for (int i = v.size() - 1; i >= 0; i--)
    {
        c += (i ? "0" : "1") + std::bitset<7>(v[i]).to_string() + " \\; ";
    }
    std::cout << c << "\\\\\n";
}

void ve(int x)
{
    int u = 0, t = x;
    std::string c, a, b;
    while (t)
        a += (char)('0' + (t & 1)), t >>= 1, u++;
    std::reverse(a.begin(), a.end());
    b += std::string(u - 1, '1') + '0';
    c = b + a.substr(1);
    std::cout << x << " : " << c << "\\\\\n";
}
int a[N];
int main()
{
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++)
        std::cin >> a[i];
    for (int i = 1; i <= n; i++)
        se(a[i]);
    for (int i = 1; i <= n; i++)
        ve(a[i]);
    std::cout << "\n";
    for (int i = 1; i <= n; i++)
        se(a[i] - a[i - 1]);
    for (int i = 1; i <= n; i++)
        ve(a[i] - a[i - 1]);
    return 0;
}
/*
4
777 17743 294068 31251336
*/
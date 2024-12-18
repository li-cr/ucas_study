#include <algorithm>
#include <iostream>
#include <queue>
#include <string.h>
#include <string>
#include <vector>

const int N = 2e5 + 10, M = 2e2 + 10, mod = 1e9 + 7;
using LL = long long;

LL dp[N][15];
int main()
{
    std::string c;
    std::cin >> c;
    std::reverse(c.begin(), c.end());
    c = ' ' + c;
    // if (c.size() > 1)
    // {
    //     if (c[1] != '1')
    //         dp[1][1] = 1;
    //     if (c[1] != '0')
    //         dp[1][0] = 1;
    // }
    LL now = 1;
    dp[0][0] = 1;
    for (int i = 1; i < c.length(); i++)
    {
        for (int j = 0; j < 13; j++)
        {
            if (c[i] != '0')
                dp[i][(j + now) % 13] = (dp[i][(j + now) % 13] + dp[i - 1][j]) % mod;
            if (c[i] != '1')
                dp[i][j] = (dp[i][j] + dp[i - 1][j]) % mod;
        }
        // for (int j = 0; j < 13; j++)
        // std::cout << dp[i][j] << ' ';
        // std::cout << "\n";
        now = now * 2 % 13;
    }
    std::cout << dp[c.length() - 1][0] << "\n";
    return 0;
}
/*
123 456
78  90

 */
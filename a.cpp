#include <bits/stdc++.h>

const int N = 5e1 + 10;
using LL = long long;

int a[N][N], dp[N][N][N][N];
bool dis[N][N][N][N];
bool dis_(int nx, int ny, int n, int m)
{
    return (nx < 1 || nx > n || ny < 1 || ny > m);
}
int dfs(int i, int j, int x, int y, int n, int m)
{
    if (dis[i][j][x][y])
        return dp[i][j][x][y];
    dis[i][j][x][y] = true;
    int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, -1, 0, 1};

    for (int u = 2; u < 4; u++)
        for (int v = 2; v < 4; v++)
        {
            int nx = x + dx[u], ny = y + dy[u];
            int ni = i + dx[v], nj = j + dy[v];
            if (dis_(nx, ny, n, m) || dis_(ni, nj, n, m))
                continue;
            int value = dfs(ni, nj, nx, ny, n, m);
            value += a[i][j] + a[x][y];
            if (i == x && j == y)
                value -= a[i][j];
            // std::cout << i << ' ' << j << ' ' << x << ' ' << y << ' ' << dp[i][j][x][y] << " " << value << " "
            //   << a[i][j] << " " << a[x][y] << "\n";

            dp[i][j][x][y] = std::max(dp[i][j][x][y], value);
        }
    return dp[i][j][x][y];
}
int main()
{
    int n, m;
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            std::cin >> a[i][j];
    dfs(1, 1, 1, 1, n, m);
    std::cout << dp[1][1][1][1];
    // dp[i][j][x][y] =
    return 0;
}
/*
2 2
0 3
3 0

3 3
0 3 9
2 8 5
5 7 0
1
4
>><<
>>><
4
4
>><<
>>><
2
><
><
4
>>><
>><<
6
>><<><
><>>><


*/
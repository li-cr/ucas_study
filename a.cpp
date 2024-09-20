#include <bits/stdc++.h>

#define r3(l, r) ((l + 2 * r) / 3)
#define l3(l, r) ((l * 2 + r) / 3)
double a, b, c, d;

double calc(double y)
{
    return ((a * y + b) * y + c) * y + d;
}

bool chick(double l, double r)
{
    double m1 = l3(l, r), m2 = r3(l, r);
    return (calc(m1) > calc(l)) * ()
}
int main()
{
    std::cin >> a >> b >> c >> d;
    double l = -1e9, r = 1e9;
    while (true)
    {
        double mid = (l + r) / 2;
    }
    return 0;
}

/*
deep[u] >= dis[u] && deep[fa] < dis[fa]
sum_u

*/
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
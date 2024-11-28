#include <iostream>
#include <queue>
#include <string>
#include <thread>

int main()
{
    int n, sum = 0;
    std::cin >> n;
    std::vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> v[i];
        sum += v[i];
    }
    // std::cout << sum << " " << sum % n << "\n";
    if (sum % n)
        return std::cout << "-1", 0;
    int asn = 0, E = 0;
    for (auto &x : v)
    {
        x -= sum / n;
        E += x;
        asn = std::max(asn, std::max(std::abs(E), std::abs(x)));
    }
    std::cout << asn << "\n";
    return 0;
}
/*
123 456
78  90

 */
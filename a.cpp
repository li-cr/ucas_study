#include <bits/stdc++.h>

const int N = 5e1 + 10;
using LL = long long;

std::map<std::string, int> ma[N];
std::vector<std::string> v;

int main()
{
    int n;
    std::cin >> n;
    std::string ans;
    while (n--)
    {

        int x;
        char c[100];
        scanf("%d %c %s", &x, c, c + 1);
        std::string a(c + 1);
        std::cout << x << " " << a << "\n";

        ans += std::to_string(x) + "\\;:\\;";
        // std::cout << "|||" << ans << "<<<<";
        for (int i = 0; i < a.size(); i += 8)
        {
            ans += a.substr(i, 8) + "\\;";
        }

        ans += '\n';
    }
    std::cout << ans;
    return 0;
}
/*
9
1 : 10000
777 : 1111111110100001001\\
17743 : 11111111111111000010101001111\\
294068 : 1111111111111111110000111110010110100\\
31251336 : 1111111111111111111111110110111001101101110001000\\
777 : 1111111110100001001\\
16966 : 11111111111111000001001000110\\
276325 : 1111111111111111110000011011101100101\\
30957268 : 1111111111111111111111110110110000101111011010100\\
*/
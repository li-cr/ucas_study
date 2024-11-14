#include <chrono>
#include <cxxabi.h> //使用abi
#include <iostream>
#include <vector>

using ST = std::chrono::high_resolution_clock;
using LL = long long;

template <typename T> void test()
{
    using TYPE = T;
    LL N = 1e9;
    while (true)
    {
        volatile TYPE tmp = 0;
        auto be = ST::now();
        for (volatile LL i = 0; i < N; i++)
        {
            tmp += (TYPE)114514.0;
        }
        double time = (ST::now() - be).count() / 1e9;
        std::cout << abi::__cxa_demangle(typeid(T).name(), 0, 0, 0) << " : " << time << " " << (N / time) << " " << tmp
                  << "\n";
    } // 2.51168
}

const int AN = 50;
template <typename T> class my_T
{

  public:
    T a[AN][AN];
};

template <typename T> void my_dot(my_T<T> &c, my_T<T> &a, my_T<T> &b)
{
    int n = AN;
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                c.a[i][j] += a.a[i][k] * b.a[k][j];
}

template <typename T> void test3()
{
    using TYPE = T;
    int n = 1e3;
    std::vector<std::vector<T>> a(n), b(n), c(n);
    for (int i = 0; i < n; i++)
    {
        a[i].resize(n);
        b[i].resize(n);
        c[i].resize(n);
    }

    auto be = ST::now();
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                c[i][j] += a[i][k] * b[k][j];
    double time = (ST::now() - be).count() / 1e9;
    std::cout << abi::__cxa_demangle(typeid(T).name(), 0, 0, 0) << " : " << time << " " << "\n";
} // 2.51168

template <typename T> void test2()
{
    using TYPE = T;
    int n = 1e3 / AN;
    std::vector<std::vector<my_T<T>>> a(n), b(n), c(n);
    for (int i = 0; i < n; i++)
    {
        a[i].resize(n);
        b[i].resize(n);
        c[i].resize(n);
    }

    auto be = ST::now();
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                my_dot<T>(c[i][j], a[i][k], b[k][j]);
    double time = (ST::now() - be).count() / 1e9;
    std::cout << abi::__cxa_demangle(typeid(T).name(), 0, 0, 0) << " : " << time << " " << "\n";
} // 2.51168

int main()
{
    // test3<double>();

    test2<double>();

    return 0;
}
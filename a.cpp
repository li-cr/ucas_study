#include <iostream>
#include <thread>

int a[10], b[10];
void f(int i)
{
    std::cin >> a[i] >> b[i];
}
int main()
{
    std::cout << " 大啊大王";
    std::thread A(f, 1), B(f, 2);
    A.join();
    B.join();
    std::cout << a[1] << " " << a[2] << "\n" << b[1] << " " << b[2] << "\n";
    return 0;
}
/*
123 456
78  90

 */
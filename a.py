def pisano_period(m):
    previous, current = 0, 1
    for i in range(m * m):  # 皮萨诺周期的上限
        previous, current = current, (previous + current) % m

        # 找到周期
        if previous == 0 and current == 1:
            return i + 1


def fibonacci_mod_k(n, k):
    if k == 1:
        return 1  # 所有斐波那契数都可以被 1 整除，返回第一个的索引

    period = pisano_period(k)
    fib_mods = []

    previous, current = 0, 1

    # 计算周期内的斐波那契数
    for i in range(period):
        fib_mods.append(previous)
        previous, current = current, (previous + current) % k

    # 获取可被 k 整除的斐波那契数的索引
    indices = [i + 1 for i in range(period) if fib_mods[i] == 0]  # 索引从 1 开始

    # 边界情况处理
    if n <= 0:
        return -1  # 如果 n 非法
    if n <= len(indices):
        return indices[n - 1] % (10**9 + 7)
    else:
        return -1  # 如果 n 超过可被 k 整除的数量，返回 -1


# 主程序入口
if __name__ == "__main__":
    import sys

    input_data = "1000000000000 1377"  # 直接设置输入
    n, k = map(int, input_data.strip().split())

    result = fibonacci_mod_k(n, k)
    print(result)  # 输出结果

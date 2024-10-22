import numpy as np
from scipy.stats import multivariate_normal


def initialize_parameters(X, K):
    # 初始化均值，协方差和混合系数
    n, d = X.shape
    mu = X[np.random.choice(n, K, False)]  # K 个高斯成分的均值，随机从数据中选择
    sigma = [np.eye(d) for _ in range(K)]  # 每个成分的协方差矩阵，初始化为单位矩阵
    pi = np.ones(K) / K  # 初始化混合权重，均匀分布
    return mu, sigma, pi


def e_step(X, mu, sigma, pi, K):
    n = X.shape[0]
    gamma = np.zeros((n, K))

    # 计算后验概率
    for k in range(K):
        gamma[:, k] = pi[k] * multivariate_normal.pdf(X, mean=mu[k], cov=sigma[k])

    # 归一化
    gamma = gamma / np.sum(gamma, axis=1, keepdims=True)
    return gamma


def m_step(X, gamma, K):
    n, d = X.shape
    Nk = np.sum(gamma, axis=0)  # 每个成分的权重和

    mu = np.zeros((K, d))
    sigma = []
    pi = Nk / n

    for k in range(K):
        # 更新均值
        mu[k] = np.sum(gamma[:, k, np.newaxis] * X, axis=0) / Nk[k]

        # 更新协方差
        diff = X - mu[k]
        cov_k = np.dot(gamma[:, k] * diff.T, diff) / Nk[k]
        sigma.append(cov_k + 1e-6 * np.eye(d))  # 加上一个小值，防止协方差矩阵奇异

    return mu, sigma, pi


def log_likelihood(X, mu, sigma, pi, K):
    n = X.shape[0]
    likelihood = np.zeros(n)

    for k in range(K):
        likelihood += pi[k] * multivariate_normal.pdf(X, mean=mu[k], cov=sigma[k])

    return np.sum(np.log(likelihood))


def em_gmm(X, K, max_iter=100, tol=1e-6):
    # 初始化参数
    mu, sigma, pi = initialize_parameters(X, K)
    log_likelihood_values = []

    for i in range(max_iter):
        # E 步：计算后验概率
        gamma = e_step(X, mu, sigma, pi, K)

        # M 步：更新模型参数
        mu, sigma, pi = m_step(X, gamma, K)

        # 计算对数似然
        ll = log_likelihood(X, mu, sigma, pi, K)
        log_likelihood_values.append(ll)

        # 检查收敛
        if (
            i > 0
            and np.abs(log_likelihood_values[-1] - log_likelihood_values[-2]) < tol
        ):
            print(f"EM算法在第 {i+1} 次迭代时收敛")
            break

    return mu, sigma, pi, log_likelihood_values


# 测试代码
if __name__ == "__main__":
    # 生成二维数据，两个不同均值的高斯分布
    np.random.seed(42)
    X1 = np.random.multivariate_normal([5, 5], [[1, 0.1], [0.1, 1]], 1000)
    X2 = np.random.multivariate_normal([0, 0], [[1, -0.2], [-0.2, 1]], 300)
    X = np.vstack([X1, X2])

    # 设定高斯成分数
    K = 2
    max_iter = 100

    # 执行 EM 算法
    mu, sigma, pi, log_likelihood_values = em_gmm(X, K, max_iter)

    # 输出结果
    print("估计的均值：")
    print(mu)
    print("估计的协方差矩阵：")
    for cov in sigma:
        print(cov)
    print("估计的混合权重：")
    print(pi)

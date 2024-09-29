import numpy as np
import matplotlib.pyplot as plt

# 设置均值和协方差矩阵
mean = [0, 0]  # 均值
cov = [[1, 0], [0, 1]]  # 协方差矩阵

# 生成网格点
x = np.linspace(-3, 3, 100)
y = np.linspace(-3, 3, 100)
X, Y = np.meshgrid(x, y)

# 计算每个点的概率密度
pos = np.dstack((X, Y))
rv = np.random.multivariate_normal(mean, cov, 1000)
Z = np.exp(-0.5 * (np.linalg.norm(pos - mean, axis=2) ** 2) / (cov[0][0])) / (
    2 * np.pi * np.sqrt(np.linalg.det(cov))
)

# 绘制等高线图
plt.contour(X, Y, Z)
plt.title("2D Normal Distribution Contour")
plt.xlabel("X-axis")
plt.ylabel("Y-axis")
plt.colorbar(label="Probability Density")
plt.savefig("a.png")

# %%

import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import norm

# 定义三个正态分布的参数
params = [
    {'mean': 0, 'stddev': 1, 'weight': 0.3, 'label': 'N(0, 1)'},
    {'mean': 2, 'stddev': 0.5, 'weight': 0.5, 'label': 'N(2, 0.5)'},
    {'mean': -3, 'stddev': 1.5, 'weight': 0.2, 'label': 'N(-1, 1.5)'},
]

# 生成样本数量
num_samples = 10000000

# 抽样
samples = np.full(num_samples, 0.0)

for param in params:
    samples += np.random.normal(param['mean'], param['stddev'], num_samples)
samples /= len(params)

# 合并所有样本
# 绘图
plt.figure(figsize=(10, 6))

# 绘制所有样本的直方图
plt.hist(samples, bins=500, density=True, alpha=0.6, color='gray', label='Sample Histogram')

# 绘制每个正态分布的概率密度
x = np.linspace(-4, 5, 1000)
for param in params:
    pdf = norm.pdf(x, loc=param['mean'], scale=param['stddev'])
    plt.plot(x, pdf, label=param['label'])

# 绘制样本的平均值
# plt.axvline(mean_value, color='red', linestyle='--', label=f'Mean Value: {mean_value:.2f}')

# 图形设置
plt.title('Samples from Three Normal Distributions and Their Mean')
plt.xlabel('x')
plt.ylabel('Probability Density')
plt.axhline(0, color='black', lw=0.5, ls='--')  # 添加 x 轴
plt.legend()
plt.grid()
plt.show()

# %%

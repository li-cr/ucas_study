import numpy as np
import matplotlib.pyplot as plt
import math

# 初始化参数
R, S, a, b = 15, 0.6, 4, 2
S_values = []
Y_values = []

# 计算S和Y
while S <= 4:
    Y = (4000 * math.pi * R * R) / (
        (math.pi * R * R / S - (2 * math.pi * R / math.sqrt(2 * S)))
        * math.pow(1 + b * S / a, -a)
    )
    S_values.append(S)
    Y_values.append(Y)
    S += 0.001

# 转换为numpy数组
S_values = np.array(S_values)
Y_values = np.array(Y_values)

# 绘制点状图
plt.scatter(S_values, Y_values, label="Data Points", color="blue")

# 使用numpy进行多项式拟合，设置为3阶多项式
poly_coeff = np.polyfit(S_values, Y_values, 3)
poly_func = np.poly1d(poly_coeff)
coeffs = poly_func.c
formatted_coeffs = [f"{coeff:.10f}" for coeff in coeffs]
print("Polynomial coefficients:", formatted_coeffs)

# 绘制多项式拟合曲线
S_fit = np.linspace(min(S_values), max(S_values), 500)
Y_fit = poly_func(S_fit)
plt.plot(S_fit, Y_fit, label="Polynomial Fit (3rd degree)", color="red")

# 在图像上粘贴多项式表达式
# poly_text = f"{poly_func}"
# plt.text(0.5, 0.5, poly_text, fontsize=12, color="green", transform=plt.gca().transAxes)

# 设置图表标题和标签
plt.title("S vs Y with Polynomial Fit")
plt.xlabel("S")
plt.ylabel("Y")
plt.legend()
plt.grid(True)

# 保存图片为a.png
plt.savefig("a.png")

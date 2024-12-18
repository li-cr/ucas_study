import matplotlib.pyplot as plt
import networkx as nx

# 定义完全二叉树节点总数和叶子节点数
total_nodes = 998
leaf_nodes = 728

# 计算非叶子节点数
non_leaf_nodes = total_nodes - leaf_nodes

# 计算完全二叉树深度
depth = 1
while 2**depth - 1 < total_nodes:
    depth += 1

# 创建完全二叉树
G = nx.DiGraph()
for i in range(1, total_nodes + 1):
    left_child = 2 * i
    right_child = 2 * i + 1
    if left_child <= total_nodes:
        G.add_edge(i, left_child)
    if right_child <= total_nodes:
        G.add_edge(i, right_child)


# 手动分层布局
def calculate_positions(total_nodes, depth):
    positions = {}
    layer_nodes = 1  # 每层节点数
    current_node = 1
    y_gap = 1 / depth  # 层间间距

    for d in range(depth):
        x_gap = 1 / (layer_nodes + 1)  # 当前层节点的横向间距
        for i in range(layer_nodes):
            x = (i + 1) * x_gap
            y = 1 - d * y_gap  # 自上而下排列
            positions[current_node] = (x, y)
            current_node += 1
            if current_node > total_nodes:
                return positions
        layer_nodes *= 2

    return positions


# 计算深度和布局
positions = calculate_positions(total_nodes, depth)

# 绘制完全二叉树
plt.figure(figsize=(40, 20))
nx.draw(
    G,
    pos=positions,
    with_labels=False,
    node_size=10,
    edge_color="gray",
    node_color="blue",
    alpha=0.7,
)
plt.title("完全二叉树 (998 个节点, 728 个叶子节点)", fontsize=16)
plt.axis("off")

# 保存图像为矢量文件（SVG 格式）
output_path = "a.svg"
plt.savefig(output_path, format="svg")
# plt.show()

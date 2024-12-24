import numpy as np
import matplotlib.pyplot as plt
from PIL import Image

# 1. 加载图像
image_path = '3.jpg'  # 替换为你的图像路径
image = Image.open(image_path)
X = np.array(image).reshape(-1, 3)  # 转换为 NumPy 数组image = Image

print(X)


def compute_centroid(points):
    return np.mean(points, axis=0)


def compute_distances(data, centroids):
    distances = np.zeros((data.shape[0], centroids.shape[0]))
    for i in range(centroids.shape[0]):
        distances[:, i] = np.linalg.norm(data - centroids[i], axis=1)
    return distances


def initialize_centroids(data, k):

    n_samples, _ = data.shape
    centroids = []
    first_centroid_idx = np.random.choice(n_samples)
    centroids.append(data[first_centroid_idx])
    for _ in range(1, k):
        distances = np.array(
            [min(np.linalg.norm(x - c)**2 for c in centroids) for x in data])
        probabilities = distances / distances.sum()
        next_centroid_idx = np.random.choice(n_samples, p=probabilities)
        centroids.append(data[next_centroid_idx])

    return np.array(centroids)


def k_means(data, k, max_iters=100):
    centroids = initialize_centroids(data, k)
    labels = np.zeros(data.shape[0])
    tmp_cen = centroids.copy()

    for i in range(max_iters):
        distances = compute_distances(data, centroids)
        new_labels = np.argmin(distances, axis=1)
        if np.all(labels == new_labels):
            # print(f"Converged after {i+1} iterations.")
            break
        labels = new_labels
        for j in range(k):
            centroids[j] = compute_centroid(data[labels == j])
    return tmp_cen, centroids, labels


def get_sig_matrix(A: np.array, num):

    eigenvalues, eigenvectors = np.linalg.eigh(A)
    sorted_indices = np.argsort(eigenvalues)
    sorted_eigenvectors = eigenvectors[:, sorted_indices]

    top_eigenvectors = sorted_eigenvectors[:, :num]

    return top_eigenvectors


def gaussian_kernel(x1, x2, sigma=1.0):
    """计算高斯核相似性"""
    distance = np.linalg.norm(x1 - x2)
    return np.exp(-distance**2 / (2 * sigma**2))


def get_l_sym(X, k=5, sigma=1.0):
    n = X.shape[0]
    W = np.zeros((n, n))

    for i in range(n):
        distances = np.linalg.norm(X - X[i], axis=1)
        nearest_indices = np.argsort(distances)[1:k+1]
        for j in nearest_indices:
            W[i, j] = gaussian_kernel(X[i], X[j], sigma)
    W = (W + W.T)/2

    D = np.diag(np.sum(W, axis=1))
    L = D - W

    D_inv_sqrt = np.diag(1.0 / np.sqrt(np.diag(D)))
    L_sym = D_inv_sqrt @ L @ D_inv_sqrt

    return L_sym


def ng(data, nearst_number, sigma, eigenvectors_number=2):
    A = get_l_sym(data, k=nearst_number, sigma=sigma)
    B = get_sig_matrix(A, eigenvectors_number)

    B_tmp = np.linalg.norm(B, axis=1, keepdims=True)
    B_tmp[B_tmp == 0] = 1
    B /= B_tmp
    _, _, Z = k_means(B, 2)

    # print(f"{Z[:100]} \n{Z[100:]}")
    ans1 = np.sum(Z[:100] == 1) + np.sum(Z[100:] == 0)
    ans2 = np.sum(Z[:100] == 0) + np.sum(Z[100:] == 1)
    return max(ans1, ans2)/len(Z)


ng(X, 10, 1, 2)

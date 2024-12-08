import hashlib
import os
import requests
from concurrent.futures import ThreadPoolExecutor
import time
import psutil

# 文件下载的 URL
url = "https://ftp.ncbi.nlm.nih.gov/blast/db/FASTA/nr.gz"
# url = "https://ftp.ncbi.nlm.nih.gov/blast/db/Betacoronavirus.02.tar.gz"
# url = "https://ftp.ncbi.nlm.nih.gov/blast/db/18S_fungal_sequences.tar.gz"
# 下载文件保存的路径
# file_name = "./data/nr.gz"
file_name = "./data/nr.gz"

# 设置线程数量
threads = 10  # 可以根据带宽和机器的性能调整

size = 10 * 8 * 1024 * 1024


# 获取文件的大小
def get_file_size(url):
    response = requests.head(url)
    return int(response.headers["Content-Length"])


# 下载文件的某个块
def download_range(start, end, file_name, thread_id):
    # 获取当前文件的大小（如果文件存在）
    if os.path.exists(f"{file_name}.part{thread_id}"):
        file_size = os.path.getsize(f"{file_name}.part{thread_id}")
    else:
        file_size = 0  # 如果文件不存在，说明从头开始写
    print(f"{thread_id} {start} {file_size}")
    # 打开文件并设置偏移量（文件末尾追加）
    with open(f"{file_name}.part{thread_id}", "ab") as file:  # 使用 'ab' 模式追加
        # 如果文件已经存在，start 需要从当前文件大小开始
        start += file_size
        for st in range(start, end, size):
            en = min(end, st + size - 1)
            headers = {"Range": f"bytes={st}-{en}"}
            response = requests.get(url, headers=headers, stream=True)
            file.write(response.content)
            print(f"bytes={st / (1024 * 1024):.2f} - {(en) / (1024 * 1024):.2f}")


# 合并所有的文件块
def merge_files(file_name, num_parts):
    with open(file_name, "wb") as final_file:
        for i in range(num_parts):
            part_filename = f"{file_name}.part{i}"
            with open(part_filename, "rb") as part_file:
                final_file.write(part_file.read())
            os.remove(part_filename)  # 下载完毕后删除部分文件


# 主函数，执行多线程下载
def download_file(url, file_name, threads):
    file_size = get_file_size(url)
    part_size = file_size // threads  # 计算每个线程下载的文件块大小
    print(f"{file_size/1024/1024:.2f} {part_size}")
    # 创建一个线程池来执行下载任务
    with ThreadPoolExecutor(max_workers=threads) as executor:
        futures = []
        for i in range(threads):
            start = i * part_size
            # 最后一个线程下载到文件末尾
            end = start + part_size - 1 if i < threads - 1 else file_size - 1
            futures.append(executor.submit(download_range, start, end, file_name, i))

        # 等待所有线程完成
        for future in futures:
            future.result()

    # 合并所有文件块
    merge_files(file_name, threads)


def get_file_md5(fname):
    m = hashlib.md5()  # 创建md5对象
    with open(fname, "rb") as fobj:
        while True:
            data = fobj.read(4096)
            if not data:
                break
            m.update(data)  # 更新md5对象

    return m.hexdigest()


if __name__ == "__main__":
    # print(get_file_md5(file_name))
    # print(get_file_md5("./data/18S_fungal_sequences (1).tar.gz"))
    download_file(url, file_name, threads)
    print(get_file_md5(file_name))
    print(f"{file_name} 下载完成！")

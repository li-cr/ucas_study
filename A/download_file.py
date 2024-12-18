import hashlib
import os
import requests
from concurrent.futures import ThreadPoolExecutor
import queue

# 文件下载的 URL
# url = "https://ftp.ncbi.nlm.nih.gov/blast/db/FASTA/nr.gz"
url = "https://ftp.ncbi.nlm.nih.gov/blast/db/Betacoronavirus.02.tar.gz"
# url = "https://ftp.ncbi.nlm.nih.gov/blast/db/18S_fungal_sequences.tar.gz"
# 下载文件保存的路径
# file_name = "./data/nr.gz"
file_name = "./nr.gz"

# url = "https://ftp.pride.ebi.ac.uk/pride/data/archive/2017/08/PXD003472/QExactiveHF_D2__500ng_500ugEcoli_120min.raw"
# file_name = "./a"

# 设置线程数量
threads = 30  # 可以根据带宽和机器的性能调整
# threads = 100
# size = 1 * 1024 * 1024
size = 1024 * 1024
# size = 10 * 8 * 1024 * 1024
task_queue = queue.Queue(maxsize=threads)


# 获取文件的大小
def get_file_size(url):
    response = requests.head(url)
    return int(response.headers["Content-Length"])


# 下载文件的某个块
def download_range(thread_id):

    with open(file_name, "r+b") as file:
        while True:
            [st, en] = task_queue.get()
            # print(st, en)
            if st < 0:
                break
            headers = {"Range": f"bytes={st}-{en}"}
            response = requests.get(url, headers=headers, stream=True)
            file.seek(st)
            file.write(response.content)
            # print(f"bytes={st / (1024 * 1024):.2f} - {(en) / (1024 * 1024):.2f}")


# 主函数，执行多线程下载
def download_file(url, file_name, threads):
    file_size = get_file_size(url)
    with ThreadPoolExecutor(max_workers=threads) as executor:
        futures = []
        if os.path.exists(file_name) == False:
            with open(file_name, "w") as file:
                a = 1
        for i in range(threads):
            futures.append(executor.submit(download_range, i))

        with open(file_name, "rb") as file:
            st = 0
            while st < file_size:
                en = st + size - 1
                if en > file_size:
                    en = file_size
                file.seek(en)
                ch = file.read(1)
                if ch == b"\x00" or ch == b"":
                    task_queue.put([st, en])
                    print(st, en)
                st += size
        for i in range(threads):
            task_queue.put([-1, -1])
        for future in futures:
            future.result()


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

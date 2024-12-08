import subprocess
import queue
import threading
from concurrent.futures import ThreadPoolExecutor
import os


def deal(qu, id):
    while True:
        (index, na, va) = qu.get()
        # 定义 blastp 命令及其参数
        file_name = f"./tmp/{index:04d}"
        result_name = f"./ans/{index:04d}"
        with open(file_name, "w") as open_file:
            open_file.write(f"{na}{va}")
        blastp_command = [
            "blastp",
            "-query",
            file_name,  # 输入文件
            "-db",
            "nr",  # BLAST 数据库
            "-remote",
            "-out",
            result_name,  # 输出文件
            "-outfmt",
            "6 qseqid sseqid pident evalue qcovhsp score",  # 输出格式
        ]
        result = subprocess.run(blastp_command, capture_output=True, text=True)
        # print(result.stdout)
        if result.stderr:
            # print("Error: ", index)
            print(f"{index} : ", result.stderr)
            os.remove(result_name)
        else:
            os.remove(file_name)


qu = queue.Queue(maxsize=10)


thread_num = 10
with ThreadPoolExecutor(max_workers=thread_num) as executor:
    futures = []
    for i in range(thread_num):
        futures.append(executor.submit(deal, qu, i))

        # 打开原始文件读取
    with open("./b.fasta", "r") as infile:
        lines = infile.readlines()
    for i in range(0, len(lines), 3):
        index = int(lines[i])
        print(f"index : {index:04d}")
        qu.put((index, lines[i + 1], lines[i + 2]))

    # 等待所有线程完成
    for future in futures:
        future.result()

# 打开原始文件读取
with open("input_file.txt", "r") as infile:
    lines = infile.readlines()

# 打开输出文件写入
with open("a.txt", "w") as outfile:
    for line in lines[2:]:  # 跳过前两行
        columns = line.split()  # 假设是空格或制表符分隔的文件
        if len(columns) > 7:  # 确保至少有8列
            # 提取第A列和第H列，A是1-based索引（Python索引从0开始，所以A列是0）
            # 假设A列是第0列，H列是第7列
            output_line = f"{columns[0]}\t{columns[7]}\n"
            outfile.write(output_line)

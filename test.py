import hashlib
import math
import os
from PIL import Image, ImageDraw
import base64


# 模拟 get_num 函数，用于计算图像分段的数目
def get_num(aid, scramble_id):
    combined = aid + scramble_id
    n = ord(hashlib.md5(combined.encode()).hexdigest()[-1])

    if aid >= "268850" and aid <= "421925":
        n = n % 10
    elif aid >= "421926":
        n = n % 8

    case_map = {0: 2, 1: 4, 2: 6, 3: 8, 4: 10, 5: 12, 6: 14, 7: 16, 8: 18, 9: 20}
    return case_map.get(n, 10)


def get_scramble_id_putput_path(file_path):
    # 获取目录部分和文件名部分
    directory, filename = os.path.split(file_path)

    # 提取文件名中的数字并去掉扩展名
    number = filename.split(".")[0]

    # 格式化为 5 位数字，前面补零，并修改扩展名为 .png
    new_filename = f"{number.zfill(5)}"
    # new_FF = str(number) + ".webp"
    # new_FF = file_path
    # 组合回完整路径
    # new_file_path = os.path.join(directory, new_FF)
    new_file_path = file_path
    return new_filename, new_file_path


# 处理图像逻辑，分段打乱并重新组合
def scramble_image(image_path, aid):
    scramble_id, output_path = get_scramble_id_putput_path(image_path)
    # print(scramble_id, output_path)
    # if os.path.exists(output_path):
    # return
    # 打开图片
    img = Image.open(image_path)
    width, height = img.size

    # 获取分割数
    segments = get_num(aid, scramble_id)

    # 打开图像并获取其尺寸
    e = Image.open(image_path)
    i = e.height
    d = e.width

    # 创建一个新的画布
    new_image = Image.new("RGB", (d, i))
    draw = ImageDraw.Draw(new_image)

    # 变量初始化
    l = int(i % segments)
    r = d

    for m in range(segments):
        c = math.floor(i / segments)
        g = c * m
        w = i - c * (m + 1) - l

        if m == 0:
            c += l
        else:
            g += l

        # 将原始图像的部分绘制到新图像中
        box = (0, w, r, w + c)  # 定义裁剪区域
        region = e.crop(box)  # 裁剪出这一部分
        new_image.paste(region, (0, g))  # 将该部分粘贴到新画布上

    # 保存最终图像
    new_image.save(output_path)
    # print(f"处理后的图像已保存到: {output_path}")


# def list_files(startpath):
#     i = 0
#     for root, dirs, files in os.walk(startpath):
#         # print(f"当前目录: {root}")
#         for file in files:
#             print(file, root, dirs)
#             print(root + "\\" + file)
#             # scramble_image(root + "\\" + file, str(TTT[i]))
#         i += 1


# 示例：遍历指定目录
# list_files("PHOTO")

# # 示例调用
# image_path = ".\\PHOTO\\105\\1.webp"  # 输入图片的路径
# aid = "550430"  # aid 示例

# scramble_image(image_path, aid)

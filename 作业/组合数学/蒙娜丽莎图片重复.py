import random
from PIL import Image


# 读入图片
def load_image(image_path):
    return Image.open(image_path)


# 改变每个像素点的位置
def transform_image(image):
    width, height = image.size
    new_image = Image.new("RGB", (width, height))  # 创建一张新的空白图片
    pixels = image.load()  # 读入原图像素
    new_pixels = new_image.load()  # 新图像像素
    print(width, " ", height)
    # 初始化所有新像素为空
    for y in range(height):
        for x in range(width):
            new_pixels[x, y] = (0, 0, 0)  # 设为黑色
    mid_h, mid_w = int(height / 2), int(width / 2)
    # 遍历所有像素点
    for y in range(height):
        for x in range(width):
            # 随机移动像素到新位置，可以根据需求调整这个逻辑
            # new_x = x + random.randint(-1, 1)  # x轴的随机偏移
            # new_y = y + random.randint(-1, 1)  # y轴的随机偏移
            new_x = mid_w * (x % 2) + int(x / 2)
            new_y = mid_h * (y % 2) + int(y / 2)
            # print(x, " ", y, "   ", new_x, " ", new_y)
            # input()
            # 确保新位置在图像范围内
            if 0 <= new_x < width and 0 <= new_y < height:
                new_pixels[int(new_x), int(new_y)] = pixels[x, y]  # 把像素放在新位置
    # for y in range(height):
    # for x in range(width):
    # if new_pixels[x, y].__eq__((0, 0, 0)):
    # print(x, " ", y, "  ", new_pixels[x, y])
    return new_image


# 保存新图片
def save_image(image, output_path):
    image.save(output_path)


if __name__ == "__main__":
    input_image_path = "红底.jpg"  # 输入图片路径
    output_image_path = "output_image.png"  # 输出图片路径

    Image.open(input_image_path).resize((1500, 2000)).save(output_image_path)

    while True:
        input_image_path = "output_image.png"
        image = load_image(input_image_path)  # 读入图片
        transformed_image = transform_image(image)  # 改变像素点位置
        save_image(transformed_image, output_image_path)  # 保存新图片

        print(f"图片已保存到: {output_image_path}")
        # input()``

with open("test.txt", "rb") as file:
    # file.seek(20)
    # file.write(b"abc")
    file.seek(40)
    print(file.read(1) == b"")

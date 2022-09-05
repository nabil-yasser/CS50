from cs50 import get_int

height = 0
while height not in range(1, 9):
    height = get_int("Height: ")
for i in range(height):
    print("{0:>{1}}  {0}".format("#" * (i + 1), height))
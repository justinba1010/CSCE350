import sys

for line in sys.stdin:
    linesplit = line.split("*")
    a = int(linesplit[0])
    b = int(linesplit[1])
    print(a*b)

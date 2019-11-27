#!/usr/bin/python3
from subprocess import run, PIPE
from random import randint

testnum = int(input())
for i in range(testnum):
    a = randint(0, 2**100)
    b = randint(0, 2**100)
    result = a*b

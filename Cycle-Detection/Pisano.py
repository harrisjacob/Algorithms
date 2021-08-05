#!/usr/bin/env python3

f = open("data.txt", "w")
hold = 0
fib1 = 0
fib2 = 1
mod = int(input("Fibonacci modulo: "))

f.write("{} ".format(fib1%mod))
f.write("{} ".format(fib2%mod))

for i in range(100):
	hold = fib1+fib2
	f.write("{} ".format(hold%mod))
	fib1 = fib2
	fib2 = hold

f.write("\n")

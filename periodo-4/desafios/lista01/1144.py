n = int(input()) + 1

for x in range(1, n):
	a = x * x
	b = x * a
	print(x, a, b)
	print(x, a + 1, b + 1)

n1, n2 = input().split()

n1 = int(n1)
n2 = int(n2)
a = 1
while a <= n2:
	for x in range(0, n1):
		print(a + x, end=' ')
	print()
	a += 3

pg = 0
n = int(input())
a = n

while pg < 2:
	for i in range(2, n):
		if a % i == 0:
			break

	if i == n-1:
		pg += 1
		print(n)

	a -= 1

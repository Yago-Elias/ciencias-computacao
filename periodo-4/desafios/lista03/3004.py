n = int(input())

for i in range(n):
	c = input().split()
	c = list(map(int, c))

	if c[0] > c[1]:
		c[0], c[1] = c[1], c[0]
	if c[2] > c[3]:
		c[2], c[3] = c[3], c[2]

	if c[0] < c[2] and c[1] < c[3]:
		print('S')
	else:
		print('N')

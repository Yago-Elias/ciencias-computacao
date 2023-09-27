t = c = 0

while True:
	if input() == '-1':
		break
	n = input().split()
	n = list(map(int, n))

	for v in n:
		t += v
		if t % 100 == 0:
			c += 1
	
	print(c)
	t = c = 0

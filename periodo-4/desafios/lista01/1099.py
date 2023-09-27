t = int(input())

for x in range(t):
	s = 0
	n1, n2 = int(input()), int(input())

	if n1 > n2:
		a = n1
		n1, n2 = n2 + 1, a
	else:
		n1 += 1

	for x in range(n1, n2):
		if x % 2 == 1:
			s += x;

	print(s)

while True:
	try:
		s, va, vb = input().split()
	except EOFError:
		break
	else:
		s, va, vb = int(s), int(va), int(vb)

		if vb > va:
			print('impossivel')
		else:
			print('{:.2f}'.format(s / (va - vb)))

from math import ceil, floor

x, y = int(input()), int(input())

r = 0

if abs(x) == abs(y):
	r = 0
else:
	if x > y:
		a = x
		x, y = y, a

	if x * y < 0:
		nx = floor(abs(x) / 2)
		ny = floor(abs(y) / 2)

		if x < 0:
			r = (ny + nx) * (ny - nx)
		else:
			r = (nx + ny) * (nx - ny)
	else:
		nx = ceil(x / 2)
		ny = floor(y / 2)
		r = (ny + nx) * (ny - nx)

print(r)

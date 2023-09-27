def mdc(a, b):
	if b == 0:
		return a
	else:
		return mdc(b, a % b)


def mmc(a, b):
	return a * b // mdc(a, b)


n = int(input())
k = n + 1

for i in range(n+1, 2*n+1):
	k = mmc(k, i)
print(k)

"""
import math
<...>
for i in range(n+1, 2*n+1):
	k = math.lcm(int(k), 1)
print(k)

"""

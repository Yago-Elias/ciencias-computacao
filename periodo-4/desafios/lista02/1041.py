x, y = input().split(' ')
x, y = float(x), float(y)

o = 0.0
c = 'Origem'

if x != o or y != o:
	if x > o and y > o:
		c = 'Q1'
	elif x < o and y > o:
		c = 'Q2'
	elif x < o and y < o:
		c = 'Q3'
	elif x > o and y < o:
		c = 'Q4'
	elif x == o:
		c = 'Eixo Y'
	else:
		c = 'Eixo X'

print(c)

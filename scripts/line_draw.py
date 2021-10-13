from matplotlib import pyplot as plt

def	line(x):
	return -2.5*x + 13/2

def	line_1(x):
	return (2/5)*x + 18/5

def	line_2(x):
	return (1/4)*x + 23/4

def	line_3(x):
	return (3/5)*x + 1

def	line_4(x):
	return (1/7)*x - 2

x = []
y = []
for i in range(-1, 10, 1):
	x.append(i)
	y.append(line_2(i))


print(x)
print(x)

plt.plot(x, y)
# plt.plot(1, 4, 'o')
plt.plot(-1, 7, 'o', "RED")
plt.plot(0, 0, 'o', "YELLOW")
plt.show()
	
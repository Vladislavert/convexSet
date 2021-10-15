from matplotlib import pyplot as plt

def readFile(filename):
	fdata_x = list()
	fdata_y = list()
	with open(filename, "r") as f:
		data = f.readline()
		fdata_x = list(map(float, data.split()))
		data = f.readline()
		fdata_y = list(map(float, data.split()))
	return fdata_x, fdata_y

set_x, set_y = readFile('../build/points')
hull_x, hull_y = readFile('../build/points_res')

for i in range(0, len(set_x)):
	plt.plot([set_x[i]], [set_y[i]], 'o', color='r')

plt.plot(hull_x, hull_y, 'b')
plt.grid()
plt.xlabel('X')
plt.ylabel('Y')
plt.title('Convex hull')
plt.show()

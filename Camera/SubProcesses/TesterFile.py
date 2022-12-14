import finishedPath as fp
import random
import matplotlib.pyplot as plt


path = fp.finishedPath()
path.printPoints()

# input
for _ in range(100):
    path.X.append(random.randint(0, 100))
    path.Y.append(0)
    path.Z.append(random.randint(0, 100))

path.printPoints()

# plot
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.scatter(path.X, path.Y, path.Z, c='r', marker='o')
ax.set_xlabel('X Label')
ax.set_ylabel('Y Label')
ax.set_zlabel('Z Label')

# save to png
plt.savefig('test.png')

# show
plt.show()

import random
import sys

# Number of instances to generate
numInstances = int(sys.argv[1])

for i in range(1, numInstances + 1):
    
  # Number of vertices
  n = random.randint(1, 2000)
  
  # Number of edges
  m = random.randint(n, n*2 - 1)

  # Minimum weight
  minWeight = random.randint(-100, 100)

  # Maximum weight
  maxWeight = random.randint(minWeight, 1000)

  file = open("DirectedWeightedGraph" + str(i) + ".mtx", "w")

  file.write(str(n) + " " + str(m) + "\n")

  edges = []
  for i in range(1, n + 1):
      for j in range(i + 1, n + 1):
          edges.append((i, j))

  random.shuffle(edges)

  for i in range(m):
      file.write(str(edges[i][0]) + " " + str(edges[i][1]) + " " + str(random.randint(minWeight, maxWeight)) + "\n")

  file.close()



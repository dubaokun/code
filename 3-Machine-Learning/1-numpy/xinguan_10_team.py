import numpy as np

min=100000
P=0.008
k=1
K=0
for i in range(1000):
  EX=1-np.power(1-P,k) + 1/k
  if EX < min:
    min = EX
    K=k
  k+=1

print(min)
print(K)

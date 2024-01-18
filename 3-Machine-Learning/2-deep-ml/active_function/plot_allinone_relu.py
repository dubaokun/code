import matplotlib.pyplot as plt
import numpy as np

x=np.linspace(-2,2,100)
y=x*(x>0)
plt.xlabel('x')
plt.ylabel('y')
plt.title("Relu function and its derivative image")
plt.plot(x,y,color='r',label="Relu")

x=np.linspace(-2,0)
y=np.linspace(0,0)
plt.plot(x,y,color='b')

x=np.linspace(0,2)
y=np.linspace(1,1)
plt.plot(x,y,color='b',label="derivative")

plt.legend()
plt.show()

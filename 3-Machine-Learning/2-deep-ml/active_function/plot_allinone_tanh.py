import matplotlib.pyplot as plt
import numpy as np


x=np.linspace(-10,10,100)
y=(1-np.exp(-2*x))/(1+np.exp(-2*x))
plt.xlabel('x')
plt.ylabel('y')
plt.title("Tanh function and its derivative image")
plt.plot(x,y,color='r',label='Tanh')
y=1-pow((1-np.exp(-2*x))/(1+np.exp(-2*x)),2)
plt.plot(x,y,color='b',label='derivative')
plt.legend()
plt.show()

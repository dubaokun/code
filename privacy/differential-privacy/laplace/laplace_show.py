import matplotlib.pyplot as plt
import numpy as np
 
def laplace_function(x, b):
    result = (1/(2*b)) * np.e**(-1*(np.abs(x)/b))
    return result

#在-100到100之间等间隔的取10000个数
x = np.linspace(-100,100,10000)
y1 = [laplace_function(x_,0.5) for x_ in x]
y2 = [laplace_function(x_,1) for x_ in x]
y3 = [laplace_function(x_,2) for x_ in x]
 
 
plt.plot(x,y1,color='r',label='u:0|b:0.5')
plt.plot(x,y2,color='g',label='u:0|b:1')
plt.plot(x,y3,color='b',label='u:0|b:2')
plt.title("Laplace distribution")
plt.legend()
plt.show()

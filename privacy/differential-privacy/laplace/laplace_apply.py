import numpy as np
 
 # 计算基于拉普拉斯分布的噪声
def laplace_noisy_count(sensitivety,epsilon):
    beta = sensitivety/epsilon
    u1 = np.random.random()
    u2 = np.random.random()
    # 计算分布函数
    if u1 <= 0.5:
        n_value = -beta*np.log(1.-u2)
    else:
        n_value = beta*np.log(u2)
    print(n_value)
    return n_value

# 计算基于拉普拉斯加噪的混淆值
def laplace_mech(data, sensitivety, epsilon):
    for i in range(len(data)):
        data[i] += laplace_noisy_count(sensitivety,epsilon)
    return data
 
# 基于拉普拉斯分布的特性，如果想要分布震荡较小，需要将隐私预算epsilon的值设置较大
if __name__ =='__main__':
    data = [1.,2.,3.]
    sensitivety = 1
    epsilon = 10
    data_noisy = laplace_mech(data, sensitivety, epsilon)
    for j in data_noisy:
        print(j)

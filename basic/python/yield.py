#encoding:UTF-8  
def yield_test(n):  
    for i in range(n):  
        yield call(i)     # 它会立即把call(i)输出，成果拿出来后才会进行下一步，所以 i, ',' 会先执行
        print("function i=",i)     # 后执行
    #做一些其它的事情      
    print("do something.")        #  待执行，最后才执行一遍
    print("end.")  
  
def call(i):  
    return i*2  
  
#使用for循环  
for i in yield_test(5):  
    print( "Return i = " , i)   # 这里的 i 是 call(i)

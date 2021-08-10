#encoding:UTF-8  

def yield_test(n):  
    for i in range(n):  
        yield call(i)
        print("function i=",i)
    print("do something.")
    print("end.")  
  
def call(i):  
    return i*2  
  
for i in yield_test(5):  
    print( "Return i = " , i)

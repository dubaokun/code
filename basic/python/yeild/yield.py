def foo():
    print("starting...")
    while True:
        res = yield 4
        print("res:",res)

#g = foo()
#print(next(g))
#print("*"*20)
#print(next(g))
for index in foo():
  print index
  foo()

# main.py
import foo

a =getattr(foo,'name',"default value")
# "hello"
print "====="
#a()

getattr(foo,'test',None)
# None

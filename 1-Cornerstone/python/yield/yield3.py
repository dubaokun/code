def p():
    print "aaaaaa"
def foo():
    print("starting...")
    while True:
        yield p()
foo()
foo()

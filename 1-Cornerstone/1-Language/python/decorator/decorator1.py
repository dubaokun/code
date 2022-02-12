import functools

def outer(func):
    @functools.wraps(func)
    def inner(*args, **kwargs):
        print("before...")
        func(*args, **kwargs)
        print("after...")

    return inner

@outer
def add(a, b):
    print(a + b)

add(1, 2)

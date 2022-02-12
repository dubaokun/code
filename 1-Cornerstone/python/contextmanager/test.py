import contextlib
import time

@contextlib.contextmanager
def timeit():
    start = time.time()
    yield
    end = time.time()
    usedTime = (end - start) * 1000
    print 'Use time %d ms' % usedTime

with timeit():
    time.sleep(1)

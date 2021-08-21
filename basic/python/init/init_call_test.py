class X(object):
	def __init__(self, a, b, range):
		self.a = a
		self.b = b
		self.range = range
	def __call__(self, a, b):
		self.a = a
		self.b = b
    print('__call__ with ({}, {)）'.format(self.a, self.b))

xInstance = X(1, 2, 3)
print("===============")
xInstance(3,4)

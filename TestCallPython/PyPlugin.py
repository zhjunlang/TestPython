
#!/usr/bin/python

import string

class MyClass:
	def HelloWorld(self):
		print 'Hello World'
		
class SecondClass:
	def invoke(self, obj):
		obj.HelloWorld()
		
def HelloWorld(strName):
	print 'Hello', strName
		
def Add(a, b, c):
	return a + b + c
	
def AddMult(a, b):
	"""
	"""
	print 'in Function AddMult...'
	print a
	print b
	return a+b, a*b
	
def StringToUpper(strSrc):
	return string.upper(strSrc)
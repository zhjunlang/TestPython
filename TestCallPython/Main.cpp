
#include <iostream>
#include "Python.h"

#pragma comment(lib,"python27.lib")


int main()
{
	Py_Initialize();

	if (!Py_IsInitialized())
	{
		std::cout<<"Py_Initialize Failed!\n";
		return -1;
	}

	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./')");
	PyRun_SimpleString("print 'Test Call Python file'");

	PyObject* pName = PyString_FromString("PyPlugin");
	PyObject* pModule = PyImport_Import(pName);
	if(!pModule)
	{
		std::cout<<"Can`t find PyPlugin.py\n";
		return -1;
	}

	PyObject* pDict = PyModule_GetDict(pModule);
	if (!pDict)
	{
		std::cout<<"PyModule_GetDict() error\n";
		return -1;
	}

	PyObject* pFunc = PyDict_GetItemString(pDict, "AddMult");
	if (!pFunc || !PyCallable_Check(pFunc))
	{
		std::cout<<"Can`t find function [AddMult]\n";
		return -1;
	}

	PyObject* pArgs = Py_BuildValue("ii", 12, 14);
	PyObject* pRet = PyEval_CallObject(pFunc, pArgs);

	int a = 0;
	int b = 0;
	if (pRet && PyArg_ParseTuple(pRet, "ii", &a, &b))
	{
		std::cout<<"Function[AddMult] call successful a + b = "<<a<<", a * b = "<<b<<"\n";
		pRet = NULL;
	}
	
	if (pArgs) Py_DECREF(pArgs);
	if (pFunc) Py_DECREF(pFunc);

	pFunc = PyDict_GetItemString(pDict, "HelloWorld");
	if (!pFunc || !PyCallable_Check(pFunc))
	{
		std::cout<<"Can`t find function [HelloWorld]\n";
		return -1;
	}

	pArgs = Py_BuildValue("(s)", "zcwtop");
	pRet = PyEval_CallObject(pFunc, pArgs);


	if (pArgs) Py_DECREF(pArgs);
	if (pFunc) Py_DECREF(pFunc);
	if (pRet) Py_DECREF(pRet);
	if (pDict) Py_DECREF(pDict);
	if (pModule) Py_DECREF(pModule);
	if (pName) Py_DECREF(pName);

	Py_Finalize();

	return -1;
}
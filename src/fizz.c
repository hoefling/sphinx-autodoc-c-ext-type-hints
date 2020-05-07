/**
 * This is a dummy Python extension, identical to writing
 *
 *     class Buzz:
 *         def fuzz(self, x):
 *             print(x)
 */

#include <Python.h>
#include "structmember.h"

// some dummy class
typedef struct {
    PyObject_HEAD
} Buzz;

static void Fizz_Buzz_dealloc(Buzz* self) {
    Py_TYPE(self)->tp_free(self);
}

static PyObject * Buzz_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
    Buzz *self;

    self = (Buzz *)type->tp_alloc(type, 0);
    return (PyObject *)self;
}

static int Buzz_init(Buzz *self, PyObject *args, PyObject *kwds) {
    return 0;
}

static PyMemberDef Buzz_members[] = {
    {NULL}  /* Sentinel */
};

static const char Buzz_fuzz__doc__[] = \
    "Takes a string and prints it (such func wow).\n\n"\
    ":param str x: a string to print\n"\
    ":return: :data:`None`\n";

static PyObject * Buzz_fuzz(PyObject* self, PyObject *args) {
    const char* x = NULL;
    if (!PyArg_ParseTuple(args, "s", &x))
        return NULL;
    printf("----- Buzz.fuzz() got %s -----\n", x);
    Py_RETURN_NONE;
}

static PyMethodDef Buzz_methods[] = {
    {"fuzz", (PyCFunction)Buzz_fuzz, METH_VARARGS, Buzz_fuzz__doc__},
    {NULL}  /* Sentinel */
};

// see https://docs.python.org/3/c-api/typeobj.html
static PyTypeObject fizz_Fizz_BuzzType = {
    PyObject_HEAD_INIT(NULL)
    "fizz.Buzz",                                /*tp_name*/
    sizeof(Buzz),                               /*tp_basicsize*/
    0,                                          /*tp_itemsize*/
    (destructor)Fizz_Buzz_dealloc,              /*tp_dealloc*/
    0,                                          /*tp_print*/
    0,                                          /*tp_getattr*/
    0,                                          /*tp_setattr*/
    0,                                          /*tp_compare*/
    0,                                          /*tp_repr*/
    0,                                          /*tp_as_number*/
    0,                                          /*tp_as_sequence*/
    0,                                          /*tp_as_mapping*/
    0,                                          /*tp_hash */
    0,                                          /*tp_call*/
    0,                                          /*tp_str*/
    0,                                          /*tp_getattro*/
    0,                                          /*tp_setattro*/
    0,                                          /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,   /*tp_flags*/
    "Buzz object",                              /* tp_doc */
    0,                                          /* tp_traverse */
    0,                                          /* tp_clear */
    0,                                          /* tp_richcompare */
    0,                                          /* tp_weaklistoffset */
    0,                                          /* tp_iter */
    0,                                          /* tp_iternext */
    Buzz_methods,                               /* tp_methods */
    Buzz_members,                               /* tp_members */
    0,                                          /* tp_getset */
    0,                                          /* tp_base */
    0,                                          /* tp_dict */
    0,                                          /* tp_descr_get */
    0,                                          /* tp_descr_set */
    0,                                          /* tp_dictoffset */
    (initproc)Buzz_init,                        /* tp_init */
    0,                                          /* tp_alloc */
    Buzz_new,                                   /* tp_new */
};

// python vtable
static PyMethodDef FizzMethods[] = {
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

// python module definition
static struct PyModuleDef fizzmodule = {
    PyModuleDef_HEAD_INIT, "fizz", "Dummy module for testing.", -1, FizzMethods
};

// register module namespace
PyMODINIT_FUNC PyInit_fizz(void) {
    PyObject *module;

    module = PyModule_Create(&fizzmodule);
    if (module == NULL)
        return NULL;

    if (PyType_Ready(&fizz_Fizz_BuzzType) < 0)
        return NULL;

    Py_INCREF(&fizz_Fizz_BuzzType);
    PyModule_AddObject(module, "Buzz", (PyObject *)&fizz_Fizz_BuzzType);
    return module;
}

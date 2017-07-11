#include <pybind11/pybind11.h>
#include <string>
#include <iostream>
#include <functional>

namespace py = pybind11;
using namespace std::placeholders;

typedef int (*callback)(int, int);
typedef std::function<int(int, int)> functor_t;

struct Class {
  Class(unsigned long long addr) : func((callback)addr) {}
  int wrapper(int a, int b) { return func(a, b); }
  functor_t func;
};


PYBIND11_MODULE(foo, m) {
  py::class_<Class>(m, "Foo")
    .def(py::init<unsigned long long>())
    .def("call", &Class::wrapper)
    ;
}

/*
 * Demo of default arguments.
 * http://pybind11.readthedocs.io/en/master/advanced/cast/index.html
 */
#include <pybind11/pybind11.h>

namespace py = pybind11;

int add(int i = 10, int j = 20) {
  return i + j;
}

PYBIND11_MODULE(foo, m) {
  m.def("add", &add, "add two numbers", py::arg("i") = 10, py::arg("j") = 20);
}

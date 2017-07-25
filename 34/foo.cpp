#include <pybind11/pybind11.h>
#include <iostream>
#include <vector>

namespace py = pybind11;

struct Foo {
  void print(int a, bool inverse = false) {
    std::cout << "a: " << a << " inverse: " << inverse << std::endl;
  }
};

PYBIND11_MODULE(foo, m) {
  py::class_< Foo >(m, "Foo")
    .def(py::init<>())
    .def("print", &Foo::print, py::arg("a"), py::arg("inverse") = false)
  ;
}

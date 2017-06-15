/*
 * Demo of keyword arguments.
 */
#include <pybind11/pybind11.h>
#include <string>
#include <iostream>

namespace py = pybind11;

int add(int i, int j) {
  std::cout << "i: " << i << " j: " << j << std::endl;
  return i + j;
}

PYBIND11_MODULE(foo, m) {
  std::string doc = "A function which adds two arguments";
  m.doc() = "Pybind11 example of keyword argument. We need to pass i and j";
  m.def("add", &add, doc.c_str(), py::arg("i"), py::arg("j"));
}

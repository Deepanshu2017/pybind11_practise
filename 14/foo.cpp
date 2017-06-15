#include <pybind11/pybind11.h>
#include <iostream>

namespace py = pybind11;

void generic(py::args args, py::kwargs kwargs) {
  for(auto item : args)
    std::cout << std::string(py::str(item)) << " ";
  std::cout << std::endl;

  for (auto item : kwargs) {
    std::cout << "key: "  << std::string(py::str(item.first)) << ", " << "item: " << std::string(py::str(item.second)) << std::endl;
  }
}

PYBIND11_MODULE(foo, m) {
  m.def("gen", &generic);
}

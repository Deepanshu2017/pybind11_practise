#include <pybind11/pybind11.h>
#include <iostream>

void print() {
  std::cout << "42\nAnswer to Life, the Universe and Everything!" << std::endl;
}

PYBIND11_MODULE(hello, m) {
  m.def("print", &print);
}

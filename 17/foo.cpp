#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <iostream>
#include <vector>

namespace py=pybind11;

void print(std::vector<int>& vec) {
  for(auto iter : vec)
    std::cout << iter << " ";
  std::cout << std::endl;
}

PYBIND11_MODULE(foo, m) {
  m.def("print", &print);
}

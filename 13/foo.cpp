#include <pybind11/pybind11.h>
#include <iostream>

namespace py = pybind11;

struct Pet {
  static void speak() { std::cout << "Woof!" << std::endl; }
  ~Pet() { std::cout << "Destructor" << std::endl; }
};

Pet& fun() {
  static Pet p;
  return p;
}

PYBIND11_MODULE(foo, m) {
  py::class_<Pet>(m, "Pet")
    .def("speak", &Pet::speak)
    ;
  m.def("fun", &fun, py::return_value_policy::move);
}

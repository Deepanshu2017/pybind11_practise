#include <pybind11/pybind11.h>

namespace py = pybind11;

struct Pet {
  std::string name;
  int age;
  Pet(std::string& name) : name(name) {}
  Pet(int age) : age(age) {}
};

PYBIND11_MODULE(foo, m) {
  py::class_<Pet>(m, "Pet")
    .def(py::init<std::string&>())
    .def(py::init<int>())
    .def_readwrite("name", &Pet::name)
    .def_readwrite("age", &Pet::age)
    ;
}

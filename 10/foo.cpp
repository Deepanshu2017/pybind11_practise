#include <pybind11/pybind11.h>

namespace py = pybind11;

struct Pet {
  Pet(const std::string &name, int age) : name(name), age(age) {}
  void set(int age) {
    this->age = age;
  }
  void set(std::string& name) {
    this->name = name;
  }
  std::string name;
  int age;
};

PYBIND11_MODULE(foo, m) {
  py::class_<Pet>(m, "Pet")
    .def(py::init<const std::string&, int>())
    .def("set", (void (Pet::*)(int)) &Pet::set, "Set the age of Pet")
    .def("set", (void (Pet::*)(std::string&)) &Pet::set,  "Set the name of Pet")
    ;
}

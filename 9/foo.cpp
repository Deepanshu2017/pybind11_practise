#include <pybind11/pybind11.h>

namespace py = pybind11;

struct Pet {
  std::string name;
  Pet(const std::string& name) : name(name) {}
};

struct Dog : public Pet {
  Dog(const std::string& name) : Pet(name) {}
  std::string bark() {
    return "Woof";
  }
};

PYBIND11_MODULE(foo, m) {
  py::class_<Pet> pet(m, "Pet");
  pet.def(py::init<const std::string&>())
    .def_readwrite("name", &Pet::name)
    ;

  py::class_<Dog>(m, "Dog", pet)
    .def(py::init<const std::string&>())
    .def("bark", &Dog::bark)
    ;

}

#include <pybind11/pybind11.h>

namespace py = pybind11;

struct Pet {
  enum Kind {
    Dog = 1,
    Cat
  };
  Pet(const std::string& name, Kind type) : name(name), type(type) {}
  std::string name;
  Kind type;
};


PYBIND11_MODULE(foo, m) {
  py::class_<Pet> pet(m, "Pet");

  pet.def(py::init<const std::string&, Pet::Kind>())
    .def_readwrite("name", &Pet::name)
    .def_readwrite("type", &Pet::type)
    ;

  py::enum_<Pet::Kind>(pet, "Kind", py::arithmetic())
    .value("Dog", Pet::Kind::Dog)
    .value("Cat", Pet::Kind::Cat)
    .export_values()
    ;
}

#include <pybind11/pybind11.h>
#include <string>

namespace py = pybind11;

struct Pet {
  std::string name;
  Pet(const std::string& name) : name(name) {}
  void setName(const std::string& name) {
    this->name = name;
  }
  const std::string& getName() const {
    return name;
  }
};

PYBIND11_MODULE(foo, m) {
  py::class_<Pet>(m, "Pet")
    .def(py::init<const std::string&>())
    //.def_readwrite("name", &Pet::name)
    //.def_readonly("name", &Pet::name)
    .def_property("name", &Pet::getName, &Pet::setName)
    //.def_property_readonly("name", &Pet::getName)
    // http://pybind11.readthedocs.io/en/master/advanced/classes.html#static-properties
    ;
}

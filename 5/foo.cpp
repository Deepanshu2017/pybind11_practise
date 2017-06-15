#include <pybind11/pybind11.h>
#include <string>

namespace py = pybind11;

struct Pet {
  Pet(const std::string& name) : name(name) {}
  void setName(std::string& name) { this->name = name; }
  std::string& getName() { return name; }
  static std::string getClassName() { return "Pet"; }
  std::string name;
};

PYBIND11_MODULE(foo, m) {
  py::class_<Pet>(m, "Pet")
    .def(py::init<const std::string &>())
    .def("set_name", &Pet::setName, py::arg("name") = "Deepu")
    .def("get_name", &Pet::getName)
    .def_static("get_class_name", &Pet::getClassName)
    .def("__repr__", [](const Pet& a) { return "<example.Pet named '" + a.name +  "'>"; } )
    ;
}

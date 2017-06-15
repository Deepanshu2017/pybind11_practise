#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(foo, m) {
  m.attr("the_answer") = 42;
  py::object world = py::cast("world");
  m.attr("what") = world;
}

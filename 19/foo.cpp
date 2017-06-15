#include <pybind11/pybind11.h>

namespace py=pybind11;

int change(int* a) {
  *a *= 10;
  return 42;
}

PYBIND11_MODULE(foo, m) {
  m.def("c", [](int *i) { int rv = change(i); return std::make_tuple(rv, *i); });
}

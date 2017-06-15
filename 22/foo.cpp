#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

namespace py=pybind11;

PYBIND11_MAKE_OPAQUE(std::vector<double>);


void function(std::size_t size, double* a) {
  for (std::size_t i = 0; i < size; ++i)
    a[i] += 42;
}

void wrapper(std::vector<double>& vec) {
  function(vec.size(), vec.data());
}


PYBIND11_MODULE(foo, m) {
  py::bind_vector<std::vector<double>>(m, "DVector");
  m.def("function", &wrapper);
}

#include "foo.h"

PYBIND11_MODULE(foo, m) {
  py::class_< fWrapper<1000> >(m, "fw")
    .def(py::init<std::array<double, 1000>const&, unsigned long long>())
    .def(py::init<py::array_t<double, py::array::c_style>&, unsigned long long>())
    .def("__call__", [](fWrapper<1000> &f, double x) {
        f(&x);
      }, py::is_operator())
    .def("__call__", [](fWrapper<1000> &f, py::array_t<double, py::array::c_style>& arr, double x) {
        f(arr, &x);
      }, py::is_operator())
    .def("__call__", [](fWrapper<1000> &f, std::array<double, 1000>& arr, double x) {
        f(arr, &x);
      }, py::is_operator())
    ;
}

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py=pybind11;

PYBIND11_MAKE_OPAQUE(std::vector<double>);

void doSomething(int const n, double* a) {
  for (std::size_t i = 0; i < n; ++i)
    a[i] += 42.0;
}

void add42(std::vector<double>& vec) {
  doSomething(vec.size(), vec.data());
}

PYBIND11_MODULE(foo, m) {
  py::class_<std::vector<double>>(m, "DVector")
    .def(py::init<>())
    .def("pop_back", &std::vector<double>::pop_back)
    /* There are multiple versions of push_back(), etc. Select the right ones. */
    .def("push_back", (void (std::vector<double>::*)(const double &)) &std::vector<double>::push_back)
    .def("__len__", [](const std::vector<double> &v) { return v.size(); })
    .def("__iter__", [](std::vector<double> &v) {
	return py::make_iterator(v.begin(), v.end());
      }, py::keep_alive<0, 1>());
  m.def("add", &add42);
}

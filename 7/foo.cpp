#include <pybind11/pybind11.h>

namespace py = pybind11;

struct Hydra {
  double para;
  Hydra(const double para) : para(para) {}
  double getPara() {
    return para;
  }
};


PYBIND11_MODULE(foo, m) {
  py::class_<Hydra>(m, "Hydra", py::dynamic_attr())
    .def(py::init<double>())
    .def_readwrite("para", &Hydra::para)
    ;
}

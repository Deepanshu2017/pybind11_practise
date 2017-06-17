#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>


namespace py = pybind11;

int func(std::function<double(unsigned int, std::vector<double>, double*)> &f) {
  int a = 10;
  double x = 42.0;
  std::vector<double> vec = {1.0, 2.0, 3.0, 4.0};
  return f(a, vec, &x);
}


PYBIND11_MODULE(foo, m) {
  m.def("fw", &func);
}

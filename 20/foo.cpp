#include <pybind11/pybind11.h>
#include <pybind11/functional.h>

namespace py=pybind11;

int func_callback_stateless(std::function<double(unsigned int, double*, double*)> &f) {
  int a = 10;
  double b = 5.95, c = 5.99;
  return f(a, &b, &c);
}

std::function<int(int)> func_ret_stateful(const std::function<int(int)> &f) {
  return [f] (int i) {
    return f(i) + 1;
  };
}

py::cpp_function func_cpp() {
  return py::cpp_function([] (int i) { return i + 1; },
			  py::arg("number")
			  );
}

double wierd(unsigned int n, double* a, double *b) {
  double d = (*a) * (*b);
  *a = 100.0;
  return d;
}

double wierd3(unsigned int n, double a, double b) {
  return a * b;
}

double wierd2(unsigned int n, double& a, double& b) {
  double d = (a) * (b);
  a = 100.0;
  return d;
}

PYBIND11_MODULE(foo, m) {
  m.def("func_arg", &func_callback_stateless);
  m.def("func_ret", &func_ret_stateful);
  m.def("func_cpp", &func_cpp);
  m.def("w", &wierd);
  m.def("w2", &wierd2);
}

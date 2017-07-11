#include <pybind11/pybind11.h>
#include <string>
#include <iostream>
#include <functional>

namespace py = pybind11;

int add(int i, int j) {
  std::cout << "i: " << i << " j: " << j << std::endl;
  return i + j;
}

int add2(int (*callback)(int, int)) {
  return callback(5, 2);
}

int add3(std::function<int(int, int)>* f) {
  return (*f)(5, 2);
}

int add6(unsigned long long addr) {
  using namespace std::placeholders;
  typedef int (*callback)(int, int);
  typedef std::function<int(int, int)> functor_t;

  callback _callback = (callback)addr;
  std::cout << (*_callback)(4, 5) << std::endl;
  functor_t f = std::bind(_callback, _1, _2);
  std::cout << f(4, 6) << std::endl;
  return 42;
}

PYBIND11_MODULE(foo, m) {
  //  m.def("add", &add, doc.c_str(), py::arg("i"), py::arg("j"));
  m.def("add2", &add2);
  m.def("add3", &add3);
  m.def("add6", &add6);
}

#include <pybind11/pybind11.h>

namespace py=pybind11;

template <typename T>
T square(T t) { return t * t; }


template <typename T>
double power_sum(T t) { return t; }


template <typename T, typename... Rest>
double power_sum(T t, Rest... rest) {
  return t + power_sum(square(rest)...);
}

PYBIND11_MODULE(foo, m) {
  
}

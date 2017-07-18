#ifndef FOO_H
#define FOO_H

#include <pybind11/pybind11.h>
#include <string>
#include <iostream>

namespace py = pybind11;

template<long long N, class impl>
struct fbase {
  fbase() = delete;

  fbase(long long var) {
    this->var = var;
  }
  
  inline long long operator() () {
    return static_cast<impl*>(this)->eval(N, var);
  }

  long long var;
  
};


template<long long N>
struct multiply : public fbase<N, multiply<N> > {
  multiply() = delete;

  multiply(long long multiple) : fbase<N, multiply<N>>(multiple) {}
  
  long long eval(long long first, long long second) {
    return first * second;
  }
  
};


template<long long N>
struct divide : public fbase<N, divide<N> > {
  divide() = delete;

  divide(long long divident) : fbase<N, divide<N>>(divident) {}
  
  long long eval(long long first, long long second) {
    if (second == 0)
      return 0;
    return first / second;
  }
  
};

template<long long N>
struct add : public fbase<N, add<N> > {
  add() = delete;

  add(long long adder) : fbase<N, add<N>>(adder) {}
  
  long long eval(long long first, long long second) {
    return first + second;
  }
  
};

template<long long N>
struct subtract : public fbase<N, subtract<N> > {
  subtract() = delete;

  subtract(long long subtracter) : fbase<N, subtract<N>>(subtracter) {}
  
  long long eval(long long first, long long second) {
    return first - second;
  }
  
};

template<typename cls>
void register_base(std::string name, const pybind11::module& m) {
  py::class_< cls >(m, name.c_str())
    .def(py::init<long long>())
    .def("__call__", [](cls &f) {
	return f();
      }, py::is_operator())
    ;
}

#endif

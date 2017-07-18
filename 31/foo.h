#ifndef FOO_H
#define FOO_H

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <pybind11/functional.h>
#include <array>
#include <iostream>

namespace py = pybind11;

typedef double (*function_t) (unsigned int, double*, double*);
typedef std::function<double(unsigned int, double*, double*)> functor_t;

template<typename FunctorType, typename ReturnType, unsigned int N>
struct fbase {
  fbase() = delete;

  fbase(std::initializer_list<double> const& list) {
    std::cout << "calling initializer_list" << std::endl;
    for (size_t i = 0; i < N; ++i) {
      fPars[i] = *(list.begin() + i);
    }
  }

  fbase(std::array<double, N>const& arr) {
    std::cout << "calling std::array" << std::endl;
    for (unsigned i = 0; i != arr.size(); ++i)
      fPars[i] = arr[i];
  }

  fbase(py::array_t<double, py::array::c_style>& arr) {
    std::cout << "calling py::array_t" << std::endl;
    auto buffer = arr.request();
    double* ptr = (double*)buffer.ptr;
    
    for (size_t i = 0; i != buffer.shape[0]; ++i)
      fPars[i] = *(ptr + i);
  }

  fbase(fbase<FunctorType, ReturnType, N>const& other) {
    std::cout << "calling copy constructor" << std::endl;
    for (size_t i = 0; i < N; ++i)
      this->fPars[i] = other.fPars[i];
  }

  template <typename T>
  inline ReturnType operator() (T* x) {
    std::cout << "calling eval empty" << std::endl;
    return static_cast<FunctorType*>(this)->eval(N, fPars, x);
  }

  template <typename T>
  inline ReturnType operator() (std::array<double, N>& fPars, T* x) {
    std::cout << "calling eval std::array" << std::endl;
    return static_cast<FunctorType*>(this)->eval(N, fPars.begin(), x);
  }
  
  template <typename T>
  inline ReturnType operator() (py::array_t<double, py::array::c_style>& fPars, T* x) {
    std::cout << "calling eval py::array" << std::endl;
    auto buf = fPars.request();
    return static_cast<FunctorType*>(this)->eval(N, (double*)buf.ptr, x);
  }
  
  double fPars[N];
  
};


template<unsigned int N>
struct fWrapper : public fbase<fWrapper<N>, double, N> {
  fWrapper() = delete;

  fWrapper(std::array<double, N>const& arr, const unsigned long long addr) : fbase<fWrapper<N>, double, N>(arr), fFunctor((function_t)(addr)) {
    std::cout << "Compiled function constructor std::arr" << std::endl;
  }

  fWrapper(py::array_t<double, py::array::c_style>& arr, const unsigned long long addr) : fbase<fWrapper<N>, double, N>(arr), fFunctor((function_t)(addr)) {
    std::cout << "Compiled function constructor py::arr" << std::endl;
  }
  
  double eval(unsigned n, double* p, double* x) {
    std::cout << "Evalvating the function" << std::endl;
    double res = fFunctor(n, p, x);
    std::cout << "Evalvation result is: " << res << std::endl;
    return res;
  }

  functor_t fFunctor;
};

//const int N_ = 5;
#endif

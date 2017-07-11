#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <iostream>

namespace py = pybind11;
using std::cout;
using std::endl;

typedef double (*function_t) (unsigned int, double*, double*);
typedef std::function<double(unsigned int, double*, double*)> functor_t;
//typedef std::function<double(unsigned int, std::vector<double>&, std::vector<double>&)> functor_t2;
typedef std::function<double(unsigned int, std::vector<double>&, double*)> functor_t2;


template<typename FunctorType, typename ReturnType, unsigned int N>
struct fbase {
  fbase() = delete;

  fbase(std::initializer_list<double> const& list) {
    for (size_t i = 0; i < N; ++i) {
      fPars[i] = *(list.begin() + i);
      //std::cout << fPars[i] << std::endl;
    }
  }

  fbase(fbase<FunctorType, ReturnType, N>const& other) {
    for (size_t i = 0; i < N; ++i)
      this->fPars[i] = other.fPars[i];
  }

  template <typename T>
  inline ReturnType operator() (T* x) {
    std::cout << "calling eval" << std::endl;
    return static_cast<FunctorType*>(this)->eval(N, fPars, x);
  }

  double fPars[N];

};


template<unsigned int N>
struct fWrapper : public fbase<fWrapper<N>, double, N> {
  fWrapper() = delete;

  fWrapper(const unsigned long long addr) : fbase<fWrapper<N>, double, N>({42.1, 42.2, 42.3, 44.4, 45.5, 46.6}), fFunctor((function_t)(addr)) {
    cout << "Compiled function constructor" << endl;
  }

  /*
  fWrapper(function_t const& fptr) : fbase<fWrapper<N>, double, N>({1.1, 2.2, 3.3, 4.4, 5.5, 6.6}), fFunctor(fptr) {
    cout << "function" << endl;
  }
  fWrapper(functor_t const& fptr) : fbase<fWrapper<N>, double, N>({1.1, 2.2, 3.3, 4.4, 5.5, 6.6}), fFunctor(fptr) {
    cout << "functor" << endl;
  }
  fWrapper(functor_t2 const& fptr) : fbase<fWrapper<N>, double, N>({1.1, 2.2, 3.3, 4.4, 5.5, 6.6}), fFunctor2(fptr) {
    cout << "functor2" << endl;
  }
  fWrapper(fWrapper const& other): fbase<fWrapper<N>, double, N>(other), fFunctor(other.fFunctor) {}
  
  double eval(unsigned int n, double* p, double* x) {
    std::cout << n << " " << *p << " " << *x << std::endl;
    for (auto i = 0; i < n; ++i)
      std::cout << p[i] << " ";
    std::cout << std::endl << "Vector: ";

    std::vector<double> vec(p, p + n);
    for(auto iter = vec.begin(); iter != vec.end(); ++iter)
      std::cout << *iter << " ";
    std::cout << std::endl;
    double d = fFunctor2(n, vec, x);
    std::cout << "after call" << std::endl;
    for(auto iter = vec.begin(); iter != vec.end(); ++iter)
      std::cout << *iter << " ";
    std::cout << std::endl;
    return d;
  }
  */
  
  double eval(unsigned n, double* p, double* x) {
    std::cout << "Evalvating the function" << std::endl;
    double res = fFunctor(n, p, x);
    std::cout << "Evalvation result is: " << res << std::endl;
    return res;
  }

  functor_t fFunctor;
  //functor_t2 fFunctor2;
};

/*
double eval(unsigned long long addr) {
  function_t callback = (function_t)(addr);
  double arr[] = {1.1, 2.2, 3.3, 4.4, 5.5};
  double a = 42.2;
  double *x = &a;
  return (*callback)(5, arr, x);
}
*/

PYBIND11_MODULE(foo, m) {
  py::class_<fWrapper<5>>(m, "fw")
    .def(py::init<unsigned long long>())
    .def("__call__", [](fWrapper<5> &f, double d) {
	//double d = 101.2; f(&d);
	f(&d);
      }, py::is_operator())
    ;
  //m.def("call", &eval);
}

/*
Python interpreter
from numba import cfunc, types, carray
  
c_sig = types.double(types.uint32, types.CPointer(types.double), types.CPointer(types.double))
 
@cfunc(c_sig)
def my_callback(a, in1_, in2_):
    in_array = carray(in1_, (a, 1))
    pointer_value = carray(in2_, (1, 1))
    # print("a:", a)
    d = pointer_value[0, 0]
    # print("array: ")
    for i in range(a):
        # print(in_array[i, 0])
        d *= in_array[i, 0]
    # print("Pointer variable:", pointer_value[0, 0])
    pointer_value[0, 0] += 1123456.45
    return d
*/

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
      std::cout << fPars[i] << std::endl;
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

  functor_t fFunctor;
  functor_t2 fFunctor2;
};


PYBIND11_MODULE(foo, m) {
  py::class_<fWrapper<5>>(m, "fw")
    .def(py::init<functor_t2>())
    .def("__call__", [](fWrapper<5> &f) {
	double d = 101.2; f(&d);
      }, py::is_operator())
    ;
}

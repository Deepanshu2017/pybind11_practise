#include <pybind11/pybind11.h>
#include <iostream>
#include <vector>

namespace py = pybind11;

// Similar to Events.h 

namespace hydra {
  template<unsigned int N, unsigned int M>
  struct Foo {

    Foo() {
      std::cout << "Constructor is called: " << N << " " << M << std::endl;
    }

    Foo(int a) {
      std::cout << "Constructor is called with int: " << a << " " << N << " " << M << std::endl;
    }
  
    template<unsigned int f>
    Foo(Foo<N, f> const& other) {
      std::cout << N << " " << f << std::endl;
    }

    template<unsigned int f>
    Foo<N, M>& operator=(Foo<N, f> const& other) {
      std::cout << N << " " << M << " " << f << " " << std::endl;
      return *this;
    }

    template<typename T>
    void print(T a) {
      std::cout << a << std::endl;
    }

    ~Foo() { std::cout << "Destructor is called" << std::endl; }

    int GetMaxWeight() const { return fMaxWeight; }
  
    int fMaxWeight = N;
  };
}

PYBIND11_MODULE(foo, m) {
  py::class_< hydra::Foo<4, 3> > c1(m, "Foo");
  c1.def(py::init<>());
  c1.def(py::init<int>());
  c1.def(py::init< hydra::Foo<4, 3> >());
  //c1.def("assign", &Foo<4, 3>::operator=);
  c1.def("print", &hydra::Foo<4, 3>::print<int>);
  //c1.def("GetMaxWeight", &hydra::Foo<4, 3>::GetMaxWeight);
}

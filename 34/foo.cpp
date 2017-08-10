#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <iostream>
#include <vector>

namespace py = pybind11;

struct Foo {
private:
  int var;
public:
  void setvar(int x) { var = x; }
  void getvar() { std::cout << var << std::endl; }
  void print(std::vector<Foo>& s) {
    for (auto &i : s)
      i.setvar(10);
  }
};

PYBIND11_MAKE_OPAQUE(std::vector<Foo>);

PYBIND11_MODULE(foo, m) {
  py::bind_vector<std::vector<Foo>>(m, "VectorFoo");
  py::class_< Foo >(m, "Foo")
    .def(py::init<>())
    .def("print", &Foo::print)
    .def("set", &Foo::setvar)
    .def("get", &Foo::getvar)
  ;
}

/*
In [1]: import foo

In [2]: l = [foo.Foo(), foo.Foo(), foo.Foo()]

In [3]: l = foo.VectorFoo(l)

In [4]: l
Out[4]: <foo.VectorFoo at 0x7f1375383990>

In [5]: a = foo.Foo()

In [6]: a.print(l)

In [7]: l[0].get()
10
*/

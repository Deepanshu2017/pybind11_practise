#include <pybind11/pybind11.h>

namespace py=pybind11;

class Animal {
public:
  virtual ~Animal() { }
  virtual std::string go(int n_times) = 0;
};

class Dog : public Animal {
  std::string go(int n_times) override {
    std::string result;
    for (int i = 0; i < n_times; ++i)
      result += "woof ";
    return result;
  }
};

std::string call_go(Animal* animal) {
  return animal->go(3);
}

PYBIND11_MODULE(foo, m) {
  py::class_<Animal> animal(m, "Animal");
  animal.def("go", &Animal::go);

  py::class_<Dog>(m, "Dog", animal)
    .def(py::init<>())
    ;

  m.def("call_go", &call_go);
}

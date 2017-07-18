import importlib
import subprocess
import json
import sys
import os


def write_pybind11_module(N):
  with open('foo.cc', 'w') as module:
    # module.write('#include "bindings.h"\n')
    module.write('#include "foo.h"\n\n')    
    # module.write(load_includes(impl_t))
    # module.write('\n')
    module.write('PYBIND11_MODULE(foo, m) {\n')
    module.write('  py::class_< fWrapper<' + str(N) + '> >(m, "fw")\n')
    module.write('    .def(py::init<std::array<double, ' + str(N) + '>const&, unsigned long long>())\n')
    module.write('    .def(py::init<py::array_t<double, py::array::c_style>&, unsigned long long>())\n')
    module.write('    .def("__call__", [](fWrapper<' + str(N) + '> &f, double x) {\n')
    module.write('        f(&x);\n')
    module.write('      }, py::is_operator())\n')
    module.write('    .def("__call__", [](fWrapper<' + str(N) + '> &f, py::array_t<double, py::array::c_style>& arr, double x) {\n')
    module.write('        f(arr, &x);\n')
    module.write('      }, py::is_operator())\n')
    module.write('    .def("__call__", [](fWrapper<' + str(N) + '> &f, std::array<double, ' + str(N) + '>& arr, double x) {\n')
    module.write('        f(arr, &x);\n')
    module.write('      }, py::is_operator())\n')
    module.write('    ;\n')
    module.write('}\n')    
    #module.write('  register_interface<Interface<' + impl_t + '>>(m);\n')
    #module.write('  pybind11::class_<' + impl_t + ', Interface<' + impl_t +
    #  '>>(m, "' + impl_t + '")\n')
    #module.write('    .def(pybind11::init<>());\n')
    #module.write('}\n')

def gen(N):
  write_pybind11_module(N)
  cmake = subprocess.Popen(["make", "foo"], cwd=os.getcwd())  
  cmake.wait()
  # name = "bindings" + impl_t
  # os.rename("bindings.cpython-36m-x86_64-linux-gnu.so", str(name + ".so"))
  name = "foo"
  os.rename("foo.cpython-35m-x86_64-linux-gnu.so", name + ".so")
  return importlib.import_module(name)

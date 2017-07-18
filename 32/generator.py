import importlib
import subprocess
import json
import sys
import os


def write_pybind11_module(N, name):
  with open(str(name) + '.cc', 'w') as module:
    module.write('#include "foo.h"\n\n')    
    module.write('PYBIND11_MODULE(' + str(name) +', m) {\n')
    module.write('  register_base< ' + str(name) + '<' + str(N) + '> >("' + str(name)  + '", m);\n')
    module.write('}\n')    


def write_makefile(name):
  with open('makefile', 'w') as makefile:
    makefile.write('include make.common\n\n')
    makefile.write('' + str(name) + ': ' + str(name) + '$(PYTHON_EXTENSION_SUFFIX) ;\n')


def gen(N, name):
  write_pybind11_module(N, name)
  write_makefile(name)
  make = subprocess.Popen(["make", name], cwd=os.getcwd())  
  make.wait()
  os.rename(str(name) + ".cpython-35m-x86_64-linux-gnu.so", name + ".so")
  return importlib.import_module(name)

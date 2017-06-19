"""This file contains "magic" implementations for IPython Notebook
that allow you to build Boost.Python programs and modules.
"""

import IPython.core.magic as ipym

# IMPORTANT: Adjust these flags to match your system.
#
# For the Python flags you can often use the ``python-config`` command.
# For boost.python, you just need to know.

"""
PYTHON_COMPILE_FLAGS=' '.join([
    '-I/usr/local/Cellar/python/2.7.6/Frameworks/Python.framework/Versions/2.7/include/python2.7',
    '-fno-strict-aliasing',
    '-fno-common',
    '-dynamic',
    '-I/usr/local/include',
    '-I/usr/local/opt/sqlite/include',
    '-DNDEBUG',
    '-g',
    '-fwrapv',
    '-O3',
    '-Wall',
    '-Wstrict-prototypes',
])

PYTHON_LINK_FLAGS=' '.join([
    '-L/usr/local/Cellar/python/2.7.6/Frameworks/Python.framework/Versions/2.7/lib/python2.7/config',
    '-ldl',
    '-framework',
    'CoreFoundation',
    '-lpython2.7',
])
"""

PYBIND_LINK_FLAGS='-I/home/deepanshu/pybind11/include'

PYTHON_COMPILE_FLAGS = ' '.join([
    '-I/usr/include/python3.5m',
    '-I/usr/include/python3.5m',
    '-Wno-unused-result',
    '-Wsign-compare',
    '-g',
    '-fstack-protector-strong',
    '-Wformat',
    '-Werror=format-security',
    '-DNDEBUG',
    '-g',
    '-fwrapv',
    '-O3',
    '-Wall',
    '-Wstrict-prototypes'
    ])

PYTHON_LINK_FLAGS=' '.join([
    '-L/usr/lib/python3.5/config-3.5m-x86_64-linux-gnu',
    '-L/usr/lib',
    '-lpython3.5m',
    '-lpthread',
    '-ldl',
    '-lutil',
    '-lm',
    '-Xlinker',
    '-export-dynamic',
    '-Wl,-O1 -Wl,-Bsymbolic-functions'
    ])

# STOP EDITING
#
# Don't edit below this line unless you know what you're doing or are
# feeling adventurous (or perhaps are stuck.)

@ipym.magics_class
class BoostPythonMagics(ipym.Magics):
    @ipym.cell_magic
    def bp_program(self, line, cell=None):
        """Compile, execute C++ code, and return the standard output."""

        args = line.split()
        name = args[0]

        args = args[1:]
        debug = 'debug' in args

        # Define the source and executable filenames.
        source_filename = '{}.cpp'.format(name)
        program_filename = './{}.exe'.format(name)
        # Write the code contained in the cell to the C++ file.
        with open(source_filename, 'w') as f:
            f.write(cell)

        result = []

        # Compile the C++ code into an executable.
        cmd = "clang++-3.8 {} {} {} {} -o {}".format(
            PYBIND_LINK_FLAGS,
            PYTHON_COMPILE_FLAGS,
            PYTHON_LINK_FLAGS,
            source_filename,
            program_filename)

        if debug:
            result.append(cmd)

        compile = self.shell.getoutput(cmd)
        result.append(compile)

        output = self.shell.getoutput(program_filename)
        result.append(output)

        if any(result):
            return ' -- '.join(map(str, filter(None, result)))

    @ipym.cell_magic
    def bp_module(self, line, cell=None):
        """Compile a boost.python module."""
        args = line.split()
        module_name = args[0]

        args = args[1:]
        debug = 'debug' in args

        # Define the source and executable filenames.
        source_filename = '{}.cpp'.format(module_name)
        # lib_filename = './{}.so'.format(module_name)

        # Write the code contained in the cell to the C++ file.
        with open(source_filename, 'w') as f:
            f.write(cell)

        result = []

        # Compile the C++ code into a shared library.
        cmd = "clang++-3.8 {} {} {} -shared -fPIC -std=c++0x {} -o foo.cpython-35m-x86_64-linux-gnu.so".format(
            PYTHON_COMPILE_FLAGS,
            PYTHON_LINK_FLAGS,
            PYBIND_LINK_FLAGS,
            source_filename)

        if debug:
            result.append(cmd)

        # run the compiler
        compile = self.shell.getoutput(cmd)

        result.append(compile)

        # If we have no output to report, return None
        if any(result):
            return ' -- '.join(map(str, filter(None, result)))

    @ipym.cell_magic
    def snippet(self, line, cell=None):
        "Ignore this code cell."
        pass

def load_ipython_extension(ipython):
    ipython.register_magics(BoostPythonMagics)

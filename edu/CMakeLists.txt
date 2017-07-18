cmake_minimum_required(VERSION 2.8.12)
project(eduardo)

add_subdirectory(pybind11)
pybind11_add_module(hello hello.cc)

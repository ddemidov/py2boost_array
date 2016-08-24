cmake_minimum_required(VERSION 3.0)
project(py2boost_array)

add_subdirectory(pybind11)
pybind11_add_module(py2boost_test py2boost_test.cpp)

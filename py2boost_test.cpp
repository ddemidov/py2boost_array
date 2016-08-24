#include <string>
#include <sstream>
#include <iomanip>

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include "py2boost_array.hpp"

namespace py = pybind11;

std::string a2s(py::array_t<int> a) {
    auto v = py2boost<2>(a);
    std::ostringstream s;

    for(int i = 0; i < v.shape()[0]; ++i) {
        for(int j = 0; j < v.shape()[1]; ++j)
            s << std::setw(3) << v[i][j];
        s << std::endl;
    }

    return s.str();
}

std::string a3s(py::array_t<int> a) {
    auto v = py2boost<3>(a);
    std::ostringstream s;

    for(int i = 0; i < v.shape()[0]; ++i) {
        for(int j = 0; j < v.shape()[1]; ++j) {
            for(int k = 0; k < v.shape()[2]; ++k)
                s << std::setw(3) << v[i][j][k];
            s << std::endl;
        }
        s << std::endl;
    }

    return s.str();
}

PYBIND11_PLUGIN(py2boost_test) {
    py::module m("py2boost_test");
    m.def("a2s", a2s, "Take 2D array, return string");
    m.def("a3s", a3s, "Take 3D array, return string");
    return m.ptr();
}

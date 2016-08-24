#ifndef PY2BOOST_ARRAY_HPP
#define PY2BOOST_ARRAY_HPP

/*
The MIT License

Copyright (c) 2016 Denis Demidov <dennis.demidov@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#include <array>
#include <algorithm>
#include <stdexcept>
#include <pybind11/numpy.h>
#include <boost/multi_array.hpp>

// Convert N-dimensional numpy array into boost::multi_array_ref with the
// appropriate storage order.
template <size_t N, typename T>
boost::multi_array_ref<T, N> py2boost(pybind11::array_t<T> p) {
    pybind11::buffer_info i = p.request();
    if (i.ndim != N) throw std::logic_error("Incompatible dimensions in py2boost()");

    size_t ord[N];
    bool   asc[N];
    for(int j = 0; j < N; ++j) {
        ord[j] = j;
        asc[j] = true;
    }

    std::sort(ord, ord + N, [&i](size_t a, size_t b){
            return i.strides[a] < i.strides[b]; });

    return boost::multi_array_ref<T, N>(static_cast<T*>(i.ptr),
            i.shape, boost::general_storage_order<N>(ord, asc));
}

#endif

#ifndef PY2BOOST_ARRAY_HPP
#define PY2BOOST_ARRAY_HPP

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

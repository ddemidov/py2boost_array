Just a convenience C++ function that takes an N-dimensional numpy array
(exported by [pybind11][1]) and returns an appropriately sized
[`boost::multi_array_ref<T,N>`][2] with the correct storage ordering.

[1]: https://github.com/pybind/pybind11
[2]: http://www.boost.org/doc/libs/release/libs/multi_array/doc/index.html

#include "pybind11/embed.h"
#include "pybind11/numpy.h"
#include "pybind11/stl.h"

#include <iostream>

namespace py = pybind11;

// ref : https://github.com/pybind/pybind11/issues/1042

template<typename T> void run_py_kernel_sigmoid_numpy(std::vector<T> x) {
  for (auto& i : x) {
    std::cout << i << std::endl;
  }
  auto x_array = py::array_t<T>(x.size(), x.data());
  py::module py_kernel = py::module::import("pyk_sigmoid_numpy");
  py::object result = py_kernel.attr("forward")(x_array);
  auto n = result.cast<std::vector<T>>();
  for (auto& i : n) {
    std::cout << i << std::endl;
  }
}

int main() {
  py::scoped_interpreter guard{}; // start the interpreter and keep it alive
  std::vector<float> x{1, 1, 1};
  run_py_kernel_sigmoid_numpy(x);
}

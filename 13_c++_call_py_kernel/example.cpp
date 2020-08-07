#include "pybind11/embed.h" // everything needed for embedding
#include <iostream>

namespace py = pybind11;

void run_py_kernel(int a, int b) {
  py::module py_kernel = py::module::import("py_kernel");
  py::object result = py_kernel.attr("add")(a, b);
  int n = result.cast<int>();
  std::cout << n << std::endl;
}

int main() {
  py::scoped_interpreter guard{}; // start the interpreter and keep it alive
  run_py_kernel(1, 2);
}

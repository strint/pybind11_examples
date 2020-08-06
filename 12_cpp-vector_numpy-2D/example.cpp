#include "pybind11/embed.h" // everything needed for embedding
#include <iostream>

namespace py = pybind11;

void say_hello() {
	py::print("Hello, World!"); // use the Python API
}

void exec_py_code() {
	py::exec(R"(
        kwargs = dict(name="World", number=42)
        message = "Hello, {name}! The answer is {number}".format(**kwargs)
        print(message)
    )");
}


void exec_using_api() {
	using namespace py::literals;
	auto kwargs = py::dict("name"_a = "World", "number"_a = 42);
	auto message = "Hello, {name}! The answer is {number}"_s.format(**kwargs);
	py::print(message);
}

void exec_combine() {
	using namespace py::literals;
	auto locals = py::dict("name"_a = "World", "number"_a = 42);
	py::exec(R"(
        message = "Hello, {name}! The answer is {number}".format(**locals())
    )", py::globals(), locals);

	auto message = locals["message"].cast<std::string>();
	std::cout << message << std::endl;
}

void import_sys_modules() {
	py::module sys = py::module::import("sys");
        py::print(sys.attr("path"));
}

void import_user_modules() {
	py::module calc = py::module::import("calc");
	py::object result = calc.attr("add")(1, 2);
	int n = result.cast<int>();
	std::cout << n << std::endl;
	assert(n == 3);
}

int main() {
	py::scoped_interpreter guard{}; // start the interpreter and keep it alive
	say_hello();
	exec_py_code();
	exec_using_api();
	exec_combine();
	import_sys_modules();
	import_user_modules();
}

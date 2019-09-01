#include <pybind11/pybind11.h>
#include "xtensor-python/pytensor.hpp"

#include "nl-lmp/solve-joint.hxx"
#include "andres/graph/graph.hxx"

namespace py = pybind11;


namespace nl_lmp {
    void export_solve_joint(py::module & module) {
        typedef andres::graph::Graph<> Graph;
        module.def("solve_joint", [](const Problem<Graph> & problem, const Solution & input_solution) {
            Solution result(input_solution.size());
            {
                py::gil_scoped_release allow_threads;
                result = update_labels_and_multicut(problem, input_solution);
            }
            return result;
        }, py::arg("problem"), py::arg("initial_solution"));
    }
}
#include <fstream>
#include <iomanip>
#include <iostream>

#include "output_data/output_utility_t.h"
#include "plugin/argumentParser.h"
#include "plugin/visualizer_t.h"
#include "process/case_table_t.h"
#include "process/solver_t.h"
#include "process/tester.h"
#include "static_data/chip_t.h"
#include "static_data/io_handler_t.h"
using namespace std;
void usage(int argc, char* argv[]) {}
int main(int argc, char** argv) {
    argumentParser argument;
    try {
        argument = argumentParser(argc, argv, usage);
    } catch (std::exception& e) {
        logger_t::error({e.what()});
    }
    if (argument.has("i")) {
        io_handler_t::input_file_name = argument.get("i");
        chip_t::file_input(io_handler_t::input_file_name,
                           chip_t::file_type_t::iccad_pd);  // fstream
    }
    if (argument.has("o")) {
        io_handler_t::output_checker_file_name = argument.get("o");
    }
    if (argument.has("t")) {
        tester_t tester;
        tester.test_sp();
        logger_t::action({"Press any key to end the program"});
        fgetc(stdin);
    } else {
        solver_t solver;
        solver.run();
    }
    return 0;
}

#include "tester.h"

#include <iomanip>
#include <iostream>

#include "../static_data/io_handler_t.h"
#include "SA_solver_t.h"
#include "process/case_table_t.h"
#include "process/functional/random_helper.h"
#include "process/sequence_pair/sequence_pair_t.h"
tester_t::tester_t() {
    random_helper::set_seed();  // build up random table

    sequence_pair_t::init();  // class initialization

    if (chip_t::get_total_module_n() < 1) {
        return;
    }
}

void tester_t::test() {}
void tester_t::test_sp() {
    case_table_t case_table;
    int case_id = chip_t::get_similar_case_num();
    sequence_pair_t SP;
    if (case_id != -1) {
        SP.v_sequence = case_table.cases[case_id][0];
        SP.h_sequence = case_table.cases[case_id][1];
        SP.set_is_in_seq(1);
        bool success =
            SP.find_position_allow_illegal_process();  // Test either
                                                       // rectilinear or
                                                       // rectangular
        // bool success = SP.find_position(true, true, 0, 0);
        if (success == false) {
            logger_t::error({"Unable to initialize"});
            return;
        }
        SP.get_wirelength();
        // SP.sequence_pair_validation();
        SP.to_rectilinear();
        SP.plot_rectilinear();
        SP.check_rectilinear_result(true);
        SP.print_inline();
    } else {
        logger_t::error(
            {"This is not a default test case, can't load a predetermined "
             "sequence pair. "});
    }
}

//
// Created by RayChang on 2023/5/6.
//

#ifndef ICCAD2023PD_SEQUENCE_PAIR_T_H
#define ICCAD2023PD_SEQUENCE_PAIR_T_H
#include <iterator>
#include <unordered_map>
#include <vector>

#include "process/components/edge_t.h"
#include "process/components/net_t.h"
#include "process/components/timer.h"
#include "process/functional/ILP_solver_t.h"
#include "static_data/chip_t.h"
#include "static_data/fixed_module_t.h"
#include "static_data/soft_module_t.h"
#include "utilities/vec2d_t.h"

using std::pair;
using std::unordered_map;
using std::vector;
class sequence_pair_t {
    friend class sp_ilp_settings_find_position_t;
    friend class sp_ilp_settings_find_position_with_area_t;

   public:
    // Constructor
    sequence_pair_t();

    // Static functions
    static void init();
    static void build_graph();
    static vector<vec2d_t> find_w_h(
        uint32_t area, int);  // Calculate a legal shapes for a specific area

    // Static properties
    static int sequence_n;            // Number of sequences number
    static int fixed_n;               // Number of fixed sequences number
    static int soft_n;                // Number of soft sequences number
    static int connection_graph_deg;  // The degree of all nets
    static int fix_start_idx;  // The sequence number of the first fix module
    static vector<net_t> connections;  // All edges (only one direction)
    static vector<pair<int, int>> deg_w;
    static vector<bool> seq_is_fix;  // Whether the module is a fixed module (so
                                     // the array should be [0,0,...,0,1,...1]
    vector<vector<vec2d_t>>
        soft_area_to_w_h_m_5;  // Shapes for the modules with 5 sample points
    vector<vector<vec2d_t>>
        soft_area_to_w_h_m_9;  // Shapes for the modules with 9 sample points
    static vector<soft_module_t*>
        seq_soft_map;  // Mapping from a soft module to its sequence number
    static vector<fixed_module_t*>
        seq_fixed_map;  // Mapping from a fixed module to its sequence number
    static vector<double>
        modules_area;  // The area of the modules (indexing by sequence number)

    // Sequence pair
    // h_sequence and v_sequence are the actual sequence pair
    vector<int> h_sequence, v_sequence, fix_v_sequence, fix_h_sequence;

    // Properties for resulting floorplan
    vector<vec2d_t> modules_wh;  // The resulting shapes
    vector<int> modules_wh_i;
    vector<vec2d_t> modules_positions;   // The resulting positions
    double actual_wirelength = -1;       // The actual HPWL without interlocking
    double rectilinear_wirelength = -1;  // The wirelength after interlocking
    double lp_predicted_wirelength = -1;  // The wirelength output from LP

    // Properties for sequence pair initialization
    vector<int>
        add_soft_order;  // The order of the inserting of the sequence numbers
    vector<int> is_in_seq;  // Whether the sequence number is inserted

    // Properties for rectilinear floorplans
    std::vector<std::pair<std::vector<vec2d_t>, std::string>> bounding_lines;
    vector<int> carved;
    vector<int> allow_to_overlap;

    // Functions with the prefix 'find_position' find the corresponding
    // floorplan
    // based on the sequence pair
    // and verify if the current sequence pair form the legal position
    bool find_position(
        bool, bool);  // Find the floorplan without given widths and heights
    bool find_position_with_area(
        bool, bool);  // Find the floorplan with given widths and heights
    bool
    find_position_allow_illegal_process();  // This function would call the two
                                            // functions below. To generate the
                                            // floorplans with overlapping
    bool find_position_allow_illegal_fill(
        bool, bool);  // Due to the overlapping, the area should be compensated
    bool find_position_allow_illegal(
        bool, bool);  // The actual function for generating the floorplans

    void to_rectilinear();    // Generate bounding lines from a overlapped
                              // floorplan
    void plot_rectilinear();  // This function requires the 'bounding_lines' to
                              // be set!

    // Check whether the resulting rectilinear floorplan is legal
    void check_rectilinear_result(bool);

    // get & set
    void swap_v(int, int);
    void swap_h(int, int);
    void set_v(std::vector<int>);
    void set_h(std::vector<int>);
    void set_vi(int, int);
    void set_hi(int, int);
    void set_module_size(int, int);
    void set_is_in_seq(int);
    int get_vi(int);
    int get_hi(int);
    std::vector<int> get_v();
    std::vector<int> get_h();
    vector<vec2d_t> get_4_points(vec2d_t, vec2d_t);
    vector<int> get_correct_area();
    vector<int> get_correct_compensation();
    double get_wirelength();
    double get_wirelength_rectilinear();
    void fill_near();
    void overlap_optimization();
    void carve();
    void deal_bounding_line();
    void change_size(int);
    void print_inline();
    void write_inline();
    void sequence_pair_validation();
    void sequence_pair_validation(int);
    void print_result();
    void set_bounding_lines();
    bool check_area_ratio();
    // Initialization
    void set_only_fix();
    bool is_completed();  // Check whether all modules are in the sequence and
                          // solvable for LP
    void init_modules_size();
    void set_fix_sequence();
    void set_add_order();

    // Functions for LP
    vector<vec2d_t> get_LP_res_pos();
    pair<vector<vec2d_t>, vector<int>> get_LP_res_wh();
    void build_constraint_graph();
    void simplify_constraint_graph();
    void mark_transitive_edge();

    // Debug
    void print();
    void print_v();
    void print_h();
    void print_logs();
    void print_shapes_i();
    void print_fix_sequence();
    void print_connections();
    void print_wirelength();

   private:
    // Properties for LP
    int constraint_n, constraint_i, variable_n;
    int x_module_offset, y_module_offset, x_edge_offset_l, x_edge_offset_r,
        y_edge_offset_l, y_edge_offset_r, x_overlap, y_overlap;
    int near_x_offset, near_y_offset;
    vector<vector<int>> near_x_map, near_y_map;
    vector<vector<int>> near_x_id, near_y_id;
    vector<int> shape_types;
    vector<vector<int>> near_x, near_y;
    ILP_solver_t ILP_solver;
    ILP_result_t ILP_result;
    vector<vector<int>> result_carving_x, result_carving_y;
    vector<bool> result_carving_x_enable, result_carving_y_enable;
    vector<edge_t> constraint_graph_h, constraint_graph_v;
    vector<vector<int>> is_transitive_h, is_transitive_v;

    // Debug properties
    vector<pair<double, double>> logs;
};

#endif  // ICCAD2023PD_SEQUENCE_PAIR_T_H

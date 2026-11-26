#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "defines.h"
#include "dsl.h"
#include "general_func_tree.h"
#include "calc_tree_functions.h"
#include "read_func.h"
//----------------------------------------------------------------------------
int main(){
// //-----------------------------------------------------------------
//     tree_diff_node_t* node1 = _DIV();
//     tree_diff_node_t* node2 = _ADD();
//     tree_diff_node_t* node3 = _VARX();
//     tree_diff_node_t* node4 = _VARX();
//     tree_diff_node_t* node5 = _MUL();
//     tree_diff_node_t* node6 = _VARX();
//     tree_diff_node_t* node7 = _VARX();

//     link_nodes(node1, node2, node5);
//     link_nodes(node2, node3, node4);
//     link_nodes(node5, node6, node7);
// //-----------------------------------------------------------------
//     tree_diff_node_t* pow = _POW();
//     tree_diff_node_t* base = _VARX();
//     tree_diff_node_t* exp = _VARX();

//     link_nodes(pow, base, exp);
// //-----------------------------------------------------------------
//     tree_diff_node_t* log = _LOG();
//     tree_diff_node_t* base_log = _VARX();
//     tree_diff_node_t* arg_log = _VARX();

//     link_nodes(log, base_log, arg_log);
// //-----------------------------------------------------------------
//     tree_diff_node_t* sin = _SIN();
//     tree_diff_node_t* div_node = _DIV();
//     tree_diff_node_t* cos = _COS();
//     link_nodes(div_node, sin, cos);
//     tree_diff_node_t* sin_arg = _VARX();
//     tree_diff_node_t* cos_arg = _VARX();
//     link_nodes(sin, sin_arg, NULL);
//     link_nodes(cos, cos_arg, NULL);

// //-----------------------------------------------------------------
//     tree_diff_node_t* arcsin = _ARCSIN();
//     tree_diff_node_t* arg_arcsin = _POW();
//     tree_diff_node_t* base_pow_arg_arcsin = _VARX();
//     tree_diff_node_t* exp_pow_arg_arcsin = _NUM(2);
//     link_nodes(arg_arcsin, base_pow_arg_arcsin, exp_pow_arg_arcsin);
//     link_nodes(arcsin, arg_arcsin, NULL);
// // ----------------------------------------------------------------
//     tree_diff_node_t* pow_2 = _POW();
//     tree_diff_node_t* base_2 = _VARX();
//     tree_diff_node_t* exp_2 = _NUM(2);

//     link_nodes(pow_2, base_2, exp_2);
// // ----------------------------------------------------------------


    FILE* viz_file = fopen("viz_file.txt", "w");
    assert(viz_file);

    FILE* file_with_deritative = fopen("file_with_deritative.txt", "w");
    assert(file_with_deritative);
    
    FILE* formula_tex = fopen("formula.tex", "w");
    assert(formula_tex);
    //printf("%lf\n", calculate_subtree(node1));
    //printf("%lf\n", calculate_subtree(node2));
    FILE* pre_order = fopen("pre_order.txt", "r");
    assert(pre_order);

    char* str_buf = create_str_buffer("pre_order.txt");
    tree_diff_node_t* pre_order_tree = parse_pre_order(str_buf);
    free(str_buf);


    // tree_diff_node_t* copy_root = subtree_copy(node1);
    tree_diff_node_t* diff_tree = diff(pre_order_tree);

    constant_folding_tree(diff_tree);
    delete_neutral_elements(diff_tree);

    tree_viz(diff_tree, file_with_deritative);
    tree_viz(pre_order_tree, viz_file);
    tex_viz_of_tree(diff_tree, formula_tex);

    //printf("%lf\n", calculate_subtree(diff_tree, sqrt(2)));

    delete_tree(pre_order_tree);
    delete_tree(diff_tree);

    fclose(pre_order);
    fclose(file_with_deritative);
    fclose(viz_file);
    fclose(formula_tex);
    return 0;
}
//----------------------------------------------------------------------------

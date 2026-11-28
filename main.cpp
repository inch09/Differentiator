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

    FILE* viz_file = fopen("viz_file.txt", "w");
    assert(viz_file);
    FILE* file_with_deritative = fopen("file_with_deritative.txt", "w");
    assert(file_with_deritative);    
    FILE* formula_tex = fopen("formula.tex", "w");
    assert(formula_tex);
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

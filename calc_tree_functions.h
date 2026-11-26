#ifndef CALC_TREE_FUNC
#define CALC_TREE_FUNC

#include "defines.h"
//-----------------------------------------------------------------
double calculate_subtree(tree_diff_node_t* node, double val_of_var);
double calculate_operation(tree_diff_node_t* node, double operand1, double operand2);
double calculate_constant_subtree(tree_diff_node_t* node);
void constant_folding_tree(tree_diff_node_t* node);
//-----------------------------------------------------------------
void delete_neutral_elements(tree_diff_node_t* node);
void delete_neutral_add_and_sub_elements(tree_diff_node_t* node);
void delete_neutral_mul_elements(tree_diff_node_t* node);
void delete_neutral_div_elements(tree_diff_node_t* node);
void delete_neutral_pow_elements(tree_diff_node_t* node);
//-----------------------------------------------------------------
tree_diff_node_t* diff(tree_diff_node_t* node);
tree_diff_node_t* deritative_sum(tree_diff_node_t* node);
tree_diff_node_t* deritative_difference(tree_diff_node_t* node);
tree_diff_node_t* deritative_product(tree_diff_node_t* node);
tree_diff_node_t* deritative_quotient(tree_diff_node_t* node);
//-----------------------------------------------------------------
tree_diff_node_t* deritative_general_pow_function(tree_diff_node_t* node);
tree_diff_node_t* deritative_pow_function(tree_diff_node_t* node);
tree_diff_node_t* deritative_exponential_function(tree_diff_node_t* node);
tree_diff_node_t* deritative_pow_and_exponential_function(tree_diff_node_t* node);
//-----------------------------------------------------------------
tree_diff_node_t* deritative_log_function(tree_diff_node_t* node);
tree_diff_node_t* deritative_log_with_const_base_function(tree_diff_node_t* node);
tree_diff_node_t* deritative_general_log_function(tree_diff_node_t* node);
//-----------------------------------------------------------------
tree_diff_node_t* deritative_sin(tree_diff_node_t* node);
tree_diff_node_t* deritative_cos(tree_diff_node_t* node);
tree_diff_node_t* deritative_tg(tree_diff_node_t* node);
tree_diff_node_t* deritative_ctg(tree_diff_node_t* node);
tree_diff_node_t* deritative_arcsin(tree_diff_node_t* node);
tree_diff_node_t* deritative_arccos(tree_diff_node_t* node);
tree_diff_node_t* deritative_arctg(tree_diff_node_t* node);
tree_diff_node_t* deritative_arcctg(tree_diff_node_t* node);
//-----------------------------------------------------------------
tree_diff_node_t* subtree_copy(tree_diff_node_t* node);
tree_diff_node_t* node_copy(tree_diff_node_t* node);
tree_diff_node_t* node_copy_without_new_node(tree_diff_node_t* node_copy_to, tree_diff_node_t* node_copy_from);
 
#endif
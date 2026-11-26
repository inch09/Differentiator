#ifndef GENERAL_FUNC_TREE_H
#define GENERAL_FUNC_TREE_H

#include "defines.h"
#include <stdio.h>
//-----------------------------------------------------------------
tree_diff_node_t* create_node(type_of_node type, node_value val, tree_diff_node_t* left, tree_diff_node_t* right, tree_diff_node_t* parent);
tree_diff_node_t* create_num_node(type_of_node type, double num, tree_diff_node_t* left, tree_diff_node_t* right, tree_diff_node_t* parent);
tree_diff_node_t* create_var_node(type_of_node type, type_of_variable var, tree_diff_node_t* left, tree_diff_node_t* right, tree_diff_node_t* parent);
tree_diff_node_t* create_op_node(type_of_node type, type_of_operation oper, tree_diff_node_t* left, tree_diff_node_t* right, tree_diff_node_t* parent);
void delete_node(tree_diff_node_t* node);
void delete_tree(tree_diff_node_t* node);
//-----------------------------------------------------------------
void link_nodes(tree_diff_node_t* parent, tree_diff_node_t* left, tree_diff_node_t* right);
void set_node_left(tree_diff_node_t* node, tree_diff_node_t* left);
void set_node_right(tree_diff_node_t* node, tree_diff_node_t* right);
void set_node_parent(tree_diff_node_t* node, tree_diff_node_t* parent);
bool is_node_have_left(tree_diff_node_t* node);
bool is_node_have_right(tree_diff_node_t* node);
bool is_node_have_parent(tree_diff_node_t* node);
//-----------------------------------------------------------------
void tex_viz_of_nodes(tree_diff_node_t* node, FILE* tex_file);
void tex_viz_of_tree(tree_diff_node_t* node, FILE* tex_file);
//-----------------------------------------------------------------
void tree_viz(tree_diff_node_t* root, FILE* viz_file);
void create_node_viz(tree_diff_node_t* node, FILE* viz_file);
void create_edge_viz(tree_diff_node_t* node, FILE* viz_file);
void create_op_node_viz(tree_diff_node_t* node, FILE* viz_file);
void create_var_node_viz(tree_diff_node_t* node, FILE* viz_file);
void create_num_node_viz(tree_diff_node_t* node, FILE* viz_file);
//-----------------------------------------------------------------
tree_diff_node_t* subtree_copy(tree_diff_node_t* node);
tree_diff_node_t* node_copy(tree_diff_node_t* node);
tree_diff_node_t* node_copy_without_new_node(tree_diff_node_t* node_copy_to, tree_diff_node_t* node_copy_from);

#endif
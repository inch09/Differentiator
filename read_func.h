#ifndef READ_FUNC_H
#define READ_FUNC_H

#include "defines.h"
#include "stddef.h"

char* convert_str_to_read_pre_order(const char* str_buf);
tree_diff_node_t* parse_pre_order(const char* str_buf);
tree_diff_node_t* parse_node_data(const char* str_buf);
int is_node_type_operation(const char* str_node_data);
int is_node_type_variable(const char* str_node_data);
double is_node_type_number(const char* str_node_data);
//-----------------------------------------------------------------
char* create_str_buffer(const char* file_name);
size_t get_file_size(const char* file_name);

#endif
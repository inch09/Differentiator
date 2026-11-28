#include "defines.h"
#include "dsl.h"
#include "general_func_tree.h"
#include "read_func.h"

#include <stddef.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

const char* arr_operations[] = {"+", "-", "*", "/", "^", "log", "sin", "cos", "tg", "ctg", "arcsin", "arccos", "arctg", "arcctg"};
const char* arr_variables[] = {"x", "y"};

char* convert_str_to_read_pre_order(const char* str_buf){
    assert(str_buf);

    size_t len = strlen(str_buf);
    size_t j = 0;
    while(j < len){
         if(str_buf[j] == '('){
            break;
         }
        j++;
    }

    size_t new_len = len - j - 1;

    char* new_buf = (char*) calloc(new_len + 1, sizeof(char));
    assert(new_buf);
    strcpy(new_buf, str_buf + j + 1);

    int i = new_len - 1;
    while(i >= 0){
        if( new_buf[i] == ')'){
            new_buf[i] = '\0';
            break; 
        }
        i--;
    }

    free((void*) str_buf);
    str_buf = NULL;

    return new_buf;
}
//----------------------------------------------------------------------------
tree_diff_node_t* parse_pre_order(const char* str_buf){
    assert(str_buf);

    static char* convert_str = convert_str_to_read_pre_order(str_buf);
    assert(convert_str);
    
    int num_of_child = 0;
    static int ind_in_str = 0;

    tree_diff_node_t* node = parse_node_data(convert_str + ind_in_str);
    assert(node);

    while (convert_str[ind_in_str] != '\0'){
        if(convert_str[ind_in_str] == '('){ 
            num_of_child++;
            ind_in_str++;
            tree_diff_node_t* child_node = parse_pre_order(convert_str); 
            set_node_parent(child_node, node);
            if(num_of_child == 1) set_node_left (node, child_node);
            if(num_of_child == 2) set_node_right(node, child_node);
        }
        else if(convert_str[ind_in_str] == ')'){
            ind_in_str++; 
            return node;
        }    
        else ind_in_str++;
    }

    ind_in_str = 0;
    free(convert_str);
    return node;
}
//----------------------------------------------------------------------------
tree_diff_node_t* parse_node_data(const char* str_buf){
    assert(str_buf);

    size_t i = 0;
    size_t count_symbols = 0;  
    while(str_buf[i] != '\0'){
        if(str_buf[i] == '(' || str_buf[i] == ')'){
            break;
        }
        if(str_buf[i] != ' ') count_symbols++;
        i++;
    }

    char* node_data = (char*) calloc(count_symbols + 1, sizeof(char));
    assert(node_data);

    i = 0;
    while(i < count_symbols){
        if(str_buf[i] != ' ') node_data[i] = str_buf[i];
        i++;
    }

    printf("<%s>\n", node_data);
    int oper_type = is_node_type_operation(node_data);
    if(oper_type >= 0) return _OP((type_of_operation) oper_type);

    printf("<%s>\n", node_data);
    int var_type = is_node_type_variable(node_data);
    if(var_type >= 0) return _VAR((type_of_variable) var_type);

    double num =  is_node_type_number(node_data);
    if(!isnan(num)) return _NUM(num);

    printf("Unknown type of node\n");
    return NULL;
}
//----------------------------------------------------------------------------
int is_node_type_operation(const char* str_node_data){
    assert(str_node_data);

    size_t count_of_op = sizeof(arr_operations) / sizeof(arr_operations[0]);
    int code_of_op = - 1;
    for(size_t i = 0; i < count_of_op; i++){
        if(strcmp(str_node_data, arr_operations[i]) == 0){
            code_of_op = i;
            break;
        }
    }
    return code_of_op;
}
//----------------------------------------------------------------------------
int is_node_type_variable(const char* str_node_data){
    assert(str_node_data);

    size_t count_of_var = sizeof(arr_variables) / sizeof(arr_variables[0]);
    int code_of_var = -1;
    for(size_t i = 0; i < count_of_var; i++){
        if(strcmp(str_node_data, arr_variables[i]) == 0){
            code_of_var = i;
            break;
        }
    }
    return code_of_var;
}
//----------------------------------------------------------------------------
double is_node_type_number(const char* str_node_data){
    assert(str_node_data);

    double node_val = NAN;
    sscanf(str_node_data, "%lf",&node_val);
    return node_val;
}
//----------------------------------------------------------------------------
char* create_str_buffer(const char* file_name){
    assert(file_name);

    FILE* file_ptr = fopen(file_name, "r");
    assert(file_ptr);

    size_t full_file_size = get_file_size(file_name);
    char* str_buf = (char*) calloc(full_file_size + 1, sizeof(char));
    assert(str_buf);

    size_t real_file_size = fread(str_buf, sizeof(char), full_file_size, file_ptr);
    realloc(str_buf, real_file_size * sizeof(char));
    assert(str_buf);

    fclose(file_ptr);

    return str_buf;
}
//----------------------------------------------------------------------------
size_t get_file_size(const char* file_name){
    assert(file_name);

    struct stat file_info = {};
    stat(file_name, &file_info);
    return file_info.st_size;
}
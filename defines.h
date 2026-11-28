#ifndef DEFINES_H
#define DEFINES_H

extern const char* arr_operations[]; 
extern const char* arr_variables[];

//-----------------------------------------------------------------
enum type_of_node{
    OP  = 0,
    VAR = 1,
    NUM = 2
};
//-----------------------------------------------------------------
enum type_of_operation{
    ADD = 0,
    SUB = 1,
    MUL = 2,
    DIV = 3,
    POW = 4,
    LOG = 5,
    SIN = 6,
    COS = 7,
    TG = 8,
    CTG = 9,
    ARCSIN = 10,
    ARCCOS = 11,
    ARCTG = 12,
    ARCCTG = 13
};
//-----------------------------------------------------------------
struct variable{
    char* name;
    double value;
};    
//-----------------------------------------------------------------
enum type_of_variable{
    X = 0,
    Y = 1
};
//-----------------------------------------------------------------
union node_value{
    double num;
    type_of_operation op_type;
    type_of_variable var;
};
//-----------------------------------------------------------------
struct tree_diff_node_t{
    type_of_node type;
    node_value val;
    tree_diff_node_t* left;
    tree_diff_node_t* right;
    tree_diff_node_t* parent;
};
//-----------------------------------------------------------------
const node_value add_union =    {.op_type = ADD};
const node_value sub_union =    {.op_type = SUB}; 
const node_value mul_union =    {.op_type = MUL}; 
const node_value div_union =    {.op_type = DIV}; 
const node_value pow_union =    {.op_type = POW}; 
const node_value log_union =    {.op_type = LOG}; 
const node_value sin_union =    {.op_type = SIN}; 
const node_value cos_union =    {.op_type = COS}; 
const node_value tg_union =     {.op_type = TG}; 
const node_value ctg_union =    {.op_type = CTG};
const node_value arcsin_union = {.op_type = ARCSIN}; 
const node_value arccos_union = {.op_type = ARCCOS}; 
const node_value arctg_union =  {.op_type = ARCTG}; 
const node_value arcctg_union = {.op_type = ARCCTG}; 
//-----------------------------------------------------------------
const node_value var_x = {.var = X};
const node_value var_y = {.var = Y};

#endif
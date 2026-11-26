#ifndef DSL_H
#define DSL_H
//----------------------------------------------------------------- 
#define _OP(op)   create_op_node(OP, op, NULL, NULL, NULL)
#define _ADD()    create_node(OP, add_union, NULL, NULL, NULL)
#define _SUB()    create_node(OP, sub_union, NULL, NULL, NULL)
#define _MUL()    create_node(OP, mul_union, NULL, NULL, NULL)
#define _DIV()    create_node(OP, div_union, NULL, NULL, NULL)
#define _POW()    create_node(OP, pow_union, NULL, NULL, NULL)
#define _LOG()    create_node(OP, log_union, NULL, NULL, NULL)
#define _SIN()    create_node(OP, sin_union, NULL, NULL, NULL)
#define _COS()    create_node(OP, cos_union, NULL, NULL, NULL)
#define _TG()     create_node(OP, tg_union, NULL, NULL, NULL)
#define _CTG()    create_node(OP, ctg_union, NULL, NULL, NULL)
#define _ARCSIN() create_node(OP, arcsin_union, NULL, NULL, NULL)
#define _ARCCOS() create_node(OP, arccos_union, NULL, NULL, NULL)
#define _ARCTG()  create_node(OP, arctg_union, NULL, NULL, NULL)
#define _ARCCTG() create_node(OP, arcctg_union, NULL, NULL, NULL)
//-----------------------------------------------------------------
#define _VAR(variable)  create_var_node(VAR, variable, NULL, NULL, NULL)
#define _VARX() create_node(VAR, var_x, NULL, NULL, NULL)
#define _VARY() create_node(VAR, var_y, NULL, NULL, NULL)
//-----------------------------------------------------------------
#define _NUM(val) create_num_node(NUM, val, NULL, NULL, NULL)
//-----------------------------------------------------------------
#define _DIFFL(node)    diff(node->left)
#define _DIFFR(node)    diff(node->right)
#define _COPYL(node)    subtree_copy(node->left)
#define _COPYR(node)    subtree_copy(node->right)
//--------------------------------------------------
#endif
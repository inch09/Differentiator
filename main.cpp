#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
// TODO: static func!!!!
// sdelat dynamich massiv perem chtoby mozhno bylo dobvlyat novye
//-----------------------------------------------------------------
//-----------------------------------------------------------------
#define _NUM(value)    create_node(NUM, value, NULL, NULL, NULL)
#define _VAR(variable) create_node(VAR, variable, NULL, NULL, NULL)
#define _OP(operation) create_node(OP, operation, NULL, NULL, NULL)
#define _DIFFL(node)   diff(node->left)
#define _DIFFR(node)   diff(node->right)
#define _COPYL(node)   subtree_copy(node->left)
#define _COPYR(node)   subtree_copy(node->right)
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
struct tree_diff_node_t{
    type_of_node type;
    double val;
    tree_diff_node_t* left;
    tree_diff_node_t* right;
    tree_diff_node_t* parent;
};
//-----------------------------------------------------------------
tree_diff_node_t* create_node(type_of_node type, double val, tree_diff_node_t* left, tree_diff_node_t* right, tree_diff_node_t* parent);
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
double calculate_subtree(tree_diff_node_t* node, double val_of_var);
double calculate_operation(tree_diff_node_t* node, double operand1, double operand2);
double calculate_constant_subtree(tree_diff_node_t* node);
void constant_folding_tree(tree_diff_node_t* node);
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
//-----------------------------------------------------------------
int main(){
//-----------------------------------------------------------------
    tree_diff_node_t* node1 = create_node(OP, 3, NULL, NULL, NULL);
    tree_diff_node_t* node2 = create_node(OP, 0, NULL, NULL, NULL);
    tree_diff_node_t* node3 = create_node(VAR, 0, NULL, NULL, NULL);
    tree_diff_node_t* node4 = create_node(VAR, 0, NULL, NULL, NULL);
    tree_diff_node_t* node5 = create_node(OP, 2, NULL, NULL, NULL);
    tree_diff_node_t* node6 = create_node(VAR, 0, NULL, NULL, NULL);
    tree_diff_node_t* node7 = create_node(VAR, 0, NULL, NULL, NULL);

    link_nodes(node1, node2, node5);
    link_nodes(node2, node3, node4);
    link_nodes(node5, node6, node7);
//-----------------------------------------------------------------
    tree_diff_node_t* pow = _OP(4);
    tree_diff_node_t* base = _VAR(0);
    tree_diff_node_t* exp = _VAR(0);

    link_nodes(pow, base, exp);
//-----------------------------------------------------------------
    tree_diff_node_t* log = _OP(5);
    tree_diff_node_t* base_log = _VAR(0);
    tree_diff_node_t* arg_log = _VAR(0);

    link_nodes(log, base_log, arg_log);
//-----------------------------------------------------------------
    tree_diff_node_t* sin = _OP(6);
    tree_diff_node_t* div_node = _OP(3);
    tree_diff_node_t* cos = _OP(7);
    link_nodes(div_node, sin, cos);
    tree_diff_node_t* sin_arg = _VAR(0);
    tree_diff_node_t* cos_arg = _VAR(0);
    link_nodes(sin, sin_arg, NULL);
    link_nodes(cos, cos_arg, NULL);

//-----------------------------------------------------------------
    tree_diff_node_t* arcsin = _OP(10);
    tree_diff_node_t* arg_arcsin = _OP(4);
    tree_diff_node_t* base_pow_arg_arcsin = _VAR(0);
    tree_diff_node_t* exp_pow_arg_arcsin = _NUM(2);
    link_nodes(arg_arcsin, base_pow_arg_arcsin, exp_pow_arg_arcsin);
    link_nodes(arcsin, arg_arcsin, NULL);
// ----------------------------------------------------------------
    tree_diff_node_t* pow_2 = _OP(4);
    tree_diff_node_t* base_2 = _VAR(0);
    tree_diff_node_t* exp_2 = _NUM(2);

    link_nodes(pow_2, base_2, exp_2);
// ----------------------------------------------------------------


    FILE* viz_file = fopen("viz_file.txt", "w");
    assert(viz_file);

    FILE* file_with_deritative = fopen("file_with_deritative.txt", "w");
    assert(file_with_deritative);
    
    FILE* formula_tex = fopen("formula.tex", "w");
    assert(formula_tex);
    //printf("%lf\n", calculate_subtree(node1));
    //printf("%lf\n", calculate_subtree(node2));

    // tree_diff_node_t* copy_root = subtree_copy(node1);
    tree_diff_node_t* diff_tree = diff(node1);

    constant_folding_tree(diff_tree);
    tree_viz(diff_tree, file_with_deritative);
    tree_viz(node1, viz_file);
    tex_viz_of_tree(diff_tree, formula_tex);

    //printf("%lf\n", calculate_subtree(diff_tree, sqrt(2)));

    delete_tree(node1);

    fclose(file_with_deritative);
    fclose(viz_file);
    fclose(formula_tex);
    return 0;
}
//-----------------------------------------------------------------
tree_diff_node_t* create_node(type_of_node type, double val, tree_diff_node_t* left, tree_diff_node_t* right, tree_diff_node_t* parent){

    tree_diff_node_t* new_node = (tree_diff_node_t*) calloc(1, sizeof(tree_diff_node_t));
    assert(new_node);

    new_node->type = type;
    new_node->val = val;
    new_node->left = left;
    new_node->right = right;
    new_node->parent = parent;

    return new_node;
}
//-----------------------------------------------------------------
void delete_node(tree_diff_node_t* node){
    assert(node);
    free(node);
    return;
}
//-----------------------------------------------------------------
void delete_tree(tree_diff_node_t* node){
    assert(node);

    if (is_node_have_left(node)) delete_tree(node->left);
    if(is_node_have_right(node)) delete_tree(node->right);

    delete_node(node);
}
//----------------------------------------------------------------------------
void link_nodes(tree_diff_node_t* parent, tree_diff_node_t* left, tree_diff_node_t* right){
    assert(parent);
    
    if(left != NULL){
        set_node_left   (parent, left);
        set_node_parent (left, parent);
    }
    if(right != NULL){
        set_node_right  (parent, right);
        set_node_parent (right, parent);
    }
}    
//-----------------------------------------------------------------
void set_node_left(tree_diff_node_t* node, tree_diff_node_t* left){
    assert(node);
    node->left = left;
    return;
}
//-----------------------------------------------------------------
void set_node_right(tree_diff_node_t* node, tree_diff_node_t* right){
    assert(node);
    node->right = right;
    return;
}
//-----------------------------------------------------------------
void set_node_parent(tree_diff_node_t* node, tree_diff_node_t* parent){
    assert(node);
    node->parent = parent;
    return;
}
//-----------------------------------------------------------------
bool is_node_have_left(tree_diff_node_t* node){
    assert(node);
    return (node->left != NULL);
}
//-----------------------------------------------------------------
bool is_node_have_right(tree_diff_node_t* node){
    assert(node);
    return (node->right != NULL);
}
//-----------------------------------------------------------------
bool is_node_have_parent(tree_diff_node_t* node){
    assert(node);
    return (node->parent != NULL);
}
//-----------------------------------------------------------------
void tex_viz_of_tree(tree_diff_node_t* node, FILE* tex_file){
    assert(node);
    assert(tex_file);

    fprintf(tex_file, "$");
    tex_viz_of_nodes(node, tex_file);
    fprintf(tex_file, "$");
}
//-----------------------------------------------------------------
void tex_viz_of_nodes(tree_diff_node_t* node, FILE* tex_file){
    assert(node);
    assert(tex_file);

    if(node->type == NUM){ 
        printf("%lg\n", node->val);
        fprintf(tex_file, "{%lg}", node->val);
        return;
    }
    if(node->type == VAR){
        switch((int) node->val){
            case 0:
                fprintf(tex_file, "{x}");
                return;
            case 1:
                fprintf(tex_file, "{y}");
                return;
            default:
                fprintf(tex_file, "Invalid variable\n");
                return;
        }
    }
    if(node->type == OP){
        switch ((int) node->val){
        case 0:
            fprintf(tex_file, "(");
            tex_viz_of_nodes(node->left, tex_file);
            fprintf(tex_file, "+");
            tex_viz_of_nodes(node->right, tex_file);
            fprintf(tex_file, ")");
            return;
        case 1:
            fprintf(tex_file, "(");
            tex_viz_of_nodes(node->left, tex_file);
            fprintf(tex_file, "-");
            tex_viz_of_nodes(node->right, tex_file);
            fprintf(tex_file, ")");
            return;
        case 2:
            tex_viz_of_nodes(node->left, tex_file);
            fprintf(tex_file, "\\cdot");
            tex_viz_of_nodes(node->right, tex_file);
            return;
        case 3:
            fprintf(tex_file, "\\frac{");
            tex_viz_of_nodes(node->left, tex_file);
            fprintf(tex_file, "}");
            fprintf(tex_file, "{");
            tex_viz_of_nodes(node->right, tex_file);
            fprintf(tex_file, "}");
            return;
        case 4:
            fprintf(tex_file, "({");
            tex_viz_of_nodes(node->left, tex_file);
            fprintf(tex_file, "})");
            fprintf(tex_file, "^");
            fprintf(tex_file, "{");
            tex_viz_of_nodes(node->right, tex_file);
            fprintf(tex_file, "}");
            return;
        case 5:
            fprintf(tex_file, "{log_{");
            tex_viz_of_nodes(node->left, tex_file);
            fprintf(tex_file, "}");
            fprintf(tex_file, " ");
            fprintf(tex_file, "{");
            tex_viz_of_nodes(node->right, tex_file);
            fprintf(tex_file, "}}");
            return;
        case 6:
            fprintf(tex_file, "\\sin({");
            tex_viz_of_nodes(node->left, tex_file);
            fprintf(tex_file, "})");
            return;
        case 7:
            fprintf(tex_file, "\\cos({");
            tex_viz_of_nodes(node->left, tex_file);
            fprintf(tex_file, "})");
            return;
        case 8:
            fprintf(tex_file, "\\tan({");
            tex_viz_of_nodes(node->left, tex_file);
            fprintf(tex_file, "})");
            return;
        case 9:
            fprintf(tex_file, "\\cot({");
            tex_viz_of_nodes(node->left, tex_file);
            fprintf(tex_file, "})");
            return;
        case 10:
            fprintf(tex_file, "\\arcsin({");
            tex_viz_of_nodes(node->left, tex_file);
            fprintf(tex_file, "})");
            return;
        case 11:
            fprintf(tex_file, "\\arccos({");
            tex_viz_of_nodes(node->left, tex_file);
            fprintf(tex_file, "})");
            return;
        case 12:
            fprintf(tex_file, "\\arctan({");
            tex_viz_of_nodes(node->left, tex_file);
            fprintf(tex_file, "})");
            return;
        case 13:
            fprintf(tex_file, "\\arctan({");//////fix in tex net arccot
            tex_viz_of_nodes(node->left, tex_file);
            fprintf(tex_file, "})");  
            return;  
        default:
            fprintf(tex_file, "Invalid type of operation\n");
            return;
        }
    }

    fprintf(tex_file, "Invalid type of node\n");
}
//-----------------------------------------------------------------
void tree_viz(tree_diff_node_t* root, FILE* viz_file){
    assert(root);
    assert(viz_file);

    fprintf(viz_file, "digraph{\n");
    create_node_viz(root, viz_file);
    create_edge_viz(root, viz_file);
    fprintf(viz_file, "}");
}
//----------------------------------------------------------------------------
void create_node_viz(tree_diff_node_t* node, FILE* viz_file){
    assert(node);
    assert(viz_file);

    switch(node->type){
        case OP:
            create_op_node_viz(node, viz_file);
            break;
        case VAR:
            create_var_node_viz(node, viz_file);
            break;
        case NUM:
            create_num_node_viz(node, viz_file);
            break;
        default:
            printf("Error type node\n");
            break;
    }

    if(is_node_have_left(node))  create_node_viz(node->left,  viz_file); 
    if(is_node_have_right(node)) create_node_viz(node->right, viz_file);
    
    if(is_node_have_left(node) && is_node_have_right(node)){
        fprintf(viz_file, "{rank = same; node%p; node%p};\n", (void*) node->left, (void*) node->right);
    }
}
//----------------------------------------------------------------------------
void create_op_node_viz(tree_diff_node_t* node, FILE* viz_file){
    assert(node);
    assert(viz_file);
    assert(node->type == OP);

    const size_t max_size_of_oper_name = 10;
    char oper_name[max_size_of_oper_name] = "";

    switch ((int) node->val/*fix enum*/)
    {
    case 0:
        strcpy(oper_name, "+");
        break;  
    case 1:
        strcpy(oper_name, "-");
        break;
    case 2:
        strcpy(oper_name, "*");
        break;
    case 3:
        strcpy(oper_name, "/");
        break;
    case 4:   
        strcpy(oper_name, "^");
        break;
    case 5:
        strcpy(oper_name, "log");
        break;
    case 6:
        strcpy(oper_name, "sin");
        break;
    case 7:
        strcpy(oper_name, "cos");
        break;
    case 8:
        strcpy(oper_name, "tg");
        break;  
    case 9:
        strcpy(oper_name, "ctg");
        break;        
    case 10:
        strcpy(oper_name, "arcsin");
        break;
    case 11:
        strcpy(oper_name, "arccos");
        break;
    case 12:
        strcpy(oper_name, "arctg");
        break;  
    case 13:
        strcpy(oper_name, "arcctg");
        break;                
    default:
        printf("Invalid type of operatiom\n");
        break;
    }
    fprintf(viz_file, "node%p[shape = circle, label = \"%s\", style = \"filled\", fillcolor = \"#8cd1e4\"];\n", (void*) node, oper_name);

}
//----------------------------------------------------------------------------
void create_var_node_viz(tree_diff_node_t* node, FILE* viz_file){
    assert(node);
    assert(viz_file);
    assert(node->type == VAR);

    const size_t max_size_of_var_name = 4;
    char var_name[max_size_of_var_name] = "";

    switch((int) node->val){
        case 0:
            strcpy(var_name, "x");
            break;
        case 1:
            strcpy(var_name, "y");
            break;
    }
    fprintf(viz_file, "node%p[shape = square, label = \"%s\", style = \"filled\", fillcolor = \"#fff0b6\"];\n", (void*) node, var_name);

}
//----------------------------------------------------------------------------
void create_num_node_viz(tree_diff_node_t* node, FILE* viz_file){
    assert(node);
    assert(viz_file);
    assert(node->type == NUM);

    fprintf(viz_file, "node%p[shape = Mrecord, label = \"%lg\", style = \"filled\", fillcolor = \"#f79eef\"];\n", (void*) node, node->val);
}
//----------------------------------------------------------------------------
void create_edge_viz(tree_diff_node_t* node, FILE* viz_file){
    assert(node);
    assert(viz_file);

    if(is_node_have_left(node)){ 
        fprintf(viz_file, "node%p->node%p;\n", (void*) node, (void*) node->left);
        create_edge_viz(node->left, viz_file);
    }
    if(is_node_have_right(node)){ 
        fprintf(viz_file, "node%p->node%p;\n", (void*) node, (void*) node->right);
        create_edge_viz(node->right, viz_file);
    }      
}

//----------------------------------------------------------------------------
double  calculate_subtree(tree_diff_node_t* node, double val_of_var){
    assert(node);

    if(node->type == NUM) return node->val;
    if(node->type == VAR) return val_of_var;//////fix val of var
    if(node->type == OP){
        double operand1 = NAN;
        double operand2 = NAN;
        if(is_node_have_left(node))  operand1 = calculate_subtree(node->left, val_of_var);
        if(is_node_have_right(node)) operand2 = calculate_subtree(node->right, val_of_var);
        return calculate_operation(node, operand1, operand2);
    }

    return NAN;
}
//----------------------------------------------------------------------------
double calculate_operation(tree_diff_node_t* node, double operand1, double operand2){
    assert(node);
    assert(node->type == OP);

    if(isnan(operand1) && isnan(operand2)){
            printf("Operands error\n");
            assert(0);
    }    

    switch ((int) node->val/*fix enum*/)
    {
    case 0: return operand1 + operand2;
    case 1: return operand1 - operand2;
    case 2: return operand1 * operand2;
    case 3:
        if(operand2 == 0){
            printf("Division by zero\n");
            assert(0);
        }     
        return operand1 / operand2;
    case 4: return pow(operand1, operand2);
    case 5: return log(operand2) / log(operand1);
    case 6: return sin(operand1);
    case 7: return cos(operand1);
    case 8: return tan(operand1);
    case 9: return 1 / tan(operand1);
    case 10: return asin(operand1); 
    case 11: return acos(operand1);
    case 12: return atan(operand1);
    case 13: return (M_PI / 2) - atan(operand1);


    default:
        printf("Invalid type of operatiom\n");
        return NAN;
    }
}
//----------------------------------------------------------------------------
double calculate_constant_subtree(tree_diff_node_t* node){
    assert(node);

    if(node->type == VAR) return NAN;
    if(node->type == NUM) return node->val;
    if(node->type == OP){
        double operand1 = NAN;
        double operand2 = NAN;
        if(is_node_have_left(node)){
            operand1 = calculate_constant_subtree(node->left);
            if(operand1 == NAN) return NAN;
        }
        if(is_node_have_right(node)){
            operand2 = calculate_constant_subtree(node->right);
            if(operand2 == NAN) return NAN;
        }
        if(!is_node_have_left(node) && !is_node_have_right(node)){
            return NAN;
        }
        return calculate_operation(node, operand1, operand2);
    }

    return NAN;
}
//----------------------------------------------------------------------------
void constant_folding_tree(tree_diff_node_t* node){
    assert(node);

    double value = calculate_constant_subtree(node);
    if(value != NAN){
        tree_diff_node_t* value_of_tree = _NUM(value);
        if(is_node_have_left(node))  delete_tree(node->left);
        if(is_node_have_right(node)) delete_tree(node->right);
    
        node_copy_without_new_node(node, value_of_tree);
        free(value_of_tree);
        return;
    }

    if( is_node_have_left(node)) constant_folding_tree(node->left);
    if(is_node_have_right(node)) constant_folding_tree(node->right);

    return;
}
//----------------------------------------------------------------------------
tree_diff_node_t* diff(tree_diff_node_t* node){
    assert(node);

    if(node->type == NUM) return _NUM(0);
    if(node->type == VAR) return _NUM(1);
    if(node->type == OP){
        switch((int) node->val){
            case 0:
                return deritative_sum(node);
            case 1:
                return deritative_difference(node);
            case 2:
                return deritative_product(node);
            case 3:
                return deritative_quotient(node);
            case 4:
                return deritative_general_pow_function(node);
            case 5:
                return deritative_log_function(node);
            case 6:
                return deritative_sin(node);
            case 7:
                return deritative_cos(node);
            case 8:
                return deritative_tg(node);
            case 9:
                return deritative_ctg(node);   
            case 10:
                return deritative_arcsin(node);
            case 11:
                return deritative_arccos(node);
            case 12:
                return deritative_arctg(node);
            case 13:
                return deritative_arcctg(node);     
            default:
                return NULL;
        }
    }

    printf("ERROR NODE TYPE\n");
    return NULL;
}
//----------------------------------------------------------------------------
tree_diff_node_t* deritative_sum(tree_diff_node_t* node){
    assert(node);
    assert(node->type == OP);
    assert((int) node->val == 0);

    tree_diff_node_t* add_node = _OP(0);
    tree_diff_node_t* diff_left  = _DIFFL(node);
    tree_diff_node_t* diff_right = _DIFFR(node);
    link_nodes(add_node, diff_left, diff_right);
    return add_node;
}
//----------------------------------------------------------------------------
tree_diff_node_t* deritative_difference(tree_diff_node_t* node){
    assert(node);
    assert(node->type == OP);
    assert((int) node->val == 1);

    tree_diff_node_t* sub_node = _OP(1);
    tree_diff_node_t* diff_left  = _DIFFL(node);
    tree_diff_node_t* diff_right = _DIFFR(node);
    link_nodes(sub_node, diff_left, diff_right);
    return sub_node;
}
//----------------------------------------------------------------------------
tree_diff_node_t* deritative_product(tree_diff_node_t* node){
    assert(node);
    assert(node->type == OP);
    assert((int) node->val == 2);

    tree_diff_node_t* add_node  = _OP(0);
    tree_diff_node_t* mul_node1 = _OP(2);
    tree_diff_node_t* mul_node2 = _OP(2);
    link_nodes(add_node, mul_node1, mul_node2);

    tree_diff_node_t* diff_left  = _DIFFL(node);
    tree_diff_node_t* right_copy = _COPYR(node);
    link_nodes(mul_node1, diff_left, right_copy);

    tree_diff_node_t* diff_right = _DIFFR(node);
    tree_diff_node_t* left_copy = _COPYL(node);
    link_nodes(mul_node2, diff_right, left_copy);

    return add_node;
}
//----------------------------------------------------------------------------
tree_diff_node_t* deritative_quotient(tree_diff_node_t* node){
    assert(node);
    assert(node->type == OP);
    assert((int) node->val == 3);

    tree_diff_node_t* div_node = _OP(3);
    
    tree_diff_node_t* sub_node  = _OP(1);
    tree_diff_node_t* mul_sqr_node = _OP(2);
    link_nodes(div_node, sub_node, mul_sqr_node);

    tree_diff_node_t* mul_node1 = _OP(2);
    tree_diff_node_t* mul_node2 = _OP(2);
    link_nodes(sub_node, mul_node1, mul_node2);

    tree_diff_node_t* diff_left  = _DIFFL(node);
    tree_diff_node_t* right_copy1 = _COPYR(node);
    link_nodes(mul_node1, diff_left, right_copy1);

    tree_diff_node_t* diff_right = _DIFFR(node);
    tree_diff_node_t* left_copy = _COPYL(node);
    link_nodes(mul_node2, diff_right, left_copy);

    tree_diff_node_t* right_copy2 = _COPYR(node);// возможно не надо две копии создавать, подумать над этим
    tree_diff_node_t* right_copy3 = _COPYR(node);
    link_nodes(mul_sqr_node, right_copy2, right_copy3);

    return div_node;
 
}
//----------------------------------------------------------------------------
tree_diff_node_t* deritative_general_pow_function(tree_diff_node_t* node){
    assert(node);
    assert(node->type == OP);
    assert((int) node->val == 4);

    if((node->right)->type == NUM && (node->left)->type == NUM) return _NUM(0);
    if((node->right)->type == NUM) return deritative_pow_function(node);
    if((node->left)->type == NUM) return deritative_exponential_function(node);

    return deritative_pow_and_exponential_function(node);
}
//----------------------------------------------------------------------------
tree_diff_node_t* deritative_pow_function(tree_diff_node_t* node){
    assert(node);
    assert(node->type == OP);
    assert((int) node->val == 4);
    assert((node->right)->type == NUM);

    if((node->left)->type == NUM) return _NUM(0);
    if((node->left)->type == VAR){
        tree_diff_node_t* mul_node = _OP(2);
        tree_diff_node_t* first_factor = _NUM((node->right)->val);
        tree_diff_node_t* second_factor = _OP(4);
        link_nodes(mul_node, first_factor, second_factor);

        tree_diff_node_t* var_node = _VAR((node->left)->val);
        tree_diff_node_t* pow_node = _NUM(((node->right)->val) - 1);
        link_nodes(second_factor, var_node, pow_node);
        return mul_node;
    }
    if((node->left)->type == OP){
        tree_diff_node_t* global_mul_mode = _OP(2);
        tree_diff_node_t* first_global_factor = _OP(2);
        tree_diff_node_t* second_global_factor = _DIFFL(node);
        link_nodes(global_mul_mode, first_global_factor, second_global_factor);

        tree_diff_node_t* first_factor = _NUM((node->right)->val);
        tree_diff_node_t* second_factor = _OP(4);
        link_nodes(first_global_factor, first_factor, second_factor);

        tree_diff_node_t* base_of_power = _COPYL(node);
        tree_diff_node_t* exponent_of_power = _NUM(((node->right)->val) - 1);
        link_nodes(second_factor, base_of_power, exponent_of_power);

        return global_mul_mode;
    }

    printf("INVALID NODE TYPE\n");
    return NULL;
}
//----------------------------------------------------------------------------
tree_diff_node_t* deritative_exponential_function(tree_diff_node_t* node){
    assert(node);
    assert(node->type == OP);
    assert((int) node->val == 4);
    assert((node->left)->type == NUM);

    if((node->right)->type == NUM) return _NUM(0);
    if((node->right)->type == VAR){
        tree_diff_node_t* mul_node = _OP(2);
        tree_diff_node_t* first_factor = _OP(4);
        tree_diff_node_t* second_factor = _OP(5);
        link_nodes(mul_node, first_factor, second_factor);

        tree_diff_node_t* base_of_power = _NUM((node->left)->val);
        tree_diff_node_t* exponent_of_power = _VAR(node->val);
        link_nodes(first_factor, base_of_power, exponent_of_power);

        tree_diff_node_t* base_of_logarithm = _NUM(M_E);
        tree_diff_node_t* argument_of_logarithm = _NUM((node->left)->val);
        link_nodes(second_factor, base_of_logarithm, argument_of_logarithm);

        return mul_node;
    }
    if((node->right)->type == OP){
        tree_diff_node_t* global_mul_node = _OP(2);
        tree_diff_node_t* first_global_factor = _OP(2);
        tree_diff_node_t* second_global_factor = _DIFFR(node);
        link_nodes(global_mul_node, first_global_factor, second_global_factor);

        tree_diff_node_t* first_factor = _OP(4);
        tree_diff_node_t* second_factor = _OP(5);
        link_nodes(first_global_factor, first_factor, second_factor);

        tree_diff_node_t* base_of_power = _NUM((node->left)->val);
        tree_diff_node_t* exponent_of_power = _COPYR(node);
        link_nodes(first_factor, base_of_power, exponent_of_power);

        tree_diff_node_t* base_of_logarithm = _NUM(M_E);
        tree_diff_node_t* argument_of_logarithm = _NUM((node->left)->val);
        link_nodes(second_factor, base_of_logarithm, argument_of_logarithm);

        return global_mul_node;
    }

    printf("INVALID NODE TYPE\n");
    return NULL;
}
//----------------------------------------------------------------------------
tree_diff_node_t* deritative_pow_and_exponential_function(tree_diff_node_t* node){
    assert(node);
    assert(node->type == OP);
    assert((int) node->val == 4);
    assert((node->left)->type != NUM && (node->right)->type != NUM);

    tree_diff_node_t* global_mul_node = _OP(2);
    tree_diff_node_t* global_first_factor = _OP(4);
    tree_diff_node_t* global_second_factor = _OP(0);
    link_nodes(global_mul_node, global_first_factor, global_second_factor);

    tree_diff_node_t* base_of_power = _COPYL(node);
    tree_diff_node_t* exponent_of_power = _COPYR(node);
    link_nodes(global_first_factor, base_of_power, exponent_of_power);

    tree_diff_node_t* first_addend = _OP(2);
    tree_diff_node_t* second_addend = _OP(2);
    link_nodes(global_second_factor, first_addend, second_addend);

    tree_diff_node_t* first_factor_in_first_addend = _DIFFR(node);
    tree_diff_node_t* second_factor_in_first_addend = _OP(5);
    tree_diff_node_t* base_of_logarithm = _NUM(M_E);
    tree_diff_node_t* argument_of_logarithm = _COPYL(node);
    link_nodes(first_addend, first_factor_in_first_addend, second_factor_in_first_addend);
    link_nodes(second_factor_in_first_addend, base_of_logarithm, argument_of_logarithm);

    tree_diff_node_t* first_factor_in_second_addend = _COPYR(node);
    tree_diff_node_t* second_factor_in_second_addend = _OP(3);
    tree_diff_node_t* numerator_node = _DIFFL(node);
    tree_diff_node_t* denumerator_node = _COPYL(node);
    link_nodes(second_addend, first_factor_in_second_addend, second_factor_in_second_addend);
    link_nodes(second_factor_in_second_addend, numerator_node, denumerator_node);

    return global_mul_node;
}
//----------------------------------------------------------------------------
tree_diff_node_t* deritative_log_function(tree_diff_node_t* node){
    assert(node);
    assert(node->type == OP);
    assert((int) node->val == 5);

    if((node->right)->type == NUM && (node->left)->type == NUM) return _NUM(0);
    if((node->left)->type == NUM) return deritative_log_with_const_base_function(node);  
    
    return deritative_general_log_function(node);
}
//----------------------------------------------------------------------------
tree_diff_node_t* deritative_log_with_const_base_function(tree_diff_node_t* node){
    assert(node);
    assert(node->type == OP);
    assert((int) node->type == 5);
    assert((node->left)->type == NUM);

    if((node->right)->type == NUM) return _NUM(0);
    if((node->right)->type == VAR || (node->right)->type == OP){
        tree_diff_node_t* div_node = _OP(3);
        tree_diff_node_t* numerator_node = _DIFFR(node);
        tree_diff_node_t* denumerator_node = _OP(2);
        link_nodes(div_node, numerator_node, denumerator_node);

        tree_diff_node_t* first_factor_in_denumerator = _COPYR(node);
        tree_diff_node_t* second_factor_in_denumerator = _OP(5);
        tree_diff_node_t* base_of_logarithm = _NUM(M_E);
        tree_diff_node_t* argument_of_logarithm = _NUM((node->left)->val);
        link_nodes(denumerator_node, first_factor_in_denumerator, second_factor_in_denumerator);
        link_nodes(second_factor_in_denumerator, base_of_logarithm, argument_of_logarithm);

        return div_node;
    }

    
    printf("INVALID NODE TYPE\n");
    return NULL;
}
//----------------------------------------------------------------------------
tree_diff_node_t* deritative_general_log_function(tree_diff_node_t* node){
    assert(node);
    assert(node->type == OP);
    assert(node->val == 5);

    tree_diff_node_t* div_node = _OP(3);
    tree_diff_node_t* numerator = _OP(1);
    //------------
    tree_diff_node_t* denumerator = _OP(4);
    tree_diff_node_t* base_of_pow = _OP(5);
    tree_diff_node_t* pow = _NUM(2);
    link_nodes(denumerator, base_of_pow, pow);
    tree_diff_node_t* base_log_denum = _NUM(M_E);
    tree_diff_node_t* arg_log_denum = _COPYL(node);
    link_nodes(base_of_pow, base_log_denum, arg_log_denum);
    //-------------
    link_nodes(div_node, numerator, denumerator);
    //-------------
    tree_diff_node_t* minuend = _OP(2);
    tree_diff_node_t* first_factor_minuend = _OP(3);
    tree_diff_node_t* second_factor_minuend = _OP(5);
    link_nodes(minuend, first_factor_minuend, second_factor_minuend);

    tree_diff_node_t* numerator_first_fact_min = _DIFFR(node);
    tree_diff_node_t* denumerator_first_fact_min = _COPYR(node);
    link_nodes(first_factor_minuend, numerator_first_fact_min, denumerator_first_fact_min);

    tree_diff_node_t* base_log_minuend = _NUM(M_E); 
    tree_diff_node_t* arg_log_minuend = _COPYL(node);
    link_nodes(second_factor_minuend, base_log_minuend, arg_log_minuend);
    //-------------
    tree_diff_node_t* subtrahend = _OP(2);
    tree_diff_node_t* first_factor_subtrahend = _OP(3);
    tree_diff_node_t* second_factor_subtrahend = _OP(5);
    link_nodes(subtrahend, first_factor_subtrahend, second_factor_subtrahend);

    tree_diff_node_t* numerator_first_fact_sub = _DIFFL(node);
    tree_diff_node_t* denumerator_first_fact_sub = _COPYL(node);
    link_nodes(first_factor_subtrahend, numerator_first_fact_sub, denumerator_first_fact_sub);

    tree_diff_node_t* base_log_subtrahend = _NUM(M_E); 
    tree_diff_node_t* arg_log_subtrahend = _COPYR(node);
    link_nodes(second_factor_subtrahend, base_log_subtrahend, arg_log_subtrahend);
    //-------------
    link_nodes(numerator, minuend, subtrahend);

    return div_node;
}
//----------------------------------------------------------------------------
tree_diff_node_t* deritative_sin(tree_diff_node_t* node){
    assert(node);
    assert(node->type == OP);
    assert((int) node->val == 6);

    tree_diff_node_t* mul_node = _OP(2);
    tree_diff_node_t* cos_node = _OP(7);
    tree_diff_node_t* cos_arg = _COPYL(node);
    link_nodes(cos_node, cos_arg, NULL);
    tree_diff_node_t* second_factor = _DIFFL(node);
    link_nodes(mul_node, cos_node, second_factor);

    return mul_node;
}
//----------------------------------------------------------------------------
tree_diff_node_t* deritative_cos(tree_diff_node_t* node){
    assert(node);
    assert(node->type == OP);
    assert((int) node->val == 7);

    tree_diff_node_t* mul_node = _OP(2);
    tree_diff_node_t* negative_mul_node = _OP(2);
    tree_diff_node_t* minus_one = _NUM(-1);
    tree_diff_node_t* sin_node = _OP(6);
    link_nodes(negative_mul_node, minus_one, sin_node);
    tree_diff_node_t* sin_arg = _COPYL(node);
    link_nodes(sin_node, sin_arg, NULL);
    tree_diff_node_t* second_factor = _DIFFL(node);
    link_nodes(mul_node, negative_mul_node, second_factor);

    return mul_node;
}
//----------------------------------------------------------------------------
tree_diff_node_t* deritative_tg(tree_diff_node_t* node){
    assert(node);
    assert(node->type == OP);
    assert((int) node->val == 8);

    tree_diff_node_t* mul_node = _OP(2);
    tree_diff_node_t* first_factor = _OP(3);
    tree_diff_node_t* second_factor = _DIFFL(node);
    link_nodes(mul_node, first_factor, second_factor);

    tree_diff_node_t* num_first_factor = _NUM(1);
    tree_diff_node_t* denum_first_factor = _OP(4);
    link_nodes(first_factor, num_first_factor, denum_first_factor);

    tree_diff_node_t* cos_node = _OP(7);
    tree_diff_node_t* cos_arg = _COPYL(node); 
    link_nodes(cos_node, cos_arg, NULL);

    tree_diff_node_t* exp_of_cos = _NUM(2);
    link_nodes(denum_first_factor, cos_node, exp_of_cos);

    return mul_node;
}
//----------------------------------------------------------------------------
tree_diff_node_t* deritative_ctg(tree_diff_node_t* node){
    assert(node);
    assert(node->type == OP);
    assert((int) node->val == 9);

    tree_diff_node_t* mul_node = _OP(2);
    tree_diff_node_t* negative_first_factor = _OP(2);
    tree_diff_node_t* second_factor = _DIFFL(node);
    link_nodes(mul_node, negative_first_factor, second_factor);

    tree_diff_node_t* minus_one = _NUM(-1);
    tree_diff_node_t* fraction = _OP(3);
    link_nodes(negative_first_factor, minus_one, fraction);

    tree_diff_node_t* num_of_fraction = _NUM(1);
    tree_diff_node_t* denum_of_fraction = _OP(4);
    link_nodes(fraction, num_of_fraction, denum_of_fraction);

    tree_diff_node_t* sin_node = _OP(6);
    tree_diff_node_t* sin_arg = _COPYL(node); 
    link_nodes(sin_node, sin_arg, NULL);

    tree_diff_node_t* exp_of_sin = _NUM(2);
    link_nodes(denum_of_fraction, sin_node, exp_of_sin);

    return mul_node;
}
//----------------------------------------------------------------------------
tree_diff_node_t* deritative_arcsin(tree_diff_node_t* node){
    assert(node);

    tree_diff_node_t* mul_node = _OP(2);
    tree_diff_node_t* first_factor = _OP(3);
    tree_diff_node_t* second_factor = _DIFFL(node);
    link_nodes(mul_node, first_factor, second_factor);

    tree_diff_node_t* numerator = _NUM(1);
    tree_diff_node_t* denumerator = _OP(4);
    link_nodes(first_factor, numerator, denumerator);

    tree_diff_node_t* base_of_pow = _OP(1);
    tree_diff_node_t* exp_of_pow = _NUM(0.5);
    link_nodes(denumerator, base_of_pow, exp_of_pow);

    tree_diff_node_t* minuend = _NUM(1);
    tree_diff_node_t* subtrahend = _OP(4);
    link_nodes(base_of_pow, minuend, subtrahend);
    
    tree_diff_node_t* base_of_pow_subtrahend = _COPYL(node);
    tree_diff_node_t* exp_of_pow_subtrahend = _NUM(2);
    link_nodes(subtrahend, base_of_pow_subtrahend, exp_of_pow_subtrahend);

    return mul_node;
}
//----------------------------------------------------------------------------
tree_diff_node_t* deritative_arccos(tree_diff_node_t* node){
    assert(node);

    tree_diff_node_t* mul_node = _OP(2);
    tree_diff_node_t* first_factor = _OP(3);
    tree_diff_node_t* second_factor = _DIFFL(node);
    link_nodes(mul_node, first_factor, second_factor);

    tree_diff_node_t* numerator = _NUM(-1);
    tree_diff_node_t* denumerator = _OP(4);
    link_nodes(first_factor, numerator, denumerator);

    tree_diff_node_t* base_of_pow = _OP(1);
    tree_diff_node_t* exp_of_pow = _NUM(0.5);
    link_nodes(denumerator, base_of_pow, exp_of_pow);

    tree_diff_node_t* minuend = _NUM(1);
    tree_diff_node_t* subtrahend = _OP(4);
    link_nodes(base_of_pow, minuend, subtrahend);
    
    tree_diff_node_t* base_of_pow_subtrahend = _COPYL(node);
    tree_diff_node_t* exp_of_pow_subtrahend = _NUM(2);
    link_nodes(subtrahend, base_of_pow_subtrahend, exp_of_pow_subtrahend);

    return mul_node;
}
//----------------------------------------------------------------------------
tree_diff_node_t* deritative_arctg(tree_diff_node_t* node){
    assert(node);

    tree_diff_node_t* mul_node = _OP(2);
    tree_diff_node_t* first_factor = _OP(3);
    tree_diff_node_t* second_factor = _DIFFL(node);
    link_nodes(mul_node, first_factor, second_factor);

    tree_diff_node_t* numerator = _NUM(1);
    tree_diff_node_t* denumerator = _OP(0);
    link_nodes(first_factor, numerator, denumerator);

    tree_diff_node_t* first_addend = _NUM(1);
    tree_diff_node_t* second_addend = _OP(4);
    link_nodes(denumerator, first_addend, second_addend);

    tree_diff_node_t* base_of_pow = _COPYL(node);
    tree_diff_node_t* exp_of_pow = _NUM(2);
    link_nodes(second_addend, base_of_pow, exp_of_pow);

    return mul_node;
}
//----------------------------------------------------------------------------
tree_diff_node_t* deritative_arcctg(tree_diff_node_t* node){
    assert(node);

    tree_diff_node_t* mul_node = _OP(2);
    tree_diff_node_t* first_factor = _OP(3);
    tree_diff_node_t* second_factor = _DIFFL(node);
    link_nodes(mul_node, first_factor, second_factor);

    tree_diff_node_t* numerator = _NUM(-1);
    tree_diff_node_t* denumerator = _OP(0);
    link_nodes(first_factor, numerator, denumerator);

    tree_diff_node_t* first_addend = _NUM(1);
    tree_diff_node_t* second_addend = _OP(4);
    link_nodes(denumerator, first_addend, second_addend);

    tree_diff_node_t* base_of_pow = _COPYL(node);
    tree_diff_node_t* exp_of_pow = _NUM(2);
    link_nodes(second_addend, base_of_pow, exp_of_pow);

    return mul_node;
}
//----------------------------------------------------------------------------
tree_diff_node_t* subtree_copy(tree_diff_node_t* node){
    assert(node);

    tree_diff_node_t* left_child = NULL;
    tree_diff_node_t* right_child = NULL;
    if(is_node_have_left(node))  left_child  = subtree_copy(node->left);
    if(is_node_have_right(node)) right_child = subtree_copy(node->right);

    tree_diff_node_t* copy_node = node_copy(node);
    if(left_child != NULL || right_child != NULL) link_nodes(copy_node, left_child, right_child);

    return copy_node;
}
//----------------------------------------------------------------------------
tree_diff_node_t* node_copy(tree_diff_node_t* node){
    assert(node);

    tree_diff_node_t* copy_node = (tree_diff_node_t*) calloc(1, sizeof(tree_diff_node_t));
    assert(copy_node);

    copy_node->type = node->type;
    copy_node->val = node->val;
    copy_node->left = node->left;
    copy_node->right = node->right;
    copy_node->parent = node->parent;

    return copy_node;
}
//----------------------------------------------------------------------------
tree_diff_node_t* node_copy_without_new_node(tree_diff_node_t* node_copy_to, tree_diff_node_t* node_copy_from){
    assert(node_copy_to);
    assert(node_copy_from);

    node_copy_to->type   = node_copy_from->type;
    node_copy_to->val    = node_copy_from->val;
    node_copy_to->left   = node_copy_from->left;
    node_copy_to->right  = node_copy_from->right;
    node_copy_to->parent = node_copy_from->parent;

    return node_copy_to;
}
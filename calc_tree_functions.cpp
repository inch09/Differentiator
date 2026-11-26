#include <stdio.h>
#include "defines.h"
#include "dsl.h"
#include "general_func_tree.h"
#include "calc_tree_functions.h"
#include <assert.h>
#include <malloc.h>
#include <math.h>


double  calculate_subtree(tree_diff_node_t* node, double val_of_var){
    assert(node);

    if(node->type == NUM) return (node->val).num;
    if(node->type == VAR) return val_of_var;
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

    switch ((node->val).op_type)
    {
    case ADD: return operand1 + operand2;
    case SUB: return operand1 - operand2;
    case MUL: return operand1 * operand2;
    case DIV:
        if(operand2 == 0){
            printf("Division by zero\n");
            assert(0);
        }     
        return operand1 / operand2;
    case POW: return pow(operand1, operand2);
    case LOG: return log(operand2) / log(operand1);
    case SIN: return sin(operand1);
    case COS: return cos(operand1);
    case TG: return tan(operand1);
    case CTG: return 1 / tan(operand1);
    case ARCSIN: return asin(operand1); 
    case ARCCOS: return acos(operand1);
    case ARCTG: return atan(operand1);
    case ARCCTG: return (M_PI / 2) - atan(operand1);


    default:
        printf("Invalid type of operatiom\n");
        return NAN;
    }
}
//----------------------------------------------------------------------------
double calculate_constant_subtree(tree_diff_node_t* node){
    assert(node);

    if(node->type == VAR) return NAN;
    if(node->type == NUM) return (node->val).num;
    if(node->type == OP){
        double operand1 = NAN;
        double operand2 = NAN;
        if(is_node_have_left(node)){
            operand1 = calculate_constant_subtree(node->left);
            if(isnan(operand1)) return NAN;
        }
        if(is_node_have_right(node)){
            operand2 = calculate_constant_subtree(node->right);
            if(isnan(operand2)) return NAN;
        }
        if(!is_node_have_left(node) && !is_node_have_right(node)){
            return NAN;
        }
        if(isnan(operand1) && isnan(operand2)) return NAN;
        return calculate_operation(node, operand1, operand2);
    }

    return NAN;
}
//----------------------------------------------------------------------------
void constant_folding_tree(tree_diff_node_t* node){
    assert(node);

    double value = calculate_constant_subtree(node);
    if(!isnan(value)){
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
void delete_neutral_elements(tree_diff_node_t* node){
    assert(node);

    if(node->type == OP){
        if((node->val).op_type == ADD || (node->val).op_type == SUB) delete_neutral_add_and_sub_elements(node); 
        else if((node->val).op_type == MUL) delete_neutral_mul_elements(node);
        else if((node->val).op_type == DIV) delete_neutral_div_elements(node);
        else if((node->val).op_type == POW) delete_neutral_pow_elements(node);
    }
    
    if(is_node_have_left(node))  delete_neutral_elements(node->left);
    if(is_node_have_right(node)) delete_neutral_elements(node->right);

    return;
}
//----------------------------------------------------------------------------
void delete_neutral_add_and_sub_elements(tree_diff_node_t* node){
    assert(node);
    assert(node->type == OP);
    assert((node->val).op_type == ADD || (node->val).op_type == SUB);

    if((node->left)->type == NUM && ((node->left)->val).num == 0){
        tree_diff_node_t* copy_ptr = node->right;
        node_copy_without_new_node(node, node->right);
        link_nodes(node, node->left, node->right);
        free(copy_ptr);
    }
    else if((node->right)->type == NUM && ((node->right)->val).num == 0){
        tree_diff_node_t* copy_ptr = node->left;
        node_copy_without_new_node(node, node->left);
        link_nodes(node, node->left, node->right);
        free(copy_ptr);
    }
}
//----------------------------------------------------------------------------
void delete_neutral_mul_elements(tree_diff_node_t* node){
    assert(node);
    assert(node->type == OP);
    assert((node->val).op_type == MUL);

    if((node->left)->type == NUM && ((node->left)->val).num == 1){
        tree_diff_node_t* copy_ptr = node->right;
        node_copy_without_new_node(node, node->right);
        link_nodes(node, node->left, node->right);
        free(copy_ptr);
    }
    else if((node->right)->type == NUM && ((node->right)->val).num == 1){
        tree_diff_node_t* copy_ptr = node->left;
        node_copy_without_new_node(node, node->left);
        link_nodes(node, node->left, node->right);
        free(copy_ptr);
    }
    else if( ((node->left)->type == NUM &&  ((node->left)->val).num == 0) || 
            ((node->right)->type == NUM && ((node->right)->val).num == 0)){
        if(is_node_have_left(node))  delete_tree(node->left);
        if(is_node_have_right(node)) delete_tree(node->right);
        tree_diff_node_t* zero_node = _NUM(0);
        node_copy_without_new_node(node, zero_node);
        free(zero_node);
    }
}
//----------------------------------------------------------------------------
void delete_neutral_div_elements(tree_diff_node_t* node){
    assert(node);
    assert(node->type == OP);
    assert((node->val).op_type == DIV);

    if((node->right)->type == NUM && ((node->right)->val).num == 1){
        tree_diff_node_t* copy_ptr = node->left;
        node_copy_without_new_node(node, node->left);
        link_nodes(node, node->left, node->right);
        free(copy_ptr);
    }
    else if((node->left)->type == NUM && ((node->left)->val).num == 0){
        if(is_node_have_left(node))  delete_tree(node->left);
        if(is_node_have_right(node)) delete_tree(node->right);
        tree_diff_node_t* zero_node = _NUM(0);
        node_copy_without_new_node(node, zero_node);
        free(zero_node);
    }
}
//----------------------------------------------------------------------------
void delete_neutral_pow_elements(tree_diff_node_t* node){
    assert(node);
    assert(node->type == OP);
    assert((node->val).op_type == POW);

    if((node->left)->type == NUM && ((node->left)->val).num == 1){
        if(is_node_have_left(node))  delete_tree(node->left);
        if(is_node_have_right(node)) delete_tree(node->right);
        tree_diff_node_t* one_node = _NUM(1);
        node_copy_without_new_node(node, one_node);
        free(one_node);
    }
    else if((node->right)->type == NUM && ((node->right)->val).num == 1){
        tree_diff_node_t* copy_ptr = node->left;
        node_copy_without_new_node(node, node->left);
        link_nodes(node, node->left, node->right);
        free(copy_ptr);
    }
    else if((node->left)->type == NUM &&  ((node->left)->val).num == 0){
        if(is_node_have_left(node))  delete_tree(node->left);
        if(is_node_have_right(node)) delete_tree(node->right);
        tree_diff_node_t* zero_node = _NUM(0);
        node_copy_without_new_node(node, zero_node);
        free(zero_node);
    }
    else if((node->right)->type == NUM && ((node->right)->val).num == 0){
        if(is_node_have_left(node))  delete_tree(node->left);
        if(is_node_have_right(node)) delete_tree(node->right);
        tree_diff_node_t* one_node = _NUM(1);
        node_copy_without_new_node(node, one_node);
        free(one_node);
    }
}
//----------------------------------------------------------------------------
tree_diff_node_t* diff(tree_diff_node_t* node){
    assert(node);

    if(node->type == NUM) return _NUM(0);
    if(node->type == VAR) return _NUM(1);
    if(node->type == OP){
        switch((node->val).op_type){
            case ADD:
                return deritative_sum(node);
            case SUB:
                return deritative_difference(node);
            case MUL:
                return deritative_product(node);
            case DIV:
                return deritative_quotient(node);
            case POW:
                return deritative_general_pow_function(node);
            case LOG:
                return deritative_log_function(node);
            case SIN:
                return deritative_sin(node);
            case COS:
                return deritative_cos(node);
            case TG:
                return deritative_tg(node);
            case CTG:
                return deritative_ctg(node);   
            case ARCSIN:
                return deritative_arcsin(node);
            case ARCCOS:
                return deritative_arccos(node);
            case ARCTG:
                return deritative_arctg(node);
            case ARCCTG:
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
    assert((node->val).op_type == ADD);

    tree_diff_node_t* add_node = _ADD();
    tree_diff_node_t* diff_left  = _DIFFL(node);
    tree_diff_node_t* diff_right = _DIFFR(node);
    link_nodes(add_node, diff_left, diff_right);
    return add_node;
}
//----------------------------------------------------------------------------
tree_diff_node_t* deritative_difference(tree_diff_node_t* node){
    assert(node);
    assert(node->type == OP);
    assert((node->val).op_type == SUB);

    tree_diff_node_t* sub_node = _SUB();
    tree_diff_node_t* diff_left  = _DIFFL(node);
    tree_diff_node_t* diff_right = _DIFFR(node);
    link_nodes(sub_node, diff_left, diff_right);
    return sub_node;
}
//----------------------------------------------------------------------------
tree_diff_node_t* deritative_product(tree_diff_node_t* node){
    assert(node);
    assert(node->type == OP);
    assert((node->val).op_type == MUL);

    tree_diff_node_t* add_node  = _ADD();
    tree_diff_node_t* mul_node1 = _MUL();
    tree_diff_node_t* mul_node2 = _MUL();
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
    assert((node->val).op_type == DIV);

    tree_diff_node_t* div_node = _DIV();
    
    tree_diff_node_t* sub_node  = _SUB();
    tree_diff_node_t* mul_sqr_node = _MUL();
    link_nodes(div_node, sub_node, mul_sqr_node);

    tree_diff_node_t* mul_node1 = _MUL();
    tree_diff_node_t* mul_node2 = _MUL();
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
    assert((node->val).op_type == POW);

    if((node->right)->type == NUM && (node->left)->type == NUM) return _NUM(0);
    if((node->right)->type == NUM) return deritative_pow_function(node);
    if((node->left)->type == NUM) return deritative_exponential_function(node);

    return deritative_pow_and_exponential_function(node);
}
//----------------------------------------------------------------------------
tree_diff_node_t* deritative_pow_function(tree_diff_node_t* node){
    assert(node);
    assert(node->type == OP);
    assert((node->val).op_type == POW);
    assert((node->right)->type == NUM);

    if((node->left)->type == NUM) return _NUM(0);
    if((node->left)->type == VAR){
        tree_diff_node_t* mul_node = _MUL();
        tree_diff_node_t* first_factor = _NUM(((node->right)->val).num);
        tree_diff_node_t* second_factor = _POW();
        link_nodes(mul_node, first_factor, second_factor);

        tree_diff_node_t* var_node = _VAR(((node->left)->val).var);
        tree_diff_node_t* pow_node = _NUM(((node->right)->val).num - 1);
        link_nodes(second_factor, var_node, pow_node);
        return mul_node;
    }
    if((node->left)->type == OP){
        tree_diff_node_t* global_mul_mode = _MUL();
        tree_diff_node_t* first_global_factor = _MUL();
        tree_diff_node_t* second_global_factor = _DIFFL(node);
        link_nodes(global_mul_mode, first_global_factor, second_global_factor);

        tree_diff_node_t* first_factor = _NUM(((node->right)->val).num);
        tree_diff_node_t* second_factor = _POW();
        link_nodes(first_global_factor, first_factor, second_factor);

        tree_diff_node_t* base_of_power = _COPYL(node);
        tree_diff_node_t* exponent_of_power = _NUM(((node->right)->val).num - 1);
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
    assert((node->val).op_type == POW);
    assert((node->left)->type == NUM);

    if((node->right)->type == NUM) return _NUM(0);
    if((node->right)->type == VAR){
        tree_diff_node_t* mul_node = _MUL();
        tree_diff_node_t* first_factor = _POW();
        tree_diff_node_t* second_factor = _LOG();
        link_nodes(mul_node, first_factor, second_factor);

        tree_diff_node_t* base_of_power = _NUM(((node->left)->val).num);
        tree_diff_node_t* exponent_of_power = _VAR((node->val).var);
        link_nodes(first_factor, base_of_power, exponent_of_power);

        tree_diff_node_t* base_of_logarithm = _NUM(M_E);
        tree_diff_node_t* argument_of_logarithm = _NUM(((node->left)->val).num);
        link_nodes(second_factor, base_of_logarithm, argument_of_logarithm);

        return mul_node;
    }
    if((node->right)->type == OP){
        tree_diff_node_t* global_mul_node = _MUL();
        tree_diff_node_t* first_global_factor = _MUL();
        tree_diff_node_t* second_global_factor = _DIFFR(node);
        link_nodes(global_mul_node, first_global_factor, second_global_factor);

        tree_diff_node_t* first_factor = _POW();
        tree_diff_node_t* second_factor = _LOG();
        link_nodes(first_global_factor, first_factor, second_factor);

        tree_diff_node_t* base_of_power = _NUM(((node->left)->val).num);
        tree_diff_node_t* exponent_of_power = _COPYR(node);
        link_nodes(first_factor, base_of_power, exponent_of_power);

        tree_diff_node_t* base_of_logarithm = _NUM(M_E);
        tree_diff_node_t* argument_of_logarithm = _NUM(((node->left)->val).num);
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
    assert((node->val).op_type == POW);
    assert((node->left)->type != NUM && (node->right)->type != NUM);

    tree_diff_node_t* global_mul_node = _MUL();
    tree_diff_node_t* global_first_factor = _POW();
    tree_diff_node_t* global_second_factor = _ADD();
    link_nodes(global_mul_node, global_first_factor, global_second_factor);

    tree_diff_node_t* base_of_power = _COPYL(node);
    tree_diff_node_t* exponent_of_power = _COPYR(node);
    link_nodes(global_first_factor, base_of_power, exponent_of_power);

    tree_diff_node_t* first_addend = _MUL();
    tree_diff_node_t* second_addend = _MUL();
    link_nodes(global_second_factor, first_addend, second_addend);

    tree_diff_node_t* first_factor_in_first_addend = _DIFFR(node);
    tree_diff_node_t* second_factor_in_first_addend = _LOG();
    tree_diff_node_t* base_of_logarithm = _NUM(M_E);
    tree_diff_node_t* argument_of_logarithm = _COPYL(node);
    link_nodes(first_addend, first_factor_in_first_addend, second_factor_in_first_addend);
    link_nodes(second_factor_in_first_addend, base_of_logarithm, argument_of_logarithm);

    tree_diff_node_t* first_factor_in_second_addend = _COPYR(node);
    tree_diff_node_t* second_factor_in_second_addend = _DIV();
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
    assert((node->val).op_type == LOG);

    if((node->right)->type == NUM && (node->left)->type == NUM) return _NUM(0);
    if((node->left)->type == NUM) return deritative_log_with_const_base_function(node);  
    
    return deritative_general_log_function(node);
}
//----------------------------------------------------------------------------
tree_diff_node_t* deritative_log_with_const_base_function(tree_diff_node_t* node){
    assert(node);
    assert(node->type == OP);
    assert((node->val).op_type == LOG);
    assert((node->left)->type == NUM);

    if((node->right)->type == NUM) return _NUM(0);
    if((node->right)->type == VAR || (node->right)->type == OP){
        tree_diff_node_t* div_node = _DIV();
        tree_diff_node_t* numerator_node = _DIFFR(node);
        tree_diff_node_t* denumerator_node = _MUL();
        link_nodes(div_node, numerator_node, denumerator_node);

        tree_diff_node_t* first_factor_in_denumerator = _COPYR(node);
        tree_diff_node_t* second_factor_in_denumerator = _LOG();
        tree_diff_node_t* base_of_logarithm = _NUM(M_E);
        tree_diff_node_t* argument_of_logarithm = _NUM(((node->left)->val).num);
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
    assert((node->val).op_type == LOG);

    tree_diff_node_t* div_node = _DIV();
    tree_diff_node_t* numerator = _SUB();
    //------------
    tree_diff_node_t* denumerator = _POW();
    tree_diff_node_t* base_of_pow = _LOG();
    tree_diff_node_t* pow = _NUM(2);
    link_nodes(denumerator, base_of_pow, pow);
    tree_diff_node_t* base_log_denum = _NUM(M_E);
    tree_diff_node_t* arg_log_denum = _COPYL(node);
    link_nodes(base_of_pow, base_log_denum, arg_log_denum);
    //-------------
    link_nodes(div_node, numerator, denumerator);
    //-------------
    tree_diff_node_t* minuend = _MUL();
    tree_diff_node_t* first_factor_minuend = _DIV();
    tree_diff_node_t* second_factor_minuend = _LOG();
    link_nodes(minuend, first_factor_minuend, second_factor_minuend);

    tree_diff_node_t* numerator_first_fact_min = _DIFFR(node);
    tree_diff_node_t* denumerator_first_fact_min = _COPYR(node);
    link_nodes(first_factor_minuend, numerator_first_fact_min, denumerator_first_fact_min);

    tree_diff_node_t* base_log_minuend = _NUM(M_E); 
    tree_diff_node_t* arg_log_minuend = _COPYL(node);
    link_nodes(second_factor_minuend, base_log_minuend, arg_log_minuend);
    //-------------
    tree_diff_node_t* subtrahend = _MUL();
    tree_diff_node_t* first_factor_subtrahend = _DIV();
    tree_diff_node_t* second_factor_subtrahend = _LOG();
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
    assert((node->val).op_type == SIN);

    tree_diff_node_t* mul_node = _MUL();
    tree_diff_node_t* cos_node = _COS();
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
    assert((node->val).op_type == COS);

    tree_diff_node_t* mul_node = _MUL();
    tree_diff_node_t* negative_mul_node = _MUL();
    tree_diff_node_t* minus_one = _NUM(-1);
    tree_diff_node_t* sin_node = _SIN();
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
    assert((node->val).op_type == TG);

    tree_diff_node_t* mul_node = _MUL();
    tree_diff_node_t* first_factor = _DIV();
    tree_diff_node_t* second_factor = _DIFFL(node);
    link_nodes(mul_node, first_factor, second_factor);

    tree_diff_node_t* num_first_factor = _NUM(1);
    tree_diff_node_t* denum_first_factor = _POW();
    link_nodes(first_factor, num_first_factor, denum_first_factor);

    tree_diff_node_t* cos_node = _COS();
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
    assert((node->val).op_type == CTG);

    tree_diff_node_t* mul_node = _MUL();
    tree_diff_node_t* negative_first_factor = _MUL();
    tree_diff_node_t* second_factor = _DIFFL(node);
    link_nodes(mul_node, negative_first_factor, second_factor);

    tree_diff_node_t* minus_one = _NUM(-1);
    tree_diff_node_t* fraction = _DIV();
    link_nodes(negative_first_factor, minus_one, fraction);

    tree_diff_node_t* num_of_fraction = _NUM(1);
    tree_diff_node_t* denum_of_fraction = _POW();
    link_nodes(fraction, num_of_fraction, denum_of_fraction);

    tree_diff_node_t* sin_node = _SIN();
    tree_diff_node_t* sin_arg = _COPYL(node); 
    link_nodes(sin_node, sin_arg, NULL);

    tree_diff_node_t* exp_of_sin = _NUM(2);
    link_nodes(denum_of_fraction, sin_node, exp_of_sin);

    return mul_node;
}
//----------------------------------------------------------------------------
tree_diff_node_t* deritative_arcsin(tree_diff_node_t* node){
    assert(node);

    tree_diff_node_t* mul_node = _MUL();
    tree_diff_node_t* first_factor = _DIV();
    tree_diff_node_t* second_factor = _DIFFL(node);
    link_nodes(mul_node, first_factor, second_factor);

    tree_diff_node_t* numerator = _NUM(1);
    tree_diff_node_t* denumerator = _POW();
    link_nodes(first_factor, numerator, denumerator);

    tree_diff_node_t* base_of_pow = _SUB();
    tree_diff_node_t* exp_of_pow = _NUM(0.5);
    link_nodes(denumerator, base_of_pow, exp_of_pow);

    tree_diff_node_t* minuend = _NUM(1);
    tree_diff_node_t* subtrahend = _POW();
    link_nodes(base_of_pow, minuend, subtrahend);
    
    tree_diff_node_t* base_of_pow_subtrahend = _COPYL(node);
    tree_diff_node_t* exp_of_pow_subtrahend = _NUM(2);
    link_nodes(subtrahend, base_of_pow_subtrahend, exp_of_pow_subtrahend);

    return mul_node;
}
//----------------------------------------------------------------------------
tree_diff_node_t* deritative_arccos(tree_diff_node_t* node){
    assert(node);

    tree_diff_node_t* mul_node = _MUL();
    tree_diff_node_t* first_factor = _DIV();
    tree_diff_node_t* second_factor = _DIFFL(node);
    link_nodes(mul_node, first_factor, second_factor);

    tree_diff_node_t* numerator = _NUM(-1);
    tree_diff_node_t* denumerator = _POW();
    link_nodes(first_factor, numerator, denumerator);

    tree_diff_node_t* base_of_pow = _SUB();
    tree_diff_node_t* exp_of_pow = _NUM(0.5);
    link_nodes(denumerator, base_of_pow, exp_of_pow);

    tree_diff_node_t* minuend = _NUM(1);
    tree_diff_node_t* subtrahend = _POW();
    link_nodes(base_of_pow, minuend, subtrahend);
    
    tree_diff_node_t* base_of_pow_subtrahend = _COPYL(node);
    tree_diff_node_t* exp_of_pow_subtrahend = _NUM(2);
    link_nodes(subtrahend, base_of_pow_subtrahend, exp_of_pow_subtrahend);

    return mul_node;
}
//----------------------------------------------------------------------------
tree_diff_node_t* deritative_arctg(tree_diff_node_t* node){
    assert(node);

    tree_diff_node_t* mul_node = _MUL();
    tree_diff_node_t* first_factor = _DIV();
    tree_diff_node_t* second_factor = _DIFFL(node);
    link_nodes(mul_node, first_factor, second_factor);

    tree_diff_node_t* numerator = _NUM(1);
    tree_diff_node_t* denumerator = _ADD();
    link_nodes(first_factor, numerator, denumerator);

    tree_diff_node_t* first_addend = _NUM(1);
    tree_diff_node_t* second_addend = _POW();
    link_nodes(denumerator, first_addend, second_addend);

    tree_diff_node_t* base_of_pow = _COPYL(node);
    tree_diff_node_t* exp_of_pow = _NUM(2);
    link_nodes(second_addend, base_of_pow, exp_of_pow);

    return mul_node;
}
//----------------------------------------------------------------------------
tree_diff_node_t* deritative_arcctg(tree_diff_node_t* node){
    assert(node);

    tree_diff_node_t* mul_node = _MUL();
    tree_diff_node_t* first_factor = _DIV();
    tree_diff_node_t* second_factor = _DIFFL(node);
    link_nodes(mul_node, first_factor, second_factor);

    tree_diff_node_t* numerator = _NUM(-1);
    tree_diff_node_t* denumerator = _ADD();
    link_nodes(first_factor, numerator, denumerator);

    tree_diff_node_t* first_addend = _NUM(1);
    tree_diff_node_t* second_addend = _POW();
    link_nodes(denumerator, first_addend, second_addend);

    tree_diff_node_t* base_of_pow = _COPYL(node);
    tree_diff_node_t* exp_of_pow = _NUM(2);
    link_nodes(second_addend, base_of_pow, exp_of_pow);

    return mul_node;
}
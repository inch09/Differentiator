#include <stdio.h>
#include "defines.h"
#include "general_func_tree.h"
#include <assert.h>
#include <malloc.h>
#include <string.h>


tree_diff_node_t* create_node(type_of_node type, node_value val, tree_diff_node_t* left, tree_diff_node_t* right, tree_diff_node_t* parent){

    tree_diff_node_t* new_node = (tree_diff_node_t*) calloc(1, sizeof(tree_diff_node_t));
    assert(new_node);

    new_node->type = type;    
    switch(type){
        case OP:
            (new_node->val).op_type = val.op_type;
            break;
        case VAR:
            (new_node->val).var = val.var;
            break;
        case NUM:
            (new_node->val).num = val.num;
            break;
        default:
            break;
    }
    new_node->left = left;
    new_node->right = right;
    new_node->parent = parent;

    return new_node;
}
//-----------------------------------------------------------------
tree_diff_node_t* create_num_node(type_of_node type, double num, tree_diff_node_t* left, tree_diff_node_t* right, tree_diff_node_t* parent){
    assert(type == NUM);

    node_value union_num = {.num = num};
    tree_diff_node_t* new_node = create_node(NUM, union_num, left, right, parent);
    return new_node;
}
//-----------------------------------------------------------------
tree_diff_node_t* create_var_node(type_of_node type, type_of_variable var, tree_diff_node_t* left, tree_diff_node_t* right, tree_diff_node_t* parent){
    assert(type == VAR);

    node_value union_var = {.var = var};
    tree_diff_node_t* new_node = create_node(VAR, union_var, left, right, parent);
    return new_node;
}
//-----------------------------------------------------------------
tree_diff_node_t* create_op_node(type_of_node type, type_of_operation oper, tree_diff_node_t* left, tree_diff_node_t* right, tree_diff_node_t* parent){
    assert(type == OP);

    node_value union_oper = {.op_type = oper};
    tree_diff_node_t* new_node = create_node(OP, union_oper, left, right, parent);
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
        printf("%lg\n", (node->val).num);
        fprintf(tex_file, "{%lg}", (node->val).num);
        return;
    }
    if(node->type == VAR){
        switch((node->val).var){
            case X:
                fprintf(tex_file, "{x}");
                return;
            case Y:
                fprintf(tex_file, "{y}");
                return;
            default:
                fprintf(tex_file, "Invalid variable\n");
                return;
        }
    }
    if(node->type == OP){
        switch ((node->val).op_type){
        case ADD:
            fprintf(tex_file, "(");
            tex_viz_of_nodes(node->left, tex_file);
            fprintf(tex_file, "+");
            tex_viz_of_nodes(node->right, tex_file);
            fprintf(tex_file, ")");
            return;
        case SUB:
            fprintf(tex_file, "(");
            tex_viz_of_nodes(node->left, tex_file);
            fprintf(tex_file, "-");
            tex_viz_of_nodes(node->right, tex_file);
            fprintf(tex_file, ")");
            return;
        case MUL:
            tex_viz_of_nodes(node->left, tex_file);
            fprintf(tex_file, "\\cdot");
            tex_viz_of_nodes(node->right, tex_file);
            return;
        case DIV:
            fprintf(tex_file, "\\frac{");
            tex_viz_of_nodes(node->left, tex_file);
            fprintf(tex_file, "}");
            fprintf(tex_file, "{");
            tex_viz_of_nodes(node->right, tex_file);
            fprintf(tex_file, "}");
            return;
        case POW:
            fprintf(tex_file, "({");
            tex_viz_of_nodes(node->left, tex_file);
            fprintf(tex_file, "})");
            fprintf(tex_file, "^");
            fprintf(tex_file, "{");
            tex_viz_of_nodes(node->right, tex_file);
            fprintf(tex_file, "}");
            return;
        case LOG:
            fprintf(tex_file, "{log_{");
            tex_viz_of_nodes(node->left, tex_file);
            fprintf(tex_file, "}");
            fprintf(tex_file, " ");
            fprintf(tex_file, "{");
            tex_viz_of_nodes(node->right, tex_file);
            fprintf(tex_file, "}}");
            return;
        case SIN:
            fprintf(tex_file, "\\sin({");
            tex_viz_of_nodes(node->left, tex_file);
            fprintf(tex_file, "})");
            return;
        case COS:
            fprintf(tex_file, "\\cos({");
            tex_viz_of_nodes(node->left, tex_file);
            fprintf(tex_file, "})");
            return;
        case TG:
            fprintf(tex_file, "\\tan({");
            tex_viz_of_nodes(node->left, tex_file);
            fprintf(tex_file, "})");
            return;
        case CTG:
            fprintf(tex_file, "\\cot({");
            tex_viz_of_nodes(node->left, tex_file);
            fprintf(tex_file, "})");
            return;
        case ARCSIN:
            fprintf(tex_file, "\\arcsin({");
            tex_viz_of_nodes(node->left, tex_file);
            fprintf(tex_file, "})");
            return;
        case ARCCOS:
            fprintf(tex_file, "\\arccos({");
            tex_viz_of_nodes(node->left, tex_file);
            fprintf(tex_file, "})");
            return;
        case ARCTG:
            fprintf(tex_file, "\\arctan({");
            tex_viz_of_nodes(node->left, tex_file);
            fprintf(tex_file, "})");
            return;
        case ARCCTG:
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

    switch ((node->val).op_type)
    {
    case ADD:
        strcpy(oper_name, "+");
        break;  
    case SUB:
        strcpy(oper_name, "-");
        break;
    case MUL:
        strcpy(oper_name, "*");
        break;
    case DIV:
        strcpy(oper_name, "/");
        break;
    case POW:   
        strcpy(oper_name, "^");
        break;
    case LOG:
        strcpy(oper_name, "log");
        break;
    case SIN:
        strcpy(oper_name, "sin");
        break;
    case COS:
        strcpy(oper_name, "cos");
        break;
    case TG:
        strcpy(oper_name, "tg");
        break;  
    case CTG:
        strcpy(oper_name, "ctg");
        break;        
    case ARCSIN:
        strcpy(oper_name, "arcsin");
        break;
    case ARCCOS:
        strcpy(oper_name, "arccos");
        break;
    case ARCTG:
        strcpy(oper_name, "arctg");
        break;  
    case ARCCTG:
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

    switch((node->val).var){
        case X:
            strcpy(var_name, "x");
            break;
        case Y:
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

    fprintf(viz_file, "node%p[shape = Mrecord, label = \"%lg\", style = \"filled\", fillcolor = \"#f79eef\"];\n", (void*) node, (node->val).num);
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
    switch(node->type){
        case OP:
            (copy_node->val).op_type = (node->val).op_type;
            break;
        case VAR:
            (copy_node->val).var = (node->val).var;
            break;
        case NUM:
            (copy_node->val).num = (node->val).num;
            break;
        default:
            break;
    }
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
    switch(node_copy_from->type){
        case OP:
            (node_copy_to->val).op_type = (node_copy_from->val).op_type;
            break;
        case VAR:
            (node_copy_to->val).var = (node_copy_from->val).var;
            break;
        case NUM:
            (node_copy_to->val).num = (node_copy_from->val).num;
            break;
        default:
            break;
    }
    node_copy_to->left   = node_copy_from->left;
    node_copy_to->right  = node_copy_from->right;
    node_copy_to->parent = node_copy_from->parent;

    return node_copy_to;
}
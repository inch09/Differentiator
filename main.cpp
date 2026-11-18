#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
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
    DIV = 3
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
//-----------------------------------------------------------------
void tree_viz(tree_diff_node_t* root, FILE* viz_file);
void create_node_viz(tree_diff_node_t* node, FILE* viz_file);
void create_edge_viz(tree_diff_node_t* node, FILE* viz_file);
void create_op_node_viz(tree_diff_node_t* node, FILE* viz_file);
void create_var_node_viz(tree_diff_node_t* node, FILE* viz_file);
void create_num_node_viz(tree_diff_node_t* node, FILE* viz_file);
//-----------------------------------------------------------------
double calculate_subtree(tree_diff_node_t* node);
double calculate_operation(tree_diff_node_t* node, double operand1, double operand2);
//-----------------------------------------------------------------
int main(){
    tree_diff_node_t* node1 = create_node(OP, 2, NULL, NULL, NULL);
    tree_diff_node_t* node2 = create_node(OP, 0, NULL, NULL, NULL);
    tree_diff_node_t* node3 = create_node(NUM, 3, NULL, NULL, NULL);
    tree_diff_node_t* node4 = create_node(NUM, 4, NULL, NULL, NULL);
    tree_diff_node_t* node5 = create_node(OP, 2, NULL, NULL, NULL);
    tree_diff_node_t* node6 = create_node(NUM, 7, NULL, NULL, NULL);
    tree_diff_node_t* node7 = create_node(NUM, 8, NULL, NULL, NULL);

    link_nodes(node1, node2, node5);
    link_nodes(node2, node3, node4);
    link_nodes(node5, node6, node7);

    FILE* viz_file = fopen("viz_file.txt", "w");
    assert(viz_file);

    printf("%lf\n", calculate_subtree(node1));
    printf("%lf\n", calculate_subtree(node2));


    tree_viz(node1, viz_file);
    delete_tree(node1);

    fclose(viz_file);
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
    assert(left || right);
    
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
        strcpy(oper_name, "ADD");
        break;  
    case 1:
        strcpy(oper_name, "SUB");
        break;
    case 2:
        strcpy(oper_name, "MUL");
        break;
    case 3:
        strcpy(oper_name, "DIV");
        break;
    default:
        printf("Invalid type of operatiom\n");
        break;
    }
    fprintf(viz_file, "node%p[shape = Mrecord, label = \"{OP | %s}\"];\n", (void*) node, oper_name);

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
    fprintf(viz_file, "node%p[shape = Mrecord, label = \"{VAR | %s}\"];\n", (void*) node, var_name);

}
//----------------------------------------------------------------------------
void create_num_node_viz(tree_diff_node_t* node, FILE* viz_file){
    assert(node);
    assert(viz_file);
    assert(node->type == NUM);

    fprintf(viz_file, "node%p[shape = Mrecord, label = \"{NUM | %lf}\"];\n", (void*) node, node->val);
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
double calculate_subtree(tree_diff_node_t* node){
    assert(node);

    if(node->type == NUM) return node->val;
    if(node->type == VAR) return 0;//////fix val of var
    if(node->type == OP){
        double operand1 = NAN;
        double operand2 = NAN;
        if(is_node_have_left(node))  operand1 = calculate_subtree(node->left);
        if(is_node_have_right(node)) operand2 = calculate_subtree(node->right);
        return calculate_operation(node, operand1, operand2);
    }

    return NAN;
}
//----------------------------------------------------------------------------
double calculate_operation(tree_diff_node_t* node, double operand1, double operand2){
    assert(node);
    assert(node->type == OP);

    switch ((int) node->val/*fix enum*/)
    {
    case 0:
        if(isnan(operand1) || isnan(operand2)){
            printf("Operands error\n");
            assert(0);
        }    
        return operand1 + operand2;
    case 1:
        if(isnan(operand1) || isnan(operand2)){
            printf("Operands error\n");
            assert(0);
        }    
        return operand1 - operand2;
    case 2:
        if(isnan(operand1) || isnan(operand2)){
            printf("Operands error\n");
            assert(0);
        }    
        return operand1 * operand2;
    case 3:
        if(isnan(operand1) || isnan(operand2)){
            printf("Operands error\n");
            assert(0);
        }
        if(operand2 == 0){
            printf("Division by zero\n");
            assert(0);
        }     
        return operand1 / operand2;
    default:
        printf("Invalid type of operatiom\n");
        return NAN;
    }
}
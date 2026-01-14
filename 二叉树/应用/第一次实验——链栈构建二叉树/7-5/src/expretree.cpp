#include <stdio.h>
#include "../include/expretree.h"
#include <cctype>
#include <cstring>

// 判断字符是否为运算符
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// 获取运算符优先级
int getPriority(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

// 递归构建表达式二叉树（合并所有解析函数）
BTNode* CreateExprTree(const char* expr, int& index, int minPriority = 0) {
    if (expr[index] == '\0') return nullptr;
    
    BTNode* left = nullptr;
    
    // 处理操作数或括号表达式
    if (expr[index] == '(') {
        index++; // 跳过 '('
        left = CreateExprTree(expr, index, 0); // 括号内重新开始
        index++; // 跳过 ')'
    } else {
        // 单个操作数
        left = new BTNode;
        left->data = expr[index];
        left->lchild = left->rchild = nullptr;
        index++;
    }
    
    // 处理后续的运算符
    while (expr[index] != '\0' && expr[index] != ')' && 
           isOperator(expr[index]) && getPriority(expr[index]) >= minPriority) {
        
        char op = expr[index];
        int currentPriority = getPriority(op);
        index++;
        
        // 递归构建右子树，处理更高优先级的运算符
        BTNode* right = CreateExprTree(expr, index, currentPriority + 1);
        
        BTNode* node = new BTNode;
        node->data = op;
        node->lchild = left;
        node->rchild = right;
        left = node;
    }
    
    return left;
}

// 包装函数
BTNode* CreateExprTree(const char* expr) {
    int index = 0;
    return CreateExprTree(expr, index, 0);
}

// 获取操作数的值
double getValue(char var) {
    return var - '0';
}

// 递归求值
double EvaluateExprTree(BTNode* root) {
    if (root == nullptr) return 0;
    
    if (!isOperator(root->data)) {
        return getValue(root->data);
    }
    
    double leftVal = EvaluateExprTree(root->lchild);
    double rightVal = EvaluateExprTree(root->rchild);
    
    switch (root->data) {
        case '+': return leftVal + rightVal;
        case '-': return leftVal - rightVal;
        case '*': return leftVal * rightVal;
        case '/': 
            if (rightVal != 0) return leftVal / rightVal;
            else {
                printf("Error: Division by zero\n");
                return 0;
            }
        default: return 0;
    }
}
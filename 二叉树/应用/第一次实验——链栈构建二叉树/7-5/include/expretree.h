#ifndef EXPRTREE_H
#define EXPRTREE_H

#include "btree.h"

bool isOperator(char c);
int getPriority(char op);
BTNode* CreateExprTree(const char* expr, int& index);
BTNode* CreateExprTree(const char* expr);
double getValue(char var);
double EvaluateExprTree(BTNode *root);

#endif
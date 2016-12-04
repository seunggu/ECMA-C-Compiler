#include "exp.h"
#include <cstdio>
#include <malloc.h>
#include <string.h>

const int INDENT_LEVEL = 4;

void indent(int n){
    if (n > 0) {
        printf(" ");
        indent(--n);
    }
};

Exp::Exp(Exp* left, Exp* right){
	this->left = left;
	this->right = right;
};

Exp::Exp(Exp* left){
	this->left = left;
	this->right = NULL;
};

Exp::Exp(){
};

BExp::BExp(char op, Exp *l, Exp *r) : op(op), Exp(l,r){
};

void BExp::printTree(int lmargin){
	indent(lmargin);
	printf("Op(%c)\n", this->op);
	this->left->printTree(lmargin+INDENT_LEVEL);
    this->right->printTree(lmargin+INDENT_LEVEL);
};

UNExp::UNExp(char op, Exp* l) : op(op), Exp(l){
};

void UNExp::printTree(int lmargin){
	indent(lmargin);
	printf("Uop(%c)\n", this->op);
	this->left->printTree(lmargin+INDENT_LEVEL);
};

Num::Num(int num) : num(num), Exp(NULL,NULL){
};

void Num::printTree(int lmargin){
	indent(lmargin);
	printf("Int(%d)\n", this->num);
};

IDExp::IDExp(char* name){
	this->name = (char *)malloc(strlen(name) + 1);
    strcpy(this->name, name);
};

void IDExp::printTree(int lmargin){
	indent(lmargin);
	printf("Id(%s)\n", this->name);
};

//void printTreeIndent(Exp *root, int lmargin);
//
//void printTree(Exp *root)
//{
//    if (root == NULL) return;
//    printTreeIndent(root, 0);
//}



//void printTreeIndent(Exp *root, int lmargin)
//{
//    indent(lmargin);
//    switch (root->tag) {
//        case Exp::INTNODE: printf("Int(%d)\n", root->num);
//                      break;
//        case Exp::IDNODE:  printf("Id(%s)\n", root->name);
//                      break;
//        case Exp::BOPNODE: printf("Op(%c)\n", root->op);
//                      printTreeIndent(root->left,  lmargin+INDENT_LEVEL);
//                      printTreeIndent(root->right, lmargin+INDENT_LEVEL);
//                      break;
//        case Exp::UOPNODE: printf("Uop(%c)\n", root->op);
//                      printTreeIndent(root->left,  lmargin+INDENT_LEVEL);
//                      break;
//        default:      ; // should be an error
//    }
//}

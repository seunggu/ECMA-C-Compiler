#ifndef __AST_H__
#define __AST_H__

#include <cstdio>

class Exp {
	public:
    class Exp *left, *right;
    virtual void printTree(int lmargin) = 0;
    Exp(Exp* left, Exp* right);
    Exp(Exp* left);
    Exp();
};

class BExp : public Exp {
	public:
    char   op;
    virtual void printTree(int lmargin);
	BExp(char op, Exp *l, Exp *r);
};

class Num : public Exp {
	public:
	int num;
	virtual void printTree(int lmargin);
	Num(int num);
};

class UNExp : public Exp {
	public:
    char   op;
    virtual void printTree(int lmargin);
	UNExp(char op, Exp *l);
};

class IDExp : public Exp {
	public:
    char* name;
    virtual void printTree(int lmargin);
	IDExp(char* name);
};

/*
Node *mkBopNode(char op, Node *l, Node *r);
Node *mkUopNode(char op, Node *l);
Node *mkIntNode(int num);
Node *mkIdNode(char *name);
void printTree(Node *root);
*/

#endif

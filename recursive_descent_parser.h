/*
* File: recursive_descent_parser.h
* Creator: Jimmy Li
* Created: Tue Oct 17 19:11:24 2017
* Time-stamp: <Tue Oct 17 23:15:42 EDT 2017 li>
*
* Project 2:
* Grammars and Parsing
*/

#ifndef _recursive_descent_parser_h
#define _recursive_descent_parser_h

typedef struct NODE *TREE;

extern int matchTerminal(char c);
extern char getTerminal();
extern int lookahead(char c);
extern int checkInputLeft();
extern void printErrorMessage();
extern TREE makeNode0(char x);
extern TREE makeNode1(char x, TREE t);
extern TREE makeNode2(char x, TREE t1, TREE t2);
extern TREE makeNode3(char x, TREE t1, TREE t2, TREE t3);
extern TREE makeNode4(char x, TREE t1, TREE t2, TREE t3, TREE t4);
extern TREE Dtree();
extern TREE NTtree();
extern TREE Ntree();
extern TREE Ftree();
extern TREE FTtree();
extern TREE Ttree();
extern TREE TTtree();
extern TREE Etree();
extern void printSuccessMessage();
extern void printTree(TREE root, int i);
extern void runPart1();

#endif

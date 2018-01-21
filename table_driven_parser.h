/*
* File: table_driven_parser.h
* Creator: Jimmy Li
* Created: Tue Oct 17 19:11:24 2017
* Time-stamp: <Tue Oct 17 23:15:42 EDT 2017 li>
*
* Project 2:
* Grammars and Parsing
*/

#ifndef _table_driven_parser_h
#define _table_driven_parser_h

typedef struct NODE *TREE;

extern int checkInputLeft();
extern void setUpTable();
extern void push(char c);
extern char pop();
extern void pushTree(TREE t);
extern TREE popTree();
extern void printStack();
extern void tableLookup(char popped);
extern void printErrorMessage();
extern void printSuccessMessage();
extern int charToIntConversion(char c);
extern void productionLookup(int p);
extern void printTree(TREE root, int i);
extern void E();
extern void TT1();
extern void TT2();
extern void TT3();
extern void T();
extern void FT1();
extern void FT2();
extern void FT3();
extern void F1();
extern void F2();
extern void N();
extern void NT1();
extern void NT2();
extern void D();
extern void Etree2();
extern void TT1tree();
extern void TT2tree();
extern void TT3tree();
extern void Ttree2();
extern void FT1tree();
extern void FT2tree();
extern void FT3tree();
extern void F1tree();
extern void F2tree();
extern void Ntree2();
extern void NT1tree();
extern void NT2tree();
extern void Dtree2();
extern TREE makeNode0(char x);
extern TREE makeNode1(char x, TREE t);
extern TREE makeNode2(char x, TREE t1, TREE t2);
extern TREE makeNode3(char x, TREE t1, TREE t2, TREE t3);
extern TREE makeNode4(char x, TREE t1, TREE t2, TREE t3, TREE t4);
extern void productionTreeLookup(int i);
extern void runPart2();

#endif

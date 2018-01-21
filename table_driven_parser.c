/*
 * File: table_driven_parser.c
 * Creator: Jimmy Li
 * Created: Tue Oct 10 19:11:24 2017
 * Time-stamp: <Tue Oct 17 23:15:42 EDT 2017>
 *
 * Project 2:
 * Grammars and Parsing
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FAILED NULL
typedef struct NODE *TREE;
struct NODE {
  char label;
  TREE leftmostChild, rightSibling;
};
TREE parseTree; /* holds the result of the parse */
char* input;
int inputCharLeft;
/* 8x8 Table Declaration*/
int table[8][8];
char stack[50];
int stack_index;
TREE stack_of_trees[50];
int sot_index;
int checkInputLeft();
void setUpTable();
void push(char c);
char pop();
void pushTree(TREE t);
TREE popTree();
void printStack();
void tableLookup(char popped);
void printErrorMessage();
void printSuccessMessage();
int charToIntConversion(char c);
void productionLookup(int p);
void printTree(TREE root, int i);
void E();
void TT1();
void TT2();
void TT3();
void T();
void FT1();
void FT2();
void FT3();
void F1();
void F2();
void N();
void NT1();
void NT2();
void D();
void Etree2();
void TT1tree();
void TT2tree();
void TT3tree();
void Ttree2();
void FT1tree();
void FT2tree();
void FT3tree();
void F1tree();
void F2tree();
void Ntree2();
void NT1tree();
void NT2tree();
void Dtree2();
TREE makeNode0(char x);
TREE makeNode1(char x, TREE t);
TREE makeNode2(char x, TREE t1, TREE t2);
TREE makeNode3(char x, TREE t1, TREE t2, TREE t3);
TREE makeNode4(char x, TREE t1, TREE t2, TREE t3, TREE t4);
void productionTreeLookup(int i);
void runPart2();

void runPart2(){
  setUpTable();
  stack_index = 0;
  sot_index = 0;
  push('$');
  push('E');
  parseTree = makeNode0('E');
  pushTree(parseTree);
  input = (char*)malloc(100*sizeof(char));
  FILE *fp;
  fp = fopen("input.txt","r");
  if (fp!=NULL)
  {
    fscanf(fp,"%s\n", input);
    inputCharLeft = strlen(input);
    while (*input != '\0'){
      printf("Creating Parse Tree For: %s\n", input);
      tableLookup(pop());
      if (checkInputLeft()){
        input = (char*)malloc(100*sizeof(char));
      }
      else{
        printTree(parseTree, 0);
      }
      stack_index = 0;
      sot_index = 0;
      push('$');
      push('E');
      parseTree = makeNode0('E');
      pushTree(parseTree);
      fscanf(fp,"%s\n", input);
      inputCharLeft = strlen(input);
      printf("\n");
      //printf("%c\n", *input);
    }
    fclose (fp);
}

}

void setUpTable(){
  int i, j;
  for(i=0; i<8; i++) {
    for(j=0;j<8;j++) {
       table[i][j] = 0;
    }
  }
  //Row 0: Expression
  table[0][4] = 1;
  table[0][6] = 1;
  //Row 1: Term
  table[1][4] = 5;
  table[1][6] = 5;
  //Row 2: Term tail
  table[2][0] = 4;
  table[2][1] = 4;
  table[2][4] = 4;
  table[2][5] = 4;
  table[2][6] = 4;
  table[2][7] = 4;
  table[2][2] = 3;
  table[2][3] = 2;
  //Row 3: Factor
  table[3][4] = 10;
  table[3][6] = 9;
  //Row 4: Factor Tail
  table[4][2] = 8;
  table[4][3] = 8;
  table[4][4] = 8;
  table[4][5] = 8;
  table[4][6] = 8;
  table[4][7] = 8;
  table[4][1] = 7;
  table[4][0] = 6;
  //Row 5: Number
  table[5][6] = 11;
  //Row 6: Number Tail
  table[6][0] = 13;
  table[6][1] = 13;
  table[6][2] = 13;
  table[6][3] = 13;
  table[6][4] = 13;
  table[6][5] = 13;
  table[6][7] = 13;
  table[6][6] = 12;
  //Row 7: Digit
  table[7][6] = 14;
}

void push(char c){
  stack[stack_index] = c;
  stack_index++;
}

char pop(){
  stack_index--;
  char c = stack[stack_index];
  return c;
}

void pushTree(TREE t){
  stack_of_trees[sot_index] = t;
  sot_index++;
}

TREE popTree(){
  sot_index--;
  TREE t = stack_of_trees[sot_index];
  return t;
}

void printStack(){
  int i = 0;
  while ((int)stack[i]!= 0){
    printf("%c, ", stack[i]);
    i++;
  }
}

void tableLookup(char popped){
  //Convert char to int
  //pInt = poppedInt, iInt = inputInt
  int pInt, iInt;
  pInt = charToIntConversion(popped);
  iInt = charToIntConversion(*input);

  if (popped == *input){
    input++;
    inputCharLeft = inputCharLeft - 1;
    tableLookup(pop());
  }
  else if (table[pInt][iInt] == 0 && popped != '$'){
    //FAILED
    printErrorMessage();
  }
  else if (popped != '$'){
    if (table[pInt][iInt] == 0){
      //FAILED
      printErrorMessage();
    }
    else {
      productionTreeLookup(table[pInt][iInt]);
    }
  }
  else if (popped == '$' && *input != '\0'){
    //FAILED
    printErrorMessage();
  }
  else{
    //SUCCESS
    printSuccessMessage();
  }
}

int charToIntConversion(char c){
  switch (c) {
    case 'E': return 0; break;
    case 'T': return 1; break;
    case 't': return 2; break;
    case 'F': return 3; break;
    case 'f': return 4; break;
    case 'N': return 5; break;
    case 'n': return 6; break;
    case 'D': return 7; break;
    case '*': return 0; break;
    case '/': return 1; break;
    case '+': return 2; break;
    case '-': return 3; break;
    case '(': return 4; break;
    case ')': return 5; break;
    case '0': return 6; break;
    case '1': return 6; break;
    case '2': return 6; break;
    case '3': return 6; break;
    case '4': return 6; break;
    case '5': return 6; break;
    case '6': return 6; break;
    case '7': return 6; break;
    case '8': return 6; break;
    case '9': return 6; break;
    case '\0': return 7; break;
    default: return -1; break;
  }
}

void productionLookup(int p){
  switch (p) {
    case 1: E(); break;
    case 2: TT1(); break;
    case 3: TT2(); break;
    case 4: TT3(); break;
    case 5: T(); break;
    case 6: FT1(); break;
    case 7: FT2(); break;
    case 8: FT3(); break;
    case 9: F1(); break;
    case 10: F2(); break;
    case 11: N(); break;
    case 12: NT1(); break;
    case 13: NT2(); break;
    case 14: D(); break;
  }
}

void E(){
  push('t');
  push('T');
  tableLookup(pop());
}

void TT1(){
  push('t');
  push('T');
  push('-');
  tableLookup(pop());
}

void TT2(){
  push('t');
  push('T');
  push('+');
  tableLookup(pop());
}

void TT3(){
  tableLookup(pop());
}

void T(){
  push('f');
  push('F');
  tableLookup(pop());
}

void FT1(){
  push('f');
  push('F');
  push('*');
  tableLookup(pop());
}

void FT2(){
  push('f');
  push('F');
  push('/');
  tableLookup(pop());
}

void FT3(){
  tableLookup(pop());
}

void F1(){
  push('N');
  tableLookup(pop());
}

void F2(){
  push(')');
  push('E');
  push('(');
  tableLookup(pop());
}

void N(){
  push('n');
  push('D');
  tableLookup(pop());
}

void NT1(){
  push('N');
  tableLookup(pop());
}

void NT2(){
  tableLookup(pop());
}

void D(){
  push(*input);
  tableLookup(pop());
}

void productionTreeLookup(int p){
  switch (p) {
    case 1: Etree2(); break;
    case 2: TT1tree(); break;
    case 3: TT2tree(); break;
    case 4: TT3tree(); break;
    case 5: Ttree2(); break;
    case 6: FT1tree(); break;
    case 7: FT2tree(); break;
    case 8: FT3tree(); break;
    case 9: F1tree(); break;
    case 10: F2tree(); break;
    case 11: Ntree2(); break;
    case 12: NT1tree(); break;
    case 13: NT2tree(); break;
    case 14: Dtree2(); break;
  }
}

void Etree2(){
  push('t');
  push('T');
  TREE current = popTree();
  TREE newT = makeNode0('T');
  TREE newTT = makeNode0('t');
  newT -> rightSibling = newTT;
  current -> leftmostChild = newT;
  pushTree(newTT);
  pushTree(newT);
  tableLookup(pop());
}

void TT1tree(){
  push('t');
  push('T');
  push('-');
  TREE current = popTree();
  TREE minus = makeNode0('-');
  TREE newT = makeNode0('T');
  TREE newTT = makeNode0('t');
  minus -> rightSibling = newT;
  newT -> rightSibling = newTT;
  current -> leftmostChild = minus;
  pushTree(newTT);
  pushTree(newT);
  tableLookup(pop());
}

void TT2tree(){
  push('t');
  push('T');
  push('+');
  TREE current = popTree();
  TREE plus = makeNode0('+');
  TREE newT = makeNode0('T');
  TREE newTT = makeNode0('t');
  plus -> rightSibling = newT;
  newT -> rightSibling = newTT;
  current -> leftmostChild = plus;
  pushTree(newTT);
  pushTree(newT);
  tableLookup(pop());
}

void TT3tree(){
  TREE current = popTree();
  TREE epsilon = makeNode0('e');
  current -> leftmostChild = epsilon;
  tableLookup(pop());
}

void Ttree2(){
  push('f');
  push('F');
  TREE current = popTree();
  TREE newF = makeNode0('F');
  TREE newFT = makeNode0('f');
  newF -> rightSibling = newFT;
  current -> leftmostChild = newF;
  pushTree(newFT);
  pushTree(newF);
  tableLookup(pop());
}

void FT1tree(){
  push('f');
  push('F');
  push('*');
  TREE current = popTree();
  TREE multiply = makeNode0('*');
  TREE newF = makeNode0('F');
  TREE newFT = makeNode0('f');
  multiply -> rightSibling = newF;
  newF -> rightSibling = newFT;
  current -> leftmostChild = newF;
  pushTree(newFT);
  pushTree(newF);
  tableLookup(pop());
}

void FT2tree(){
  push('f');
  push('F');
  push('/');
  TREE current = popTree();
  TREE division = makeNode0('/');
  TREE newF = makeNode0('F');
  TREE newFT = makeNode0('f');
  division -> rightSibling = newF;
  newF -> rightSibling = newFT;
  current -> leftmostChild = newF;
  pushTree(newFT);
  pushTree(newF);
  tableLookup(pop());
}

void FT3tree(){
  TREE current = popTree();
  TREE epsilon = makeNode0('e');
  current -> leftmostChild = epsilon;
  tableLookup(pop());
}

void F1tree(){
  push('N');
  TREE current = popTree();
  TREE newN = makeNode0('N');
  current -> leftmostChild = newN;
  pushTree(newN);
  tableLookup(pop());
}

void F2tree(){
  push(')');
  push('E');
  push('(');
  TREE current = popTree();
  TREE open_paren = makeNode0('(');
  TREE newE = makeNode0('E');
  TREE closed_paren = makeNode0(')');
  open_paren -> rightSibling = newE;
  newE -> rightSibling = closed_paren;
  current -> leftmostChild = open_paren;
  pushTree(newE);
  tableLookup(pop());
}

void Ntree2(){
  push('n');
  push('D');
  TREE current = popTree();
  TREE newD = makeNode0('D');
  TREE newNT = makeNode0('n');
  newD -> rightSibling = newNT;
  current -> leftmostChild = newD;
  pushTree(newNT);
  pushTree(newD);
  tableLookup(pop());
}

void NT1tree(){
  push('N');
  TREE current = popTree();
  TREE newN = makeNode0('N');
  current -> leftmostChild = newN;
  pushTree(newN);
  tableLookup(pop());
}

void NT2tree(){
  TREE current = popTree();
  TREE epsilon = makeNode0('e');
  current -> leftmostChild = epsilon;
  tableLookup(pop());
}

void Dtree2(){
  push(*input);
  TREE current = popTree();
  TREE digit = makeNode0(*input);
  current -> leftmostChild = digit;
  tableLookup(pop());
}

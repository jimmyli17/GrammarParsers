/*
 * File: recursive_descent_parser.c
 * Creator: Jimmy Li
 * Created: Tue Oct 10 19:11:24 2017
 * Time-stamp: <Tue Oct 17 23:15:42 EDT 2017 li>
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
char* nextInputChar;
int inputCharLeft;
int matchTerminal(char c);
char getTerminal();
int lookahead(char c);
int checkInputLeft();
void printErrorMessage();
TREE makeNode0(char x);
TREE makeNode1(char x, TREE t);
TREE makeNode2(char x, TREE t1, TREE t2);
TREE makeNode3(char x, TREE t1, TREE t2, TREE t3);
TREE makeNode4(char x, TREE t1, TREE t2, TREE t3, TREE t4);
TREE Dtree();
TREE NTtree();
TREE Ntree();
TREE Ftree();
TREE FTtree();
TREE Ttree();
TREE TTtree();
TREE Etree();
void printSuccessMessage();
void printTree(TREE root, int i);
void runPart1();

void runPart1(){
  nextInputChar = (char*)malloc(100*sizeof(char));
  FILE *fp;
  fp = fopen("input.txt","r");
  if (fp!=NULL)
  {
    fscanf(fp,"%s\n", nextInputChar);
    while (*nextInputChar != '\0'){
      printf("Creating Parse Tree For: %s\n", nextInputChar);
      inputCharLeft = strlen(nextInputChar);
      parseTree = Etree();
      if (checkInputLeft()){
        printErrorMessage();
        nextInputChar = (char*)malloc(100*sizeof(char));
      }
      else{
        printSuccessMessage();
        printTree(parseTree, 0);
      }
      printf("\n");
      fscanf(fp,"%s\n", nextInputChar);
    }
    fclose (fp);
  }
}

/** Attempts to match the given character against
  * the current input symbol (character).
  * If so, consumes the symbol and returns true,
  * otherwise returns false.
  */
int matchTerminal(char c) {
  if (*nextInputChar == c) {
    nextInputChar++;
    inputCharLeft = inputCharLeft - 1;
    return 1;
  }
  else {
    return 0;
  }
}

/** Consumes next symbol from the input
  * and returns it.
  */
char getTerminal() {
  char terminal = *nextInputChar;
  nextInputChar++;
  inputCharLeft = inputCharLeft - 1;
  return terminal;
}

/** Returns true if the next input character
  * matches the given character, else false.
  * Does not consume any input.
  */
int lookahead(char c) {
  return *nextInputChar == c;
}

/** Returns true if all the input characters
  * have been consumed, else false.
  */
int checkInputLeft(){
  if (inputCharLeft > 0){
    return 1;
  }
  return 0;
}

void printErrorMessage(){
  printf("ERROR: Input is not well-formed.\n");
}

void printSuccessMessage(){
  printf("SUCCESS: Input is well-formed.\n");
}

TREE makeNode0(char x) {
  TREE root; root = (TREE) malloc(sizeof(struct NODE));
  root->label = x;
  root->leftmostChild = NULL;
  root->rightSibling = NULL;
  return root;
}

TREE makeNode1(char x, TREE t) {
  TREE root; root = makeNode0(x);
  root->leftmostChild = t;
  return root;
}

TREE makeNode2(char x, TREE t1, TREE t2) {
  TREE root; root = makeNode1(x, t1);
  t1->rightSibling = t2;
  return root;
}

TREE makeNode3(char x, TREE t1, TREE t2, TREE t3) {
  TREE root; root = makeNode1(x, t1);
  t1->rightSibling = t2;
  t2->rightSibling = t3;
  return root;
}

TREE makeNode4(char x, TREE t1, TREE t2, TREE t3, TREE t4) {
  TREE root; root = makeNode1(x, t1);
  t1->rightSibling = t2;
  t2->rightSibling = t3;
  t3->rightSibling = t4;
  return root;
}

/* Parses a digit from the input.
 * Returns constructed tree if successful and
 * returns FAILED if unsuccessful.
 *
 * Character Symbol: 'D'
 */
TREE Dtree() {
  if (!lookahead('0') && !lookahead('1') && !lookahead('2') && !lookahead('3') && !lookahead('4') && !lookahead('5') && !lookahead('6') && !lookahead('7') && !lookahead('8') && !lookahead('9')){
    return FAILED;
  }
  char digit = getTerminal();
  return makeNode1('D', makeNode0(digit));
}

/* Parses a number "tail" from the input.
 * Returns constructed tree if successful and
 * returns FAILED if unsuccessful.
 *
 * Character Symbol : 'n'
 */
TREE NTtree() {
  if (!lookahead('0') && !lookahead('1') && !lookahead('2') && !lookahead('3') && !lookahead('4') && !lookahead('5') && !lookahead('6') && !lookahead('7') && !lookahead('8') && !lookahead('9')) {
    return makeNode1('n', makeNode0('e'));
  }
  else {
    TREE number = Ntree();
    if (number == FAILED){
      return FAILED;
    }
    return makeNode1('n', number);
  }
}

/* Parses a number from the input.
 * Returns constructed tree if successful and
 * returns FAILED if unsuccessful.
 *
 * Character Symbol : 'N'
 */
TREE Ntree() {
  TREE digit = Dtree();
  if (digit == FAILED){
    return FAILED;
  }
  TREE number_tail = NTtree();
  if (number_tail == FAILED){
    return FAILED;
  }
  return makeNode2('N', digit, number_tail);
}

/* Parses a factor from the input.
 * Returns constructed tree if successful and
 * returns FAILED if unsuccessful.
 *
 * Character Symbol : 'F'
 */
TREE Ftree() {
  if (!lookahead('(')) {
    TREE number = Ntree();
    if (number == FAILED){
      return FAILED;
    }
    return makeNode1('F', number);
  }
  else{
    if (!matchTerminal('(')){
      return FAILED;
    }
    TREE expression = Etree();
    if (expression == FAILED){
      return FAILED;
    }
    if (!matchTerminal(')')){
      return FAILED;
    }
    return makeNode3('F', makeNode0('('), expression, makeNode0(')'));
  }
}

/* Parses a factor "tail" from the input.
 * Returns constructed tree if successful and
 * returns FAILED if unsuccessful.
 *
 * Character Symbol : 'f'
 */
TREE FTtree() {
  if (lookahead('*')){
    if (!matchTerminal('*'))
      return FAILED;
    TREE factor = Ftree();
    if (factor == FAILED)
      return FAILED;
    TREE factor_tail = FTtree();
    if (factor_tail == FAILED)
      return FAILED;
    return makeNode3('f', makeNode0('*'), factor, factor_tail);
  }
  else if (lookahead('/')){
    if (!matchTerminal('/'))
      return FAILED;
    TREE factor = Ftree();
    if (factor == FAILED)
      return FAILED;
    TREE factor_tail = FTtree();
    if (factor_tail == FAILED)
      return FAILED;
    return makeNode3('f', makeNode0('/'), factor, factor_tail);
  }
  return makeNode1('f', makeNode0('e'));
}
/* Parses a term from the input.
 * Returns constructed tree if successful and
 * returns FAILED if unsuccessful.
 *
 * Character Symbol : 'T'
 */
TREE Ttree() {
  TREE factor = Ftree();
  if (factor == FAILED){
    return FAILED;
  }
  TREE factor_tail = FTtree();
  if (factor_tail == FAILED){
    return FAILED;
  }
  return makeNode2('T', factor, factor_tail);
}
/* Parses a term "tail" from the input.
 * Returns constructed tree if successful and
 * returns FAILED if unsuccessful.
 *
 * Character Symbol : 't'
 */
TREE TTtree() {
  if (lookahead('+')){
    if (!matchTerminal('+'))
      return FAILED;
    TREE term = Ttree();
    if (term == FAILED)
      return FAILED;
    TREE term_tail = TTtree();
    if (term_tail == FAILED)
      return FAILED;
    return makeNode3('t', makeNode0('+'), term, term_tail);
  }
  else if (lookahead('-')){
    if (!matchTerminal('-'))
      return FAILED;
    TREE term = Ttree();
    if (term == FAILED)
      return FAILED;
    TREE term_tail = TTtree();
    if (term_tail == FAILED)
      return FAILED;
    return makeNode3('t', makeNode0('-'), term, term_tail);
  }
  return makeNode1('t', makeNode0('e'));
}
/* Parses an expression from the input.
 * Returns constructed tree if successful and
 * returns FAILED if unsuccessful.
 *
 * Character Symbol : 'E'
 */
TREE Etree() {
  TREE term = Ttree();
  if (term == FAILED){
    return FAILED;
  }
  TREE term_tail = TTtree();
  if (term_tail == FAILED){
    return FAILED;
  }
  return makeNode2('E', term, term_tail);
}
/* Prints parse tree starting at chosen root
 *
 * i stands for the number of indents for
 * the current level
 */
void printTree(TREE root, int i){
  if (root != NULL){
    for (int j = i; j > 0; j--){
      printf("  ");
    }
    printf("%c\n", root->label);
    printTree(root->leftmostChild, i+1);
    printTree(root->rightSibling, i);
  }
}

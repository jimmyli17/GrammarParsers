/*
* File: expr.c
* Creator: Jimmy Li
* Created: Tue Oct 17 19:11:24 2017
* Time-stamp: <Tue Oct 17 23:15:42 EDT 2017 li>
*
* Project 2:
* Grammars and Parsing
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recursive_descent_parser.h"
#include "table_driven_parser.h"

void runPart1();
void runPart2();

int main (int argc, char *argv[]){
  printf("Part 1: Recursive Descent Parser\n");
  printf("--------------------------------\n");
  runPart1();
  printf("\nPart 2: Table Driven Parser\n");
  printf("--------------------------------\n");
  runPart2();
}

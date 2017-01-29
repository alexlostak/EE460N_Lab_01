//
//  parse.h
//  EE460N_Lab_01
//
//  Created by Alex Lostak on 1/29/17.
//  Copyright © 2017 Alex Lostak. All rights reserved.
//

#ifndef parse_h
#define parse_h

#include <stdio.h> /* standard input/output library */
#include <stdlib.h> /* Standard C Library */
#include <string.h> /* String operations library */
#include <ctype.h> /* Library for useful character operations */
#include <limits.h> /* Library for definitions of common variable type characteristics */


/*Hex numbers must be in the form “x3000”, and decimal numbers must be in the form “#30”.*/
int toNum(char* ptr);
/*
 Take a line of the input file and parse it into corresponding fields.
 Note that you need to write the isOpcode(char*) function which determines whether a string of characters is a valid opcode.
 */
int readAndParse(FILE * pInfile, char * pLine, char ** pLabel, char ** pOpcode, char ** pArg1, char ** pArg2, char ** pArg3, char ** pArg4);

int isOpcode(char* op);

#endif /* parse_h */

//
//  main.c
//  EE460N_Lab_01
//
//  Created by Alex Lostak on 1/28/17.
//  Copyright © 2017 Alex Lostak. All rights reserved.
//


#include <stdio.h> /* standard input/output library */
#include <stdlib.h> /* Standard C Library */
#include <string.h> /* String operations library */
#include <ctype.h> /* Library for useful character operations */
#include <limits.h> /* Library for definitions of common variable type characteristics */
#include "instructions.h"
#include "parse.h"



#define MAX_LINE_LENGTH 255
enum
{
	   DONE, OK, EMPTY_LINE
};

void testing(void) {
    instr_add_imm_t testAdd;
    testAdd.imm5 = 3;
    testAdd.A = 1;
    testAdd.SR1 = 2;
    testAdd.DR1 = 5;
    testAdd.opcode = 0xE;
    
    printf("Expected: 0xEAA3\n Actual: %x\n", testAdd);
    return;
}

int main(int argc, const char * argv[]) {
    
    char lLine[MAX_LINE_LENGTH + 1], *lLabel, *lOpcode, *lArg1,
    *lArg2, *lArg3, *lArg4;
    
	   int lRet;
    int i = 0;
    
    FILE * lInfile;
    
    testing();
    //testing, so returning here
    //return 0;
    lInfile = fopen( "data.in", "r" );	/* open the input file */
    do
        {
           lRet = readAndParse( lInfile, lLine, &lLabel,
                               &lOpcode, &lArg1, &lArg2, &lArg3, &lArg4 );
           if( lRet != DONE && lRet != EMPTY_LINE )
           {
               
               printf("Line %d - %s %s %s %s %s %s \n", i, lLabel, lOpcode, lArg1, lArg2, lArg3, lArg4);
               i++;
               
           }
       } while( lRet != DONE );
    return 0;
}

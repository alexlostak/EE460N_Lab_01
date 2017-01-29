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



#define MAX_LINE_LENGTH 255
enum
{
	   DONE, OK, EMPTY_LINE
};

int isOpcode (char* op) {
    return 1;
}

int
readAndParse( FILE * pInfile, char * pLine, char ** pLabel, char
             ** pOpcode, char ** pArg1, char ** pArg2, char ** pArg3, char ** pArg4
             )
{
	   char * lRet, * lPtr;
	   int i;
	   if( !fgets( pLine, MAX_LINE_LENGTH, pInfile ) )
           return( DONE );
	   for( i = 0; i < strlen( pLine ); i++ )
           pLine[i] = tolower( pLine[i] );
	   
    /* convert entire line to lowercase */
	   *pLabel = *pOpcode = *pArg1 = *pArg2 = *pArg3 = *pArg4 = pLine + strlen(pLine);
    
	   /* ignore the comments */
	   lPtr = pLine;
    
	   while( *lPtr != ';' && *lPtr != '\0' &&
             *lPtr != '\n' )
           lPtr++;
    
	   *lPtr = '\0';
	   if( !(lPtr = strtok( pLine, "\t\n ," ) ) )
           return( EMPTY_LINE );
    
	   if( isOpcode( lPtr ) == -1 && lPtr[0] != '.' ) /* found a label */
       {
           *pLabel = lPtr;
           if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );
       }
	   
    *pOpcode = lPtr;
    
	   if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );
	   
    *pArg1 = lPtr;
	   
    if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );
    
	   *pArg2 = lPtr;
	   if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );
    
	   *pArg3 = lPtr;
    
	   if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );
    
	   *pArg4 = lPtr;
    
	   return( OK );
}

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
    return 0;
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
    
    printf("Hello, World!\n");
    return 0;
}

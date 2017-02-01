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

typedef struct symboltable {
    char* symbol;
    int address;
} SymbolTable_t;

int main(int argc, const char * argv[]) {
    
    char lLine[MAX_LINE_LENGTH + 1], *lLabel, *lOpcode, *lArg1,
    *lArg2, *lArg3, *lArg4;
	   int lRet;
    int i = 0;
    int j = 0;
    int address = 0;
    instr_general_t* instrRepresentation;
    FILE * lInfile;
    instr_t* currentInstruction;
    
    SymbolTable_t* symbolTable = malloc(sizeof(SymbolTable_t) * 100);
    
    lInfile = fopen( "data.in", "r" );	/* open the input file */
    do
    {
        lRet = readAndParse( lInfile, lLine, &lLabel,
                            &lOpcode, &lArg1, &lArg2, &lArg3, &lArg4 );
        if( lRet != DONE && lRet != EMPTY_LINE )
        {
            if (!strcmp(lOpcode, ".orig")) {
                address = toNum(lArg1);
            }
            
            if (strcmp(lLabel,"")) {  /* If there is a label*/
                symbolTable[j].symbol = malloc(strlen(lLabel) + 1);
                strcpy(symbolTable[j].symbol, lLabel);
                symbolTable[j].address = address;
                j++;
            }
             
            printf("%x - %s %s %s %s %s %s \n", address, lLabel, lOpcode, lArg1, lArg2, lArg3, lArg4);
            i++;
            address += 2;
        }
    } while( lRet != DONE );
    
    printf("\nSymbol Table\n");
    for (i = 0; i < j; i++) {
        printf("%s - %x\n", symbolTable[i].symbol, symbolTable[i].address);
    }
    printf("entering second pass");
    
    
    
    //rewind(lInfile);
    fclose(lInfile);
    lInfile = fopen( "data.in", "r" );
    
    
    printf("\nafter file reopen\n");
    do
    {
        lRet = readAndParse( lInfile, lLine, &lLabel,
                            &lOpcode, &lArg1, &lArg2, &lArg3, &lArg4 );
        //printf("\nafter read and parse\n");
        if( lRet != DONE && lRet != EMPTY_LINE )
        {
            //printf("start of if loop\n");
            currentInstruction = instr_new(lLabel, lOpcode, lArg1, lArg2, lArg3, lArg4);
            
            instrRepresentation = repInstruction(currentInstruction);
            /*
           writeToFile(instrRepresentation);
             */
            printf("%x\n", *instrRepresentation); //segmentation fault here
            
        }
    } while( lRet != DONE );
    
    return 0;
}

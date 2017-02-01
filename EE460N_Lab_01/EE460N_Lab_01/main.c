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
char lLine[MAX_LINE_LENGTH + 1], *lLabel, *lOpcode, *lArg1,
*lArg2, *lArg3, *lArg4;
int j = 0;

void parseLoop(void (*doWorkOnFile)() ) {
    int lRet;
    FILE * lInfile;
    lInfile = fopen( "data.in", "r" );	/* open the input file */
    do
    {
        lRet = readAndParse( lInfile, lLine, &lLabel,
                            &lOpcode, &lArg1, &lArg2, &lArg3, &lArg4 );
        if(lRet != DONE && lRet != EMPTY_LINE ) {
            (*doWorkOnFile)();
        }
    } while( lRet != DONE );
    fclose(lInfile);
}

void createSymbolTable() {
    if (!strcmp(lOpcode, ".orig")) {
        address = toNum(lArg1);
        originAddress = address;
    }
    if (strcmp(lLabel,"")) {  /* If there is a label*/
        symbolTable[j].symbol = malloc(strlen(lLabel) + 1);
        strcpy(symbolTable[j].symbol, lLabel);
        symbolTable[j].address = address;
        j++;
        numOfLabels++;
    }
    printf("%x - %s %s %s %s %s %s \n", address, lLabel, lOpcode, lArg1, lArg2, lArg3, lArg4);
    address += 2;
}

void assemble() {
    instr_general_t* instrRepresentation;
    instr_t* currentInstruction;
    
    currentInstruction = instr_new(lLabel, lOpcode, lArg1, lArg2, lArg3, lArg4);
    instrRepresentation = repInstruction(currentInstruction);
    /*
     writeToFile(instrRepresentation);
     */
    printf("x%x - ", address);
    printf("%x\n", *instrRepresentation);
    address+=2;
}

int main(int argc, const char * argv[]) {
    int i = 0;
    symbolTable = malloc(sizeof(SymbolTable_t) * 100);
    
    parseLoop(createSymbolTable);
    
    printf("\nSymbol Table\n");
    for (i = 0; i < numOfLabels; i++) {
        printf("%s - %x\n", symbolTable[i].symbol, symbolTable[i].address);
    } printf("\n\n");
    
    parseLoop(assemble);
    
    return 0;
}

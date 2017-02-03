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
*lArg2, *lArg3, *lArg4, *inputFile, *outputFile;
int j = 0;
FILE *output, *lInfile;

void parseLoop(void (*doWorkOnFile)() ) {
    int lRet;
    lInfile = fopen( inputFile, "r" );
    output = fopen( outputFile, "w" );
    
    do
    {
        lRet = readAndParse( lInfile, lLine, &lLabel,
                            &lOpcode, &lArg1, &lArg2, &lArg3, &lArg4 );
        if(lRet != DONE && lRet != EMPTY_LINE ) {
            
            (*doWorkOnFile)();
        }
    } while( lRet != DONE );
    fclose(lInfile);
    fclose(output);
}

void createSymbolTable() {
    if (!strcmp(lOpcode, ".orig")) {
        address = toNum(lArg1);
        originAddress = address;
    }
    if (strcmp(lLabel,"")) {  /* If there is a label*/
        isValidLabel(lLabel);
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
    fprintf(output, "0x%.4X\n", *instrRepresentation);
    printf("x%x - %x\n", address, *instrRepresentation);
    address+=2;
}

void setInputOutput(int argc, const char * argv[]) {
    if (argc > 1) {
        /*inputFile = malloc(strlen(argv[1]) + 1);
        outputFile = malloc(strlen(argv[1]) + 1);
        strcpy(inputFile, argv[1]);
        strcpy(outputFile, argv[2]);
         */
         inputFile = (char*) argv[1];
        outputFile = (char*) argv[2];
        printf("input = %s and output = %s\n", inputFile, outputFile);
    } else {
        inputFile = malloc(strlen("data.in") + 1);
        outputFile = malloc(strlen("data.out") + 1);
        strcpy(inputFile, "data.in");
        strcpy(outputFile, "data.out");
    }
}

void printSymbolTable() {
    printf("\nSymbol Table\n");
    int i = 0;
    for (i = 0; i < numOfLabels; i++) {
        printf("%s - %x\n", symbolTable[i].symbol, symbolTable[i].address);
    } printf("\n\n");
}

int main(int argc, const char * argv[]) {
    symbolTable = malloc(sizeof(SymbolTable_t) * 100);
    setInputOutput(argc, argv);
    
    parseLoop(createSymbolTable);
    printSymbolTable();
    parseLoop(assemble);
    
    return 0;
}

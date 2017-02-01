//
//  instructions.h
//  EE460N_Lab_01
//
//  Created by Alex Lostak on 1/29/17.
//  Copyright © 2017 Alex Lostak. All rights reserved.
//

#ifndef instructions_h
#define instructions_h

typedef struct symboltable {
    char* symbol;
    int address;
} SymbolTable_t;

#include <stdio.h>
extern int address;
extern int originAddress;
extern int numOfLabels;
extern SymbolTable_t* symbolTable;

//lLabel, lOpcode, lArg1, lArg2, lArg3, lArg4
typedef struct instr {
    char* label;
    char* opcode;
    char* arg1;
    char* arg2;
    char* arg3;
    char* arg4;
} instr_t;

typedef struct instr_general{
    uint16_t imm5 : 16;
} instr_general_t;

typedef struct instr_add_imm {
    uint16_t imm5 : 5;
    uint16_t A : 1;
    uint16_t SR1 : 3;
    uint16_t DR1 : 3;
    uint16_t opcode : 4;
} instr_add_imm_t;

typedef struct instr_add_sr {
    uint16_t SR2 : 3;
    uint16_t opspec : 2;
    uint16_t A : 1;
    uint16_t SR1 : 3;
    uint16_t DR1 : 3;
    uint16_t opcode : 4;
} instr_add_sr_t;

typedef struct instr_orig {
    uint16_t address : 16;
} instr_orig_t;

typedef struct instr_lea {
    uint16_t offset : 9;
    uint16_t DR1 : 3;
    uint16_t opcode : 4;
} instr_lea_t;

instr_t* instr_new (char* lLabel, char* lOpcode, char* lArg1, char* lArg2, char* lArg3, char* lArg4);
instr_general_t* repInstruction(instr_t* i);

/*
 Determine op code type
 create instruction struct for said op code
 take next part of instruction
 add to instruction struct
 continue until opcode struct full
 output opcode struct
 
 */

#endif /* instructions_h */

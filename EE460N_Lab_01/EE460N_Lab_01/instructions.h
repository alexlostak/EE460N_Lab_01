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

typedef struct instr_and_imm {
    uint16_t imm5 : 5;
    uint16_t one : 1;
    uint16_t SR1 : 3;
    uint16_t DR1 : 3;
    uint16_t opcode : 4;
} instr_and_imm_t;

typedef struct instr_and_sr {
    uint16_t SR2 : 3;
    uint16_t zeros : 3;
    uint16_t SR1 : 3;
    uint16_t DR1 : 3;
    uint16_t opcode : 4;
} instr_and_sr_t;

typedef struct instr_jsr {
    uint16_t offset : 11;
    uint16_t steering : 1;
    uint16_t opcode : 4;
} instr_jsr_t;

typedef struct instr_jsrr {
    uint16_t zeros2 : 6;
    uint16_t baseReg : 3;
    uint16_t zeros : 2;
    uint16_t steering : 1;
    uint16_t opcode : 4;
} instr_jsrr_t;

typedef struct instr_rti {
    uint16_t zeros : 12;
    uint16_t opcode : 4;
} instr_rti_t;

typedef struct instr_lshf {
    uint16_t amount : 4;
    uint16_t zeros : 2;
    uint16_t SR : 3;
    uint16_t DR : 3;
    uint16_t opcode : 4;
} instr_lshf_t;

typedef struct instr_rshfl {
    uint16_t amount : 4;
    uint16_t zeros : 2;
    uint16_t SR : 3;
    uint16_t DR : 3;
    uint16_t opcode : 4;
} instr_rshfl_t;

typedef struct instr_rshfa {
    uint16_t amount : 4;
    uint16_t zeros : 2;
    uint16_t SR : 3;
    uint16_t DR : 3;
    uint16_t opcode : 4;
} instr_rshfa_t;

typedef struct instr_xor_sr {
    uint16_t SR2 : 3;
    uint16_t zeros : 3;
    uint16_t SR1 : 3;
    uint16_t DR : 3;
    uint16_t opcode : 4;
} instr_xor_sr_t;

typedef struct instr_xor_imm {
    uint16_t imm5 : 5;
    uint16_t one : 1;
    uint16_t SR : 3;
    uint16_t DR : 3;
    uint16_t opcode : 4;
} instr_xor_imm_t;

typedef struct instr_nop {
    uint16_t zeros : 16;
} instr_nop_t;

typedef struct instr_fill {
    uint16_t number : 16;
} instr_fill_t;

typedef struct instr_jmp {
    uint16_t opspec : 6;
    uint16_t baseR : 3;
    uint16_t DR1 : 3;
    uint16_t opcode : 4;
} instr_jmp_t;

typedef struct instr_not {
    uint16_t opspec : 5;
    uint16_t A : 1;
    uint16_t SR1 : 3;
    uint16_t DR1 : 3;
    uint16_t opcode : 4;
} instr_not_t;

typedef struct instr_ret {
    uint16_t opspec : 6;
    uint16_t SR1 : 3;
    uint16_t DR1 : 3;
    uint16_t opcode : 4;
} instr_ret_t;

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

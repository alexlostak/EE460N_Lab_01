//
//  instructions.h
//  EE460N_Lab_01
//
//  Created by Alex Lostak on 1/29/17.
//  Copyright © 2017 Alex Lostak. All rights reserved.
//

#ifndef instructions_h
#define instructions_h

#include <stdio.h>


//lLabel, lOpcode, lArg1, lArg2, lArg3, lArg4
typedef struct instr {
    char* label;
    uint16_t opcode;
    char* arg1;
    char* arg2;
    char* arg3;
    char* arg4;
} instr_t;


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

/*
 Determine op code type
 create instruction struct for said op code
 take next part of instruction
 add to instruction struct
 continue until opcode struct full
 output opcode struct
 
 */

#endif /* instructions_h */

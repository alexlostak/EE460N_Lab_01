//
//  instructions.c
//  EE460N_Lab_01
//
//  Created by Alex Lostak on 1/29/17.
//  Copyright © 2017 Alex Lostak. All rights reserved.
//

#include "instructions.h"
#include "parse.h"



uint16_t reg_to_uint16_t (char* reg) {
    
    return 1;
}

instr_t* instr_new (char* lLabel, uint16_t lOpcode, char* lArg1, char* lArg2, char* lArg3, char* lArg4) {
    instr_t* i = malloc(sizeof(instr_t));
    i->label = lLabel;
    i->opcode = lOpcode;
    i->arg1 = lArg1;
    i->arg2 = lArg2;
    i->arg3 = lArg3;
    i->arg4 = lArg4;
    return i;
    
}



instr_add_imm_t* instr_add_imm_t_new (instr_t* instr) {
    //convert args to numbers
    //assign numbers to fields in add struct
    //ADD R1, R1, #5
    //convert arg1
    uint16_t arg1;
    //convert arg2
    uint16_t arg2;
    //convert imm5
    uint16_t imm5 = toNum(instr->arg3);
    instr_add_imm_t* i = malloc(sizeof(instr_add_imm_t));
    i->opcode = instr->opcode;
    arg1 = instr->arg1[1] - 49;
    i->A = 1;
    i->imm5 = imm5;
    
    
    
    return i;
}

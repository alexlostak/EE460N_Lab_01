//
//  instructions.c
//  EE460N_Lab_01
//
//  Created by Alex Lostak on 1/29/17.
//  Copyright © 2017 Alex Lostak. All rights reserved.
//
#include <stdlib.h> /* Standard C Library */
#include "instructions.h"
#include "parse.h"

int originAddress = 0;
int address = 0;
int numOfLabels = 0;
SymbolTable_t* symbolTable;

uint16_t reg_to_uint16_t (char* reg) {
    uint16_t char_value;
    char_value = reg[1] - 48; //ASCII value of 0;
    return char_value;
}

int determine_add(char* final_arg) {
    if (final_arg[0] == 35) {
        return 1;
    }
    return 0;
}

uint16_t calcOffset(char* label) {
    int i;
    int offset;
    int labelAddress;
    for (i = 0; i < numOfLabels; i++) {
        if (!strcmp(label,symbolTable[i].symbol)) {
            labelAddress = symbolTable[i].address;
            break;
        }
    }
    offset = (labelAddress - (address + 2)) / 2;
    printf("offset = (%x - (%x + 2)) / 2 = %d\n", labelAddress, address, offset);
    return offset;
}

instr_t* instr_new (char* lLabel, char* lOpcode, char* lArg1, char* lArg2, char* lArg3, char* lArg4) {
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
    uint16_t arg1;
    uint16_t arg2;
    uint16_t imm5;
    instr_add_imm_t* i;
    arg1 = reg_to_uint16_t(instr->arg1);
    arg2 = reg_to_uint16_t(instr->arg2);
    imm5 = toNum(instr->arg3);
    i = malloc(sizeof(instr_add_imm_t));
    i->opcode = 1; //ADD OPCODE
    i->DR1 = arg1;
    i->SR1 = arg2;
    i->A = 1;
    i->imm5 = imm5;
    return i;
}

instr_add_sr_t* instr_add_sr_t_new(instr_t* instr) {
    uint16_t arg1;
    uint16_t arg2;
    uint16_t arg3;
    instr_add_sr_t* i;
    arg1 = reg_to_uint16_t(instr->arg1);
    arg2 = reg_to_uint16_t(instr->arg2);
    arg3 = reg_to_uint16_t(instr->arg3);
    i = malloc(sizeof(instr_add_sr_t));
    i->opcode = 1;
    i->DR1 = arg1;
    i->SR1 = arg2;
    i->A = 0;
    i->opspec = 0;
    i->SR2 = arg3;
    return i;
};

instr_not_t* instr_not_t_new(instr_t* instr) {
    uint16_t arg1;
    uint16_t arg2;
    instr_not_t* i;
    arg1 = reg_to_uint16_t(instr->arg1);
    arg2 = reg_to_uint16_t(instr->arg2);
    i = malloc(sizeof(instr_not_t));
    i->opcode = 9;
    i->DR1 = arg1;
    i->SR1 = arg2;
    i->A = 1;
    i->opspec = 9;
    return i;
}

instr_ret_t* instr_ret_t_new(instr_t* instr) {
    instr_ret_t* i;
    i = malloc(sizeof(instr_ret_t));
    i->opcode =12;
    i->DR1 = 0;
    i->SR1 = 7;
    i->opspec = 0;
    return i;
}

instr_orig_t* instr_orig_t_new (instr_t* instr) {
    instr_orig_t* i;
    i = malloc(sizeof(instr_orig_t));
    i->address = toNum(instr->arg1);
    address = originAddress;
    return i;
}



instr_lea_t* instr_lea_t_new (instr_t* instr) {
    uint16_t offset;
    instr_lea_t* i;
    i = malloc(sizeof(instr_general_t));
    i->opcode = 14;
    i->DR1 = reg_to_uint16_t(instr->arg1);
    offset = calcOffset(instr->arg2);
    i->offset = offset;
    return i;
}

instr_general_t* instruction_add(instr_t* instr) {
    if (determine_add(instr->arg3)) {
        return instr_add_imm_t_new(instr);
    }
    return instr_add_sr_t_new(instr);
}

instr_lea_t* instruction_lea(instr_t* instr) {
    return instr_lea_t_new(instr);
}

instr_general_t* instruction_not(instr_t* instr) {
    return instr_not_t_new(instr);
}

instr_ret_t* instruction_ret(instr_t* instr) {
    return instr_ret_t_new(instr);
}


instr_general_t* repInstruction(instr_t* instr) {
    if (!strcmp(instr->opcode, "add")) {
        return instruction_add(instr);
    } else if (!strcmp(instr->opcode, ".orig")) {
        return instr_orig_t_new(instr);
    } else if (!strcmp(instr->opcode, "lea")) {
        return instruction_lea(instr);
    } else if (!strcmp(instr->opcode, "not")) {
        return instruction_not(instr);
    }
    
        /*
    
    } else if (!strcmp(op, "brn")) {
        return 1;
    } else if (!strcmp(op, "brp")) {
        return 1;
    } else if (!strcmp(op, "brnp")) {
        return 1;
    } else if (!strcmp(op, "br")) {
        return 1;
    } else if (!strcmp(op, "brz")) {
        return 1;
    } else if (!strcmp(op, "brnz")) {
        return 1;
    } else if (!strcmp(op, "brzp")) {
        return 1;
    } else if (!strcmp(op, "brnzp")) {
        return 1;
    } else if (!strcmp(op, "jmp")) {
        return 1;
    } else if (!strcmp(op, "jsr")) {
        return 1;
    } else if (!strcmp(op, "jsrr")) {
        return 1;
    } else if (!strcmp(op, "ldb")) {
        return 1;
    } else if (!strcmp(op, "ldw")) {
        return 1;
    } else if (!strcmp(op, "lea")) {
        return 1;
    } else if (!strcmp(op, "rti")) {
        return 1;
    } else if (!strcmp(op, "shf")) {
        return 1;
    } else if (!strcmp(op, "stb")) {
        return 1;
    } else if (!strcmp(op, "stw")) {
        return 1;
    } else if (!strcmp(op, "trap")) {
        return 1;
    } else if (!strcmp(op, "xor")) {
        return 1;
    }
    */
    return NULL;
}






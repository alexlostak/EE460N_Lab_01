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
    //convert args to numbers
    //assign numbers to fields in add struct
    //ADD R1, R1, #5
    //convert arg1
    //variable declaration
    uint16_t arg1;
    //convert arg2
    uint16_t arg2;
    //convert imm5
    uint16_t imm5;
    instr_add_imm_t* i;
    arg1 = reg_to_uint16_t(instr->arg1);
    arg2 = reg_to_uint16_t(instr->arg2);
    imm5 = toNum(instr->arg3);
    i = malloc(sizeof(instr_add_imm_t));
    i->opcode = 1;
    i->A = 1;
    i->imm5 = imm5;
    i->DR1 = arg1;
    i->SR1 = arg2;
    return i;
}

instr_add_sr_t* instr_add_sr_t_new(void) {
    return NULL;
};

instr_orig_t* instr_orig_t_new (instr_t* instr) {
    instr_orig_t* i;
    i = malloc(sizeof(instr_orig_t));
    i->address = toNum(instr->arg1);
    address = originAddress;
    return i;
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

instr_general_t* repInstruction(instr_t* instr) {
    if (!strcmp(instr->opcode, "add")) {
        return instr_add_imm_t_new(instr);
    } else if (!strcmp(instr->opcode, ".orig")) {
        return instr_orig_t_new(instr);
    } else if (!strcmp(instr->opcode, "lea")) {
        return instr_lea_t_new(instr);
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






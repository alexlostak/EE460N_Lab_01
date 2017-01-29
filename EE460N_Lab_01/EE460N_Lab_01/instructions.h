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

typedef struct instr_add_imm {
    uint16_t imm5 : 5;
    uint16_t A : 1;
    uint16_t SR1 : 3;
    uint16_t DR1 : 3;
    uint16_t opcode : 4;
} instr_add_imm_t;





#endif /* instructions_h */

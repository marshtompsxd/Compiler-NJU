//
// Created by sunxudong on 12/27/17.
//

#ifndef COMPILER_SPIM_H
#define COMPILER_SPIM_H

#include "../common.h"
#include "../intercode/IC.h"
#include "../intercode/ICTable.h"
#include "../intercode/InterCode.h"

enum { MTEMP, MVAR };

typedef struct ArgInStackEntry_ AISE;

extern void MachineCodeGenerator(char *filename);

struct ArgInStackEntry_ {

  Operand *op;
};

#endif // COMPILER_SPIM_H

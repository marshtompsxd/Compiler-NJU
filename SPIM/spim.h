//
// Created by sunxudong on 12/27/17.
//

#ifndef COMPILER_SPIM_H
#define COMPILER_SPIM_H

enum { MTEMP, MVAR };

typedef struct ArgInRegEntry_ AIRE;
typedef struct ArgInStackEntry_ AISE;

extern void MachineCodeGenerator(char* filename);


struct ArgInRegEntry_ {

    //int ARegNo;
    int kind; // MTEMP or MVAR
    int Index;

};


struct ArgInStackEntry_ {

    int kind;
    int Index;
};

#endif //COMPILER_SPIM_H

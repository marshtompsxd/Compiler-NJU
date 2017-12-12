//
// Created by sunxudong on 12/11/17.
//
#ifndef COMPILER_ICTABLE_H
#define COMPILER_ICTABLE_H

#include "InterCode.h"
#include "ParsingNode.h"

extern void GenerateICVarTable(SymbolTableHead* table);

extern void GenerateICFunTable(SymbolTableHead* table);

extern void CheckElemInICVarTable(ICVarTableHead* table);

extern void CheckElemInICFunTable(ICFunTableHead* table);

extern ICVarEntry* LookUpForICVarEntry(char* VariableName);

int NewLabelIndex();

extern Operand* NewVOperand(int attr, int VIndex);

extern Operand* NewTOperand(int attr);

extern Operand* NewICOperand(int ICons);

extern Operand* NewFCOperand(float FCons);

extern Operand* GetLvalueIDOperand(ParsingNode* node);

extern void InsertInterCodeEntry(InterCodeEntry* entry);

extern void InsertEntryIntoInterCodeList(InterCodeEntry* entry, InterCodeListHead* list);

extern void MergeInterCodeList(InterCodeListHead* sublist, InterCodeListHead* list);

extern int arithmeticConvert(int arithmetic);

extern InterCodeEntry* NewInterCodeEntryBINOP(int kind, Operand* result, Operand* op1, Operand* op2);

extern InterCodeEntry* NewInterCodeEntryASSIGN(Operand* left, Operand* right);

extern InterCodeEntry* NewInterCodeEntryIFGT(Operand* op1, Operand* op2, int relop, int LIndex);

extern InterCodeEntry* NewInterCodeEntryGT(int LIndex);

extern InterCodeEntry* NewInterCodeEntryLABELDEC(int LIndex);



#endif //COMPILER_ICTABLE_H

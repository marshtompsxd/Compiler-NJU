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

extern int GetAccumulatedSizeReverse(ICVarEntry* VE, int rdim);

extern bool IsARRAYID(char* VariableName);

extern void InsertInterCodeEntry(InterCodeEntry* entry);

extern void PushEntryIntoArgList(ArgEntry* entry, ArgListHead* list);

extern void InsertEntryIntoInterCodeList(InterCodeEntry* entry, InterCodeListHead* list);

extern void MergeInterCodeList(InterCodeListHead* sublist, InterCodeListHead* list);

extern int arithmeticConvert(int arithmetic);

extern InterCodeEntry* NewInterCodeEntryBINOP(int kind, Operand* result, Operand* op1, Operand* op2);

extern InterCodeEntry* NewInterCodeEntryASSIGN(Operand* left, Operand* right);

extern InterCodeEntry* NewInterCodeEntryIFGT(Operand* op1, Operand* op2, int relop, int LIndex);

extern InterCodeEntry* NewInterCodeEntryGT(int LIndex);

extern InterCodeEntry* NewInterCodeEntryLABELDEC(int LIndex);

extern InterCodeEntry* NewInterCodeEntryCALL(Operand* ret, char* funName);

extern InterCodeEntry* NewInterCodeEntryRET(Operand* ret);

extern InterCodeEntry* NewInterCodeEntryREAD(Operand* input);

extern InterCodeEntry* NewInterCodeEntryWRITE(Operand* output);

extern InterCodeEntry* NewInterCodeEntryARG(Operand* arg);

extern InterCodeEntry* NewInterCodeEntryDEC(Operand* address, int size);

extern InterCodeEntry* NewInterCodeEntryFUN(char* funName);

extern InterCodeEntry* NewInterCodeEntryPARAM(Operand* parameter);

extern ArgEntry* NewArgEntry(Operand* op);

extern void DeleteInterCodeEntry(InterCodeEntry* ICE, InterCodeListHead* list);

extern void PrintInterCodeList(InterCodeListHead* list);

#endif //COMPILER_ICTABLE_H

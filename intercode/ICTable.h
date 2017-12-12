//
// Created by sunxudong on 12/11/17.
//
#include "InterCode.h"

#ifndef COMPILER_ICTABLE_H
#define COMPILER_ICTABLE_H

extern void InsertEntryIntoICVarTable(ICVarEntry* entry, ICVarTableHead* table);

extern void InsertEntryIntoICFunTable(ICFunEntry* entry, ICFunTableHead* table);

extern void GenerateICVarTable(SymbolTableHead* table);

extern void GenerateICFunTable(SymbolTableHead* table);

extern void CheckElemInICVarTable(ICVarTableHead* table);

extern void CheckElemInICFunTable(ICFunTableHead* table);

#endif //COMPILER_ICTABLE_H

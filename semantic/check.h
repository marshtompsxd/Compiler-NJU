#ifndef __CHECK_H__
#define __CHECK_H__

#include "symbol_table.h"
#include "../common.h"
#include <stdlib.h>

//Error Type 15
// need repair
extern void CheckDuplicatedFieldNameInOneStruct(Type* TP);

//Error Type 3 and 16
extern void CheckSameVarNameInSymbolTable(char* varname, int lineno, SymbolTableHead* table, int Name);

extern void CheckSameFunNameInSymbolTable(char* funname, int lineno, SymbolTableHead* table);

extern void CheckSameFieldNameInStruct(char* fieldname, int lineno, Type* TP, int Name);

extern void CheckSameVarNameInStructTypeTable(char* varname, int lineno, StructTypeTableHead* table, int Name);

extern void CheckSameVarNameInParamList(char* varname, int lineno, ParamList* PL);

extern void CheckElemInTable(SymbolTableHead* table);

extern bool CheckTypeEquivalence(Type* T1, Type* T2);

extern bool IsTypeInt(Type* T);

extern bool IsTypeFloat(Type* T);

extern bool IsTypeStruct(Type* T);

extern bool IsArray(Type* T);

extern char* GenerateTypeString(Type* TP);

extern char* GenerateParamString(ParamList* PL);

extern bool CheckParamEquivalence(ParamList* PL1, ParamList* PL2);

extern void CheckElemInICVarTable(ICVarTableHead* table);

extern void CheckElemInICFunTable(ICFunTableHead* table);


#endif
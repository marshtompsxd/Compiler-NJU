#ifndef __LIST_H__
#define __LIST_H__

#include "symbol_table.h"
#include "../intercode/InterCode.h"
#include <stdlib.h>

extern FieldList* FLTail(FieldList* FL);

extern void InsertItemIntoSymbolTable(SymbolTableEntry* item, SymbolTableHead* table);

extern void InsertItemIntoStructTypeTable(StructTypeTableEntry* item, StructTypeTableHead* table);

extern Type* LookUpForStructTypeFromStructTypeTable(char* structname, StructTypeTableHead* table);

extern Type* LookUpForStructType(char* structname);

extern SymbolTableEntry* LookUpForVarDefFromSymbolTable(char* varname, SymbolTableHead* table);

extern SymbolTableEntry* LookUpForVarDef(char* varname);

extern SymbolTableEntry* LookUpForFunDefFromSymbolTable(char* funname, SymbolTableHead* table);

extern SymbolTableEntry* LookUpForFunDef(char* funname);

extern SymbolTableEntry* LookUpForParam(char* varname, ParamList* PL);

extern Type* LookUpForField(char* fieldname, Type* TP);

extern void PushPrevTable();

extern void PopPrevTable();



#endif
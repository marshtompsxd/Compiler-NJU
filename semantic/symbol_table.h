#ifndef __SYMBOL_TABLE__
#define __SYMBOL_TABLE__

#include "../common.h"

typedef struct Type_ Type;
typedef struct FieldList_ FieldList;
typedef struct SymbolTableEntry_ SymbolTableEntry;
typedef struct SymbolTableHead_ SymbolTableHead;
typedef struct StructTypeTableEntry_ StructTypeTableEntry;
typedef struct StructTypeTableHead_ StructTypeTableHead;
typedef struct ParamList_ ParamList;

enum { BASIC, ARRAY, STRUCTURE };
enum { VAR, FUN };
enum { LV, RV };
enum { VarName, StructName, FieldName };

struct Type_
{
	int kind;
	union
	{
		int basic;
		struct { Type* elem; int size; int * DimSize; int dim;} array;
		struct { char* structname; FieldList* member;} structure;
	};
};

struct FieldList_
{
	char* name; 
	Type* type; 
	int lineno;
	FieldList* tail; 
};

struct SymbolTableEntry_
{
	int kind;
	int lineno;
	union {
		struct { char* VariableName; Type* VariableType; } Variable;
		struct { char* FunName; Type* RetType; ParamList* PL; } Function;
	};
	SymbolTableEntry* tail;
};

struct SymbolTableHead_
{
	SymbolTableEntry* head;
};

struct StructTypeTableEntry_
{
	int lineno;
	Type* TP;
	StructTypeTableEntry* tail;
};

struct StructTypeTableHead_
{
	StructTypeTableEntry* head;
};

struct ParamList_
{
	SymbolTableEntry* head;
};

#define STACK_SIZE 100

extern int sym_top;
extern int struct_top;

extern SymbolTableHead* RootSymbolTable;
extern SymbolTableHead* CurrentSymbolTable;
extern SymbolTableHead* SymbolTableStack[STACK_SIZE];

extern StructTypeTableHead* RootStructTypeTable;
extern StructTypeTableHead* CurrentStructTypeTable;
extern StructTypeTableHead* StructTypeTableStack[STACK_SIZE];

#endif
#ifndef  __INTERCODE__
#define  __INTERCODE__

#include "../common.h"
#include "symbol_table.h"

typedef struct Operand_ Operand;
typedef struct InterCode_ InterCode;
typedef struct Cond_ Cond;

typedef struct ICVarEntry_ ICVarEntry;
typedef struct ICFunEntry_ ICFunEntry;
typedef struct InterCodeEntry_ InterCodeEntry;

typedef struct ICVarTableHead_ ICVarTableHead;
typedef struct ICFunTableHead_ ICFunTableHead;
typedef struct InterCodeListHead_ InterCodeListHead;

enum { VARIABLE, TEMP, CONSTANT };
enum { VALUE, ADDRESS, REFERENCE };
enum { 	ASSIGN, ADD, SUB, MUL, DIV, GOTO, IF, 
		RETURN, DEC, ARG, CALL, PARAM, READ, WRITE };

extern ICVarTableHead* RootICVarTable;
extern ICFunTableHead* RootICFunTable;
extern InterCodeListHead* RootInterCodeList;

extern int VIndex, TIndex;

struct ICVarEntry_{
	char* VariableName; 
	Type* VariableType;
    int VIndex;
	ICVarEntry* next;
};

struct ICFunEntry_{
	char* FunName;
	ICFunEntry* next;
};

struct InterCodeEntry_{
	InterCode* IC;
    InterCodeEntry* prev;
	InterCodeEntry* next;
};

struct ICVarTableHead_
{
	ICVarEntry* head;
};

struct ICFunTableHead_
{
	ICFunEntry* head;
};

struct InterCodeListHead_{
	InterCodeEntry* head;
};

struct Operand_ {
	int kind;
    int attr;
	union
	{
        int VIndex;
        int TIndex;
        int consValue;
	};

};

struct Cond_ {
	Operand* op1, op2;
	int relop;
	
};

struct InterCode_ {
	int kind;
	union {
		struct {
			char* dstLabel;
		}labelDec;

		struct {
			char* funName;
		}funDec;

		struct {
			Operand *right, *left;
		}assign;

		struct {
			Operand *result, *op1, *op2;
		}binop;

		struct {
			char* dstLabel;
		}gt;

		struct {
			Cond* condition;
			char* dstLabel;
		}ifgt;

		struct {
			Operand* retValue;
		}ret;

		struct {
			Operand* address;
			int size;
		}spaceDec;

		struct {
			Operand* argument;
		}arg;

		struct {
			Operand* dst;
			char* funName;
		}call;

		struct {
			Operand* parameter;
		}param;

		struct {
			Operand* input;
		}readFun;

		struct {
			Operand* output;
		}writeFun;
	};
};



#endif 

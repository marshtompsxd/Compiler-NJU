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

enum { OVAR, OTEMP, OICONS, OFCONS }; 	//kind of Operand
enum { OVALUE, OADDR, OREF };			//attr of Operand
enum { 	IASSIGN, IADD, ISUB, IMUL, IDIV, IGOTO, IIF,
		IRETURN, IDEC, IARG, ICALL, IPARAM, IREAD, IWRITE }; //kind of InterCode

extern ICVarTableHead* RootICVarTable;
extern ICFunTableHead* RootICFunTable;
extern InterCodeListHead* RootInterCodeList;

extern int VIndex, TIndex, LIndex;

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
        int ICons;
		float FCons;
	};

};

struct Cond_ {
	Operand* op1, op2;
	int relop;
};

struct InterCode_ {
	int kind;
	union {
		struct { int LIndex; }LABELDEC;

		struct { char* funName; }FUNDEC;

		struct { Operand *right, *left; }ASSIGN;

		struct { Operand *result, *op1, *op2; }BINOP;

		struct { int LIndex; }GT;

		struct { Cond* condition; int LIndex; }IFGT;

		struct { Operand* retValue; }RET;

		struct { Operand* address; int size; }SPACEDEC;

		struct { Operand* argument; }ARG;

		struct { Operand* dst; char* funName; }CALL;

		struct { Operand* parameter; }PARAM;

		struct { Operand* input; }READ;

		struct { Operand* output; }WRITE;
	};
};



#endif 

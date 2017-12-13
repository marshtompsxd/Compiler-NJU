#ifndef __Parsing_NODE__
#define __Parsing_NODE__

#include "../common.h"


//#define TERMINAL_DEBUG
//#define VARIABLE_DEBUG

enum {	AINT = 0, AFLOAT, AID, ASEMI, ACOMMA, AASSIGNOP, ARELOP, 
		APLUS, AMINUS, ASTAR, ADIV, AAND, AOR, ADOT, ANOT, ATYPE,
		ALP, ARP, ALB, ARB, ALC, ARC, ASTRUCT, ARETURN, AIF, AELSE, AWHILE,
		AProgram, AExtDefList, AExtDef, ASpecifier, AExtDecList,
		AVarDec, AStructSpecifier, AOptTag, ATag, AFunDec, AVarList, 
		AParamDec, ACompSt, AStmtList, AStmt, AExp, ADef, ADefList, 
		ADec, ADecList, AArgs};

enum { Terminal, Variable, Dummy };

enum { EQ, LT, GT, NEQ, LEQ, GEQ };

extern bool ParsingSwitch;

extern char* relopTable[6];

struct ParsingNode
{
	int kind;
    int SymbolIndex;
    int lineno;
    int depth;
    int childrenNum;
    struct ParsingNode* firstchild;
    struct ParsingNode* parent;
    struct ParsingNode* nextsibiling;
	union
	{
		char* IDname; // for ID
		int type; // for TYPE
    	int int_value; // for INT
    	float float_value; // for FLOAT
    	int relop_kind; // for RELOP
	};   
};

typedef struct ParsingNode ParsingNode;

extern ParsingNode* ParsingRoot;

extern bool CheckLvalue(ParsingNode* node);

extern bool IsArithmeticNode(ParsingNode* node);

extern bool IsLogicNode(ParsingNode* node);

extern bool IsRELOPNode(ParsingNode* node);

extern ParsingNode* GenerateSimpleTerminalNode(int TerminalType, int lineno);

extern ParsingNode* GenerateIDNode(int lineno, char* text);

extern ParsingNode* GenerateRELOPNode(int lineno, char* text);

extern ParsingNode* GenerateTypeNode(int TerminalType, int lineno, char* text);

extern ParsingNode* GenerateDummyNode(int VariableType);

extern ParsingNode* GenerateVariableNode(int VariableType, int childrenNum, ...);

extern void SetDepthOfParsingTree(ParsingNode* node, int depth);

extern void PreorderPrintParsingTree(ParsingNode* node);

extern void SyntaxOutput(ParsingNode* node);

#endif 
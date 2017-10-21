#ifndef __Parsing_NODE__
#define __Parsing_NODE__

#define int_type 0
#define float_type 1

#define lexical_type 0
#define syntax_type 1

#define true 1
#define false 0

typedef int bool;

//#define TERMINAL_DEBUG
//#define VARIABLE_DEBUG

enum {	AINT = 0, AFLOAT, AID, ASEMI, ACOMMA, AASSIGNOP, ARELOP, 
		APLUS, AMINUS, ASTAR, ADIV, AAND, AOR, ADOT, ANOT, ATYPE,
		ALP, ARP, ALB, ARB, ALC, ARC, ASTRUCT, ARETURN, AIF, AELSE, AWHILE,
		AProgram, AExtDefList, AExtDef, ASpecifier, AExtDecList,
		AVarDec, AStructSpecifier, AOptTag, ATag, AFunDec, AVarList, 
		AParamDec, ACompSt, AStmtList, AStmt, AExp, ADef, ADefList, 
		ADec, ADecList, AArgs};

extern char* symbolsTable[48];
extern char* typeTables[2];
extern bool ParsingSwitch;
struct ParsingNode
{
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
	};   
};

typedef struct ParsingNode ParsingNode;

extern ParsingNode* ParsingRoot;

extern ParsingNode* GenerateSimpleTerminalNode(int TerminalType, int lineno);

extern ParsingNode* GenerateIDNode(int lineno, char* text);

extern ParsingNode* GenerateTypeNode(int TerminalType, int lineno, char* text);

extern ParsingNode* GenerateVariableNode(int VariableType, int childrenNum, ...);

extern void SetDepthOfParsingTree(ParsingNode* node, int depth);

extern void PrintSpace(ParsingNode* node);

extern void PrintParsingNode(ParsingNode* node);

extern void PreorderPrintParsingTree(ParsingNode* node);

#endif 
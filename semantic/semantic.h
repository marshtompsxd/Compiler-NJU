#ifndef __SEMANTIC__
#define __SEMANTIC__

#include "symbol_table.h"
#include "../lexical_syntax/ParsingNode.h"


extern void SemanticAnalysis(ParsingNode* node);
extern bool SemanticSwitch;

#endif
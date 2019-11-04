#ifndef __SEMANTIC__
#define __SEMANTIC__

#include "../lexical_syntax/ParsingNode.h"
#include "symbol_table.h"

extern void SemanticAnalysis(ParsingNode *node);
extern bool SemanticSwitch;

#endif
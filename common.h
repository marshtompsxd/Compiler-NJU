#ifndef __COMMON__
#define __COMMON__

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define int_type 0
#define float_type 1

#define lexical_type 0
#define syntax_type 1

#define true 1
#define false 0

typedef int bool;

#define skind(node) node->SymbolIndex

#define firstchild(node) node->firstchild
#define secondchild(node) firstchild(node)->nextsibiling
#define thirdchild(node) secondchild(node)->nextsibiling
#define fourthchild(node) thirdchild(node)->nextsibiling
#define fifthchild(node) fourthchild(node)->nextsibiling
#define sixthchild(node) fifthchild(node)->nextsibiling
#define seventhchild(node) sixthchild(node)->nextsibiling

#endif
//
// Created by sunxudong on 12/14/17.
//
#include "optimazation.h"
#include "ICTable.h"
#include "InterCode.h"
#include "IC.h"

bool OperandEquivalence(Operand* op1, Operand* op2)
{
    if(!(op1->attr == op2->attr && op1->kind == op2->kind))return false;
    if(op1->kind == OICONS)return op1->ICons == op2->ICons;
    else if(op1->kind == OFCONS)return op1->FCons == op2->FCons;
    else if(op1->kind == OVAR)return op1->VIndex == op2->VIndex;
    else return op1->TIndex == op2->TIndex;

}

static void RedundantAssignElimation(InterCodeEntry* ICE, InterCodeListHead* list)
{
    assert(ICE->IC->kind == IASSIGN);
    InterCodeEntry* ICEHead = list->head;

    

}

void InterCodeOptimazation(InterCodeListHead* list)
{

}

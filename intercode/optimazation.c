//
// Created by sunxudong on 12/14/17.
//
#include "optimazation.h"
#include "InterCode.h"

bool OperandEquivalence(Operand* op1, Operand* op2)
{
    if(!(op1->attr == op2->attr && op1->kind == op2->kind))return false;
    if(op1->kind == OICONS)return op1->ICons == op2->ICons;
    else if(op1->kind == OFCONS)return op1->FCons == op2->FCons;
    else if(op1->kind == OVAR)return op1->VIndex == op2->VIndex;
    else return op1->TIndex == op2->TIndex;

}

bool OperandOverlap(Operand* op1, Operand* op2)
{
    if(op1->kind != op2->kind)return false;
    if(op1->kind == OICONS)return op1->ICons == op2->ICons;
    else if(op1->kind == OFCONS)return op1->FCons == op2->FCons;
    else if(op1->kind == OVAR)return op1->VIndex == op2->VIndex;
    else return op1->TIndex == op2->TIndex;
}

void ReplaceOperand(Operand* opdst, Operand* opsrc)
{
    memcpy(opdst, opsrc, sizeof(Operand));
}

static void RAPairProcess(InterCodeEntry* formerAssign, InterCodeEntry* laterCode)
{
    Operand* left = formerAssign->IC->ASSIGN.left;
    Operand* right = formerAssign->IC->ASSIGN.right;
    if(laterCode->IC->kind == IADD || laterCode->IC->kind == ISUB || laterCode->IC->kind == IMUL
       || laterCode->IC->kind == IDIV )
    {
        if( OperandEquivalence(laterCode->IC->BINOP.op1, left))
        {
            ReplaceOperand(laterCode->IC->BINOP.op1, right);
        }
        else if(OperandEquivalence(laterCode->IC->BINOP.op2, left))
        {
            ReplaceOperand(laterCode->IC->BINOP.op2, right);
        }
    }
    else if(laterCode->IC->kind == IASSIGN)
    {
        if( OperandEquivalence(laterCode->IC->ASSIGN.right, left))
        {
            ReplaceOperand(laterCode->IC->ASSIGN.right, right);
        }
    }
    else if(laterCode->IC->kind == IRETURN)
    {
        if( OperandEquivalence(laterCode->IC->RET.ret, left))
        {
            ReplaceOperand(laterCode->IC->RET.ret, right);
        }
    }
    else if(laterCode->IC->kind == IIFGOTO)
    {
        if(OperandEquivalence(laterCode->IC->IFGT.condition->op1, left))
        {
            ReplaceOperand(laterCode->IC->IFGT.condition->op1, right);
        }
        else if(OperandEquivalence(laterCode->IC->IFGT.condition->op2, left))
        {
            ReplaceOperand(laterCode->IC->IFGT.condition->op2, right);
        }
    }
}

static bool Used(Operand* left, InterCodeEntry* laterCode)
{
    if(laterCode->IC->kind == IADD || laterCode->IC->kind == ISUB || laterCode->IC->kind == IMUL
       || laterCode->IC->kind == IDIV )
    {
        if( OperandOverlap(laterCode->IC->BINOP.op1, left))
        {
            return true;
        }
        else if(OperandOverlap(laterCode->IC->BINOP.op2, left))
        {
            return true;
        }
    }
    else if(laterCode->IC->kind == IASSIGN)
    {
        if( OperandOverlap(laterCode->IC->ASSIGN.right, left) )
        {
            return true;
        }
        else if(OperandOverlap(laterCode->IC->ASSIGN.left, left)
                && laterCode->IC->ASSIGN.left->attr == OREF)
        {
            return true;
        }
    }
    else if(laterCode->IC->kind == IRETURN)
    {
        if( OperandOverlap(laterCode->IC->RET.ret, left))
        {
            return true;
        }
    }
    else if(laterCode->IC->kind == IIFGOTO)
    {
        if(OperandOverlap(laterCode->IC->IFGT.condition->op1, left))
        {
            return true;
        }
        else if(OperandOverlap(laterCode->IC->IFGT.condition->op2, left))
        {
            return true;
        }
    }
    else if(laterCode->IC->kind == IARG)
    {
        if(OperandOverlap(laterCode->IC->ARG.argument, left))
        {
            return true;
        }
    }
    else if(laterCode->IC->kind == ICALL)
    {
        if(OperandOverlap(laterCode->IC->CALL.ret, left))
        {
            return true;
        }
    }
    else if(laterCode->IC->kind == IREAD)
    {
        if(OperandOverlap(laterCode->IC->READ.input, left))
        {
            return true;
        }
    }
    else if(laterCode->IC->kind == IWRITE)
    {
        if(OperandOverlap(laterCode->IC->WRITE.output, left))
        {
            return true;
        }
    }
    return false;
}

static bool Pollution(InterCodeEntry* formerAssign, InterCodeEntry* laterCode)
{
    Operand* left = formerAssign->IC->ASSIGN.left;
    Operand* right = formerAssign->IC->ASSIGN.right;
    if(laterCode->IC->kind == IASSIGN)
    {
        if(laterCode->IC->ASSIGN.left->attr == OREF )
            return true;
        else if(OperandEquivalence(laterCode->IC->ASSIGN.left, left))
            return true;
        else if(OperandEquivalence(laterCode->IC->ASSIGN.left, right))
            return true;
    }
    else if(laterCode->IC->kind == ICALL)
    {
        if(laterCode->IC->RET.ret->attr == OREF )
            return true;
        else if(OperandEquivalence(laterCode->IC->RET.ret, left))
            return true;
        else if(OperandEquivalence(laterCode->IC->RET.ret, right))
            return true;
    }
    return false;
}

static void RedundantAssignElimation(InterCodeEntry* formerAssign, InterCodeListHead* list)
{
    assert(formerAssign->IC->kind == IASSIGN);
    InterCodeEntry* ICEHead = list->head;
    InterCodeEntry* entry = formerAssign->next;
    Operand* left = formerAssign->IC->ASSIGN.left;
    InterCodeEntry* stop = ICEHead;

    while (entry != ICEHead)
    {
        if(Pollution(formerAssign, entry))
        {
            stop = entry;
            break;
        }
        RAPairProcess(formerAssign, entry);
        entry = entry->next;
    }

    entry = formerAssign->next;

    while (entry != ICEHead)
    {
        if(Used(left, entry))return;
        entry = entry->next;
    }

    DeleteInterCodeEntry(formerAssign, list);

}

void InterCodeOptimazation(InterCodeListHead* list)
{
    InterCodeEntry* ICEHead = list->head;
    InterCodeEntry* entry = list->head->next;

    while (entry != ICEHead)
    {
        if(entry->IC->kind == IASSIGN && entry->IC->ASSIGN.left->kind == OTEMP
                && entry->IC->ASSIGN.left->attr == OVALUE
                && entry->IC->ASSIGN.right->attr == OVALUE)
        {
            RedundantAssignElimation(entry, list);
        }

        entry = entry->next;
    }

    entry = list->head->next;
    while (entry != ICEHead)
    {
        if(entry->IC->kind == IASSIGN
           && OperandEquivalence(entry->IC->ASSIGN.left, entry->IC->ASSIGN.right))
            DeleteInterCodeEntry(entry, list);

        entry = entry->next;
    }

}

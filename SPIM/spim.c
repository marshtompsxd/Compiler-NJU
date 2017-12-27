//
// Created by sunxudong on 12/27/17.
//

#include <symbol_table.h>
#include "../common.h"
#include "../intercode/IC.h"
#include "../intercode/ICTable.h"
#include "../intercode/InterCode.h"

int VSize;
int TSize;
int VBegin;
int TBegin;
int* VOffset;
int* TOffset;

void InitRootInterCodeList()
{
    InterCodeEntry *ICVhead, *ICVtail;
    ICVhead = RootInterCodeList->head;
    ICVtail = ICVhead->prev;

    ICVhead->prev = NULL;
    ICVtail->next = NULL;
}

void GetVTSize()
{
    TSize = TIndex;
    VSize = 0;
    ICVarEntry* ICV;
    for(ICV = RootICVarTable->head; ICV != NULL; ICV = ICV->next)
    {
        Type* TP = ICV->VariableType;
        if(TP->kind == BASIC)VSize++;
        else if(TP->kind == ARRAY)
        {
            assert(TP->array.dim == 1);
            VSize = VSize + TP->array.DimSize[0];
        }
        else assert(0);
    }

    VOffset = (int*)malloc((unsigned)4*VIndex);
    TOffset = (int*)malloc((unsigned)4*TIndex);

    int i;
    int offset = 0;
    VOffset[0] = 0;
    for(ICV = RootICVarTable->head; ICV->next != NULL; ICV = ICV->next)
    {
        ICVarEntry* ICVnxt = ICV->next;
        Type* TP = ICV->VariableType;
        if(TP->kind == BASIC)
        {
            offset++;
            VOffset[ICVnxt->VIndex] = offset;
        }
        else if(TP->kind == ARRAY)
        {
            assert(TP->array.dim == 1);
            offset = offset + TP->array.DimSize[0];
            VOffset[ICVnxt->VIndex] = offset;
        }
        else assert(0);
    }

    offset = 0;
    for(i = 0; i<TIndex; i++)
    {
        TOffset[i] = offset;
        offset++;
    }


}

void MachineCodePreparation(FILE* stream)
{
    fprintf(stream,
            ".data\n"
            "_prompt: .asciiz \"Enter an integer:\"\n"
            "_ret: .asciiz \"\\n\"\n"
            ".globl main\n"
            ".text\n"
            "read:\n"
            "  li $v0, 4\n"
            "  la $a0, _prompt\n"
            "  syscall\n"
            "  li $v0, 5\n"
            "  syscall\n"
            "  jr $ra\n\n"
            "write:\n"
            "  li $v0, 1\n"
            "  syscall\n"
            "  li $v0, 4\n"
            "  la $a0, _ret\n"
            "  syscall\n"
            "  move $v0, $0\n"
            "  jr $ra\n\n");
}

void FUNGenerator(InterCode* IC, FILE* stream)
{
    fprintf(stream, "%s:\n", IC->FUN.funName);

    if(strcmp(IC->FUN.funName, "main") == 0)
    {
        int frameSize = (1 + VSize + TSize) * 4;
        fprintf(stream, "  subu $sp, $sp, %d\n", frameSize );
        fprintf(stream, "  sw $fp, (%d - 4)($sp)\n", frameSize);
        fprintf(stream, "  addi $fp, $sp, %d\n", frameSize);


        /* in main function:
         *
         *         --------------  <- $fp
         *         |   old fp   |
         *         --------------  <- $fp + VBegin
         *         |            |
         *         |   V data   |
         *         |            |
         *         --------------  <- $fp + TBegin
         *         |            |
         *         |   T data   |
         *         |            |
         *         --------------
         */

        VBegin = 4;                 // v_i is at ($fp + VBegin + VOffset[i]*4) in stack
        TBegin = VBegin + VSize*4;  // t_i is at ($fp + TBegin + TOffset[i]*4) in stack

    }
    else{
        assert(0);
    }
}

void MachineCodeGenerator(char* filename)
{
    FILE* fp;

    if(filename == NULL)
    {
        fp = stdout;
    }
    else
    {
        fp = fopen(filename, "w");
        assert(fp != NULL);
    }

    MachineCodePreparation(fp);


    InterCodeEntry* ICV ;
    for (ICV = RootInterCodeList->head;  ICV->next!=NULL ; ICV = ICV->next)
    {
        InterCode* IC = ICV->IC;
        switch (IC->kind)
        {
            case IFUNCTION: FUNGenerator(IC, fp);break;
            case IASSIGN:
            default:assert(0);
        }
    }

}
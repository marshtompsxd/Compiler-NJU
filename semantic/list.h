#ifndef __LIST_H__
#define __LIST_H__

#include "symbol_table.h"
#include <stdlib.h>

FieldList* FLTail(FieldList* FL)
{
	while(FL->tail!=NULL)
	{
		FL = FL->tail;
	}
	return FL;
}

void InsertItemIntoSymbolTable(SymbolTableEntry* item, SymbolTableHead* table)
{
	/* you can choose to insert at head but I don't like it...
	item->tail = table->head;
	table->head = item;
	*/

	/*I prefer to insert at tail even though it is slower...
	*/
	if(table->head == NULL)
	{
		item->tail = NULL;
		table->head = item;
	}
	else
	{
		SymbolTableEntry* SE;
		for(SE = table->head; SE->tail != NULL; SE = SE->tail);
		SE->tail = item;
		item->tail = NULL;
	}
}

void InsertItemIntoStructTypeTable(StructTypeTableEntry* item, StructTypeTableHead* table)
{
	/* you can choose to insert at head but I don't like it...
	item->tail = table->head;
	table->head = item;
	*/

	/*I prefer to insert at tail even though it is slower...
	*/
	if(table->head == NULL)
	{
		item->tail = NULL;
		table->head = item;
	}
	else
	{
		StructTypeTableEntry* STE;
		for(STE = table->head; STE->tail != NULL; STE = STE->tail);
		STE->tail = item;
		item->tail = NULL;
	}
}


Type* GetStructTypeFromStructTypeTable(char* structname, StructTypeTableHead* table)
{
	StructTypeTableEntry* STE;
	for(STE = table->head; STE != NULL; STE = STE->tail)
	{
		if(strcmp(structname, STE->TP->structure.structname)==0)
		{
			return STE->TP;			
		}
	}
	return NULL;
}

Type* GetStructType(char* structname)
{
	int idx = struct_top;
	Type* type;
	if( (type = GetStructTypeFromStructTypeTable(structname, CurrentStructTypeTable)) != NULL)
	{
		return type;
	}
	while(idx >= 0)
	{
		if((type = GetStructTypeFromStructTypeTable(structname, StructTypeTableStack[idx])) != NULL)
			return type;
		idx--;
	}
	return NULL;
}

void PushPrevTable()
{
	sym_top++;
	struct_top++;
	SymbolTableStack[sym_top] = CurrentSymbolTable;
	StructTypeTableStack[struct_top] = CurrentStructTypeTable;

	CurrentSymbolTable = (SymbolTableHead*)malloc(sizeof(SymbolTableHead));
	CurrentSymbolTable->head = NULL;
	CurrentStructTypeTable = (StructTypeTableHead*)malloc(sizeof(StructTypeTableHead));
	CurrentStructTypeTable->head = NULL;

}

void PopPrevTable()
{
	free(CurrentSymbolTable);
	free(CurrentStructTypeTable);
	CurrentSymbolTable = SymbolTableStack[sym_top];
	CurrentStructTypeTable = StructTypeTableStack[struct_top];
	sym_top--;
	struct_top--;
}

#endif
/*Copyright (C) 
 * 2018 - eda1 dot fiunam at yahoo dot com dot mx
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 * 
 */

/**
 * @file DLL.h
 * @brief TDU para una lista doblemente enlazada de enteros (versión reducida)
 * @author eda1 dot fiunam at yahoo dot com dot mx
 * @version 0.1
 * @date 29/ago/19
 */


#ifndef  DLL_INC
#define  DLL_INC

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

//#include "City.h"

typedef void* Item;

typedef struct Node
{
	Item info;

	struct Node* next;
	struct Node* prev;
} Node;

typedef struct DLL
{
	Node*  first;
	Node*  last;
	Node*  cursor;
	size_t len;
} DLL;


DLL*   DLL_New();
void   DLL_Delete(      DLL* this );
bool   DLL_InsertBack(  DLL* this, Item value );
bool   DLL_RemoveFront( DLL* this, Item* value );
bool   DLL_RemoveNode(  DLL* this, Item value);
bool   DLL_Peek(        DLL* this, Item* value );
bool   DLL_IsEmpty (    DLL* this);
bool   DLL_IsOnList  (  DLL* this, Item value );
void   DLL_Purge(       DLL* this );
size_t DLL_Len(         DLL* this );
void   DLL_GetInformation( DLL* this, void* ptrArr[] );

#endif   /* ----- #ifndef DLL_INC  ----- */

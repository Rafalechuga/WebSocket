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


#include "DLL.h"


/*-------------------------------------------------------------------
 *  funciones privadas!!
 *-----------------------------------------------------------------*/

static Node* newNode( Item value )
{
	Node* n = ( Node* ) malloc( sizeof ( Node ) );
	if( NULL != n ) {
		n->info = value;
		n->next = NULL;
		n->prev = NULL;
	}

	return n;
}

Node* findNode (  DLL* this, Item value ){
	assert( this );
	if( DLL_IsEmpty( this ) ) { return NULL; }	
	Node* tmp = this->first;
	for( size_t i = 0; i < DLL_Len( this ); ++i ){
		if( value == tmp->info ){
			return tmp;
		}
		tmp = tmp->next;
	}
	return NULL;
}

/*-------------------------------------------------------------------
 *  Funciones públicas (operaciones) !!
 *-----------------------------------------------------------------*/

/**
 * @brief Crea una nueva lista
 *
 * @return Referencia a la nueva lista; NULL en caso de error
 */
DLL* DLL_New()
{
	DLL* p = ( DLL* ) malloc( sizeof( DLL ) );
	if( NULL != p ) {
		p->first = NULL;
		p->last = NULL;
		p->len = 0;
	}

	return p;
}

/**
 * @brief Destruye una lista
 *
 * @param this Referencia al objeto que se quiere destruir
 */
void DLL_Delete( DLL* this )
{
	assert( this );

	while( this->first != NULL ) {
		Node* tmp = this->first->next;
		free( this->first );
		this->first = tmp;

		this->last->next = this->first;
		// tal vez no se necesita
	}

	free( this );
	this = NULL;
}

bool DLL_InsertBack( DLL* this, Item value )
{
	assert (this);

	Node* n = newNode( value );
	if( n == NULL ) { return false;	}

	if( this->first == NULL ){
		this->first = n;
		this->last = n;
	}
	else {
		n->prev = this->last;
		this->last->next = n;
		this->last = n;
	}

	++this->len;

	return true;
}


bool DLL_RemoveFront( DLL* this, Item* value )
{
	assert( this );

	if( NULL == this->first ) return false;
	// lista vacía

	*value = this->first->info;
	// guardamos los datos antes de borrar al nodo

	if( this->first == this->last ){
		free( this->first );
		this->first = NULL;
		this->last = NULL;
	}
	else{
		Node* tmp = this->first->next;
		free( this->first );
		this->first = tmp;
		this->first->prev = NULL;
	}
	--this->len;

	return true;
}

bool   DLL_IsOnList  (  DLL* this, Item value ){
	assert( this );
	if( DLL_IsEmpty( this ) ) { return false ; }	
	Node* tmp = this->first;
	for( size_t i = 0; i < DLL_Len( this ); ++i ){
		if( value == tmp->info )
			return true;
		tmp = tmp->next;
	}
	return false;
}

bool DLL_RemoveNode(  DLL* this, Item value)
{
	assert( this );
	if( DLL_IsOnList( this, value ) ){
		Node* n = findNode( this, value );

		if( n != NULL ){
			Node* tmp1 = n->prev; 
			Node* tmp2 = n->next;

			free( n );

			if( tmp1 != NULL )
				tmp1->next = tmp2;

			if( tmp2 != NULL )
				tmp2->prev = tmp1;

			--this->len;

			return true;
		}
	}
	return false;
}

/**
 * @brief Indica si una lista está vacía o no
 *
 * @param this Referencia a un objeto tipo DLL
 *
 * @return true si la lista está vacía; false en caso contrario
 */
bool DLL_IsEmpty (DLL* this)
{
	assert( this );

	return this->first == NULL ? true : false;
}

/**
 * @brief Purga (limpia) una lista. 
 * Esta función no elimina la lista. Si lo que se desea es eliminarla,
 * entonces use a la función \see DLL_Delete()
 *
 * @param this Referencia a un objeto tipo DLL
 */
void DLL_Purge( DLL* this )
{
	assert( this );

	if( DLL_IsEmpty( this ) ) { return; }

	while( this->first != NULL ){
		Node* tmp = this->first->next;
		free( this->first );
		this->first = tmp;
	}

	this->len = 0;
}

size_t DLL_Len( DLL* this )
{
	return this->len;
}

bool DLL_Peek( DLL* this, Item* value )
{
	assert( this );

	if( NULL == this->first ) return false;
	// lista vacía

	*value = this->first->info;
	return true;
}


/*
*	@brief Guarda la direccion de los objetos en un arreglo.
*	@param this Referencia a la lista.
*	@param ptrArr Arreglo donde se guardaran las direcciones.
*/
void DLL_GetInformation( DLL* this, void* ptrArr[] ){
	assert( this );
	if( DLL_IsEmpty( this ) ) { return; }	
	Node* tmp = this->first;
	for( size_t i = 0; i < DLL_Len( this ); ++i ){
		ptrArr[ i ] = tmp->info;
		tmp = tmp->next;
	}
}

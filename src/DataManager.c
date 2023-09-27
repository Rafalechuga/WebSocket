#include "DataManager.h"

/**************************************************
				MÉTODOS PRIVADOS
**************************************************/

/**
*	@brief Guarda la lista de ciudades en una base de datos SQL.
*	@param this Referecia a un objeto DataManager.
*	@return true Si se tuvo éxito al guardar.
*	@return false Si falló el guardado.
*/
bool save_Data( DataManager* this ){
	return DB_Save_Information( this->dataBase, this->cities, this->axis /*Redefinir si es necesario*/ );
}

/**
*	@brief Carga ciudades guardadas en una base de datos SQL.
*	@param this Referencia a un objeto DataManager.
*	@return true Si se recupero con éxito la información.
*	@return false Si falló la recuperación.
*/
bool recover_Data( DataManager* this ){
	return DB_Recover_Information( this->dataBase, this->cities, this->axis );
}

/**
*	@brief Asigna la lista de vecinos de una tipo City a su respectivo tipo Axis.
*	@param this Referencia al objeto DataManager.
*/
void axis_Asigment( DataManager* this, City* c1, City* c2, size_t weight ){
	Axis* a = Axis_New( c1, c2, weight);
	DLL_InsertBack( this->axis, a );
}

/**************************************************
				MÉTODOS PÚBLICOS
**************************************************/


/**
*	@brief Constructor del objeto DataManager.
*	@return dm Referencia a el objeto DataManager.
*/
DataManager* DataManager_New()
{
	DataManager* dm = ( DataManager* )malloc( sizeof( DataManager ) );

	if( dm->students == NULL )
		dm ->students = DLL_New();

	return dm;
}

/**
*	@brief Destructor del objeto DataManager, Salvar los datos aquí
*	de destruir al objeto.
*	@param this Referencia a un objeto DataManager.
*/
void DataManager_Delete( DataManager* this )
{
	assert( this );

	//save_Data( this );

	size_t lenAxis = DLL_Len( this->axis );
	void* ptrAxis[ lenAxis ];

	DLL_GetInformation( this->axis, ptrAxis );

	for( size_t i = 0; i < lenAxis; ++i )
		Axis_Delete( ( Axis* )ptrAxis[ i ] );


	size_t len = DLL_Len( this->cities );
	void* ptrArr[ len ];

#if 1

	DLL_GetInformation( this->cities , ptrArr );

	for( size_t i = 0; i < len ; i++ )
		City_Delete( ( City* )ptrArr[ i ] );

	DataBase_Delete(  this->dataBase );

	free( this );

#endif
}
/**
*	@brief Carga información previa de una DB.
*	@param this Referencia a un objeto DataManager.
*/
void DM_LoadInformation( DataManager* this ){ recover_Data( this ); }


/**
*	@brief Guarda la lista de direcciones de los vértices City.
*	@param this Referencia al objeto DataManager.
*	@param ptrArr Referencia a la lista donde se guardaran direcciones,
*	debe tener el tamagno de numero de ciudades en DLL cities. Usar método
*	DLL_Len() 	
*/
void DM_Get_CitiesList( DataManager* this, void* ptrArr[] ){ DLL_GetInformation( this->cities, ptrArr ); }

/**
*	@brief Imprime la lista de ciudades hasta el momento almacenadas en la DLL
*	cities.
*	@param this Referencia al objeto DataManager.
*/
void DM_Print_CitiesList( DataManager* this ){
	size_t dllSize = DLL_Len( this->cities ); 

	void* ptrArr[ dllSize ];
	DM_Get_CitiesList( this, ptrArr );

	for( size_t i = 0; i < dllSize; i++ ){
		CT_Print( ( City* )ptrArr[ i ] );	
	}
}


/**
*	@brief Agega un eje con direccion a la ciudad con name1 a la ciudad
*	con nombre name2, el metodo valida que las ciudades esten en la lista.
*	@param this Referencia a un objeto DataManager.
* 	@param name1 Nombre de la primer ciudad.
*	@param name2 Nombre de la segunda ciudad.
*	@return true Si se añadio con éxito.
*	@return false Si falló o no se encontraron las ciudades.
*/
bool DM_Add_City( DataManager* this, char name[] ){
	City* c = City_New( name );
	return DLL_InsertBack( this->cities, c );
}

/**
*	@brief Busca una ciudad en la DLL cities por su nombre.
*	@param name Nombre de la ciudad a buscar.
*	@param direction Apuntador a ciudad donde se guardara coincidencia de búsqueda
*	@return Referencia a una ciudad si la encontro, NULL en caso contrario.
*/
City* DM_Find_City( DataManager* this, char name[] ){
	size_t cLen = DLL_Len( this->cities );
	void* cList[ cLen ];

	DM_Get_CitiesList( this, cList );

	City* c = NULL;

	for( size_t i = 0; i < cLen; ++i ){
		c = ( City* )cList[ i ];
		if( strcmp( c->name, name ) == 0  )
			return c;
	}
	return c;
}



#include "DataManager.h"



/**************************************************
				MÉTODOS PRIVADOS
**************************************************/

/**
*	@brief Guarda la lista de alumnos.
*	@param this Referecia a un objeto DataManager.
*	@return true Si se tuvo éxito al guardar.
*	@return false Si falló el guardado.
*/
bool save_Data( DataManager* this ){
	
}

/**
*	@brief Carga ciudades guardadas en un TXT
*	@param this Referencia a un objeto DataManager.
*	@return true Si se recupero con éxito la información.
*	@return false Si falló la recuperación.
*/
bool recover_Data( DataManager* this ){
	
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

	///////////////////////////////////////////////
	// 		CARGAR TXT Y OBTENER ULTIMO ID 		///
	///////////////////////////////////////////////
	dm->lastStudentID = 0;


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

	///////////////////////////////////////////////
	// 		Salvar información			 		///
	///////////////////////////////////////////////

	size_t lenStudents = DLL_Len( this->students );
	void* ptrStudents[ lenStudents ];

	DLL_GetInformation( this->students, ptrStudents );

	for( size_t i = 0; i < lenStudents; ++i )
		Student_Delete( ( Student* )ptrStudents[ i ] );
}

/**
*	@brief Imprime la lista de estudiantes hasta el momento almacenadas en la DLL
*	@param this Referencia al objeto DataManager.
*/
void DM_Print_StudentsList( DataManager* this ){
	size_t dllSize = DLL_Len( this->students ); 

	void* ptrArr[ dllSize ];
	DM_Get_StudentesList( this, ptrArr );

	for( size_t i = 0; i < dllSize; i++ ){
		ST_Print( ( Student* )ptrArr[ i ] );	
	}
}

/**
*	@brief Agega un un objeto de tipo estudiante
*	con nombre name2, el metodo valida que las ciudades esten en la lista.
*	@param this Referencia a un objeto DataManager.
* 	@param id Id del estudiente.
* 	@param name Nombre del estudiante
*	@param lastName Apellido del estudiante
* 	@param semester Semestre lectivo
* 	@param program Carrera del estudiante.
*	@return true Si se añadio con éxito.
*	@return false Si falló o no se encontraron las ciudades.
*/
bool DM_Add_Student( DataManager* this, char name[], char lastName[], int semester, char program[]  ){
	this->lastStudentID++;
	Student* s = Student_New( this->lastStudentID, name, lastName, semester, program );
	return DLL_InsertBack( this->students, s );
}

/**
*	@brief Guarda la lista de direcciones de los estudiantes
*	@param this Referencia al objeto DataManager.
*	@param ptrArr Referencia a la lista donde se guardaran direcciones,
*	debe tener el tamagno de numero de ciudades en DLL Students. Usar método
*	DLL_Len() 	
*/
void DM_Get_StudentesList( DataManager* this, void* ptrArr[] ){ DLL_GetInformation( this->students, ptrArr ); }

#if 0
/**
*	@brief Carga información previa de una DB.
*	@param this Referencia a un objeto DataManager.
*/
void DM_LoadInformation( DataManager* this ){ recover_Data( this ); }

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

#endif


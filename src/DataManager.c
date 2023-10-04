#include "DataManager.h"


/**
*	@brief Guarda la lista de alumnos.
*	@param this Referecia a un objeto DataManager.
*	@return true Si se tuvo éxito al guardar.
*	@return false Si falló el guardado.
*/
bool save_Data( DataManager* this ){
	const char *nombreArchivo = "alumno.txt";
	if (remove(nombreArchivo) == 0) {
        printf("Archivo borrado%s.\n", nombreArchivo);
    } else {
        printf("No se pudo borrar el archivo %s.\n", nombreArchivo);
    }

	size_t dllSize = DLL_Len( this->students ); 
	void* ptrArr[ dllSize ];
	DM_Get_StudentesList( this, ptrArr );

    

    // Abre el archivo en modo append
    FILE *archivo = fopen(nombreArchivo, "a");

    // Verifica si el archivo se abrió correctamente
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    fprintf(archivo, "%s\n", "ID, Nombre, Apellido, Semestre, Carrera");
    // Guardar cada alumno
    for( size_t i = 0; i < dllSize; i++ ){
    	char tmpChain[ 256 ];
		ST_To_String( ( Student* )ptrArr[ i ], tmpChain, 256 );
		fprintf(archivo, "%s\n", tmpChain);	
	}
    
    fclose(archivo);
}

/**
*	@brief Carga ciudades guardadas en un TXT
*	@param this Referencia a un objeto DataManager.
*	@return true Si se recupero con éxito la información.
*	@return false Si falló la recuperación.
*/
bool recover_Data( DataManager* this ){

    const char *nombreArchivo = "alumno.txt";

    FILE *archivo = fopen(nombreArchivo, "r");

    // Verifica si el archivo se abrió correctamente
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo %s.\n", nombreArchivo);
        return 1;
    }

    // Variables para almacenar la línea leída y los tokens
    char linea[256];
    char *token;

    //Leer cabecera del archivo e ignorar
    fgets(linea, sizeof(linea), archivo);

    // Lee cada línea del archivo
    while (fgets(linea, sizeof(linea), archivo) != NULL) {

    	// Elimina el salto de línea ('\n') si está presente en la línea
        char *posicionSaltoLinea = strchr(linea, '\n');
        if (posicionSaltoLinea != NULL) {
            *posicionSaltoLinea = '\0';  // Reemplaza '\n' con '\0' (fin de cadena)
        }

        // Tokeniza la línea usando la coma como delimitador
        token = strtok(linea, ",");

		char name[ 32 ];
		char lastName[ 32 ];
		int semester;
		char program[ 32 ];

		for (int i = 0; i < 5; ++i)
		{	
			if( i == 0 ) if( this->lastStudentID < atoi(token) )  this->lastStudentID = atoi(token);
			if( i == 1 ) strcpy( name, token);
			if( i == 2 ) strcpy( lastName, token );
			if( i == 3 ) semester = atoi(token);
			if( i == 4 ) strcpy( program, token );

			token = strtok(NULL, ",");
		}

		DM_Load_Student( this, name, lastName, semester, program );
    }

    // Cierra el archivo
    fclose(archivo);

    return 0;
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

	dm->lastStudentID = 0;
	dm->selectF = false;
	dm->insertF = false;
	dm->updateF = false;

	dm->sendF = false;
	dm->deleteF = false;

	if( dm->students == NULL )
		dm ->students = DLL_New();

	// Recuperar Informacion
	recover_Data( dm );

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

	// SALVAR INFORMACIÓN!
	save_Data( this );

	size_t lenStudents = DLL_Len( this->students );
	void* ptrStudents[ lenStudents ];

	DLL_GetInformation( this->students, ptrStudents );

	for( size_t i = 0; i < lenStudents; ++i )
		Student_Delete( ( Student* )ptrStudents[ i ] );
}

/**
 * 	@brief Limpia la lista de alumnos
 * 	@param this referencia al objeto DataManager 
 */
void DM_Purge( DataManager* this )
{
	if( this->students == NULL )
		this ->students = DLL_New();
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
*	@param this Referencia a un objeto DataManager.
* 	@param id Id del estudiente.
* 	@param name Nombre del estudiante
*	@param lastName Apellido del estudiante
* 	@param semester Semestre lectivo
* 	@param program Carrera del estudiante.
*	@return true Si se añadio con éxito.
*	@return false Si falló o no se encontraron las ciudades.
*/
bool DM_Load_Student( DataManager* this, char name[], char lastName[], int semester, char program[]  ){
	Student* s = Student_New( this->lastStudentID, name, lastName, semester, program );
	return DLL_InsertBack( this->students, s );
}

/**
*	@brief Agega un un objeto de tipo estudiante
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

/**
*	@brief Busca una ciudad en la DLL students por su ID
*	@param id ID del alumno a buscar.
*	@param direction Apuntador a ciudad donde se guardara coincidencia de búsqueda
*	@return Referencia a objeto student si la encontro, NULL en caso contrario.
*/
Student* DM_Find_Student( DataManager* this, int id ){
	size_t sLen = DLL_Len( this->students );
	void* sList[ sLen ];

	DM_Get_StudentesList( this, sList );

	Student* s = NULL;

	for( size_t i = 0; i < sLen; ++i ){
		s = ( Student* )sList[ i ];
		if( s->id == id  )
			return s;
	}

	ST_Print( s );
	return s;
}

/**
*	@brief Edita un registro alumno en su apellid
* 	@param this Referencia de un objeto Data Manager
*  	@param id Parametro de busqueda para modificar
*/
void DM_Update_Student_LastName( DataManager* this, int id, char newLastName[] )
{
	Student* s = DM_Find_Student( this, id );
	if( s == NULL ){ printf("Sin coincidencia de busqueda\n"); }
	else ST_Set_LastName( s , newLastName );
}

/**
*	@brief Borra un registro de alumno
* 	@param this Referencia de un objeto Data Manager
*  	@param id Parametro de busqueda para borrar
*/
void DM_Delete_Student( DataManager* this, int id )
{
	Student* s = DM_Find_Student( this, id );
	if( s == NULL ){ printf("Sin coincidencia de busqueda\n"); }
	else
	{ 
		DLL_RemoveNode(  this->students, s ); 
	}

}

void DM_Tokenize_Data( DataManager* this, char chain[] )
{
	// Copiar la cadena en una variable modificable
    char copiaCadena[256]; // Tamaño suficientemente grande para contener la cadena
    strcpy(copiaCadena, chain);

    // Elimina el salto de línea ('\n') si está presente en la línea
    char *posicionSaltoLinea = strchr(copiaCadena, '\n');
    if (posicionSaltoLinea != NULL) 
    {
        *posicionSaltoLinea = '\0';  // Reemplaza '\n' con '\0' (fin de cadena)
    }

    

    // Tokenizar la cadena usando el espacio en blanco como delimitador
    char *token = strtok(copiaCadena, " ");
    int tmpID;
	char tmpName[ 32 ];
	char tmpLastName[ 32 ];
	int  tmpSemester;
	char tmpProgram[ 32 ];

	size_t i = 0;

    while (token != NULL) 
    {
    	// Elimina espacios en blanco (' ') si está presente en la línea
	    posicionSaltoLinea = strchr(token, ' ');
	    if (posicionSaltoLinea != NULL) 
	    {
	        *posicionSaltoLinea = '\0';  // Reemplaza '\n' con '' 
	    }
	    // Elimina apertura parentesis ('(') si está presente en la línea
	    posicionSaltoLinea = strchr(token, '(');
	    if (posicionSaltoLinea != NULL) 
	    {
	        *posicionSaltoLinea = '\0';  // Reemplaza '\n' con '' 
	    }
	    // Elimina cerradura parentesis (')') si está presente en la línea
	    posicionSaltoLinea = strchr(token, ')');
	    if (posicionSaltoLinea != NULL) 
	    {
	        *posicionSaltoLinea = '\0';  // Reemplaza '\n' con '' 
	    }
	    // Elimina coma parentesis (',') si está presente en la línea
	    posicionSaltoLinea = strchr(token, ',');
	    if (posicionSaltoLinea != NULL) 
	    {
	        *posicionSaltoLinea = '\0';  // Reemplaza '\n' con '' 
	    }

        if( strcmp( token, "SELECT" ) == 0 ) 
        {
        	this->selectF = true;
			this->insertF = false;
			this->updateF = false;
			this->deleteF = false;
        }else if( strcmp( token, "INSERT") == 0 ) 
        {
        	this->selectF = false;
			this->insertF = true;
			this->updateF = false;
			this->deleteF = false;
        }else if( strcmp( token, "UPDATE" ) == 0 ) 
        {
        	this->selectF = false;
			this->insertF = false;
			this->updateF = true;
			this->deleteF = false;
        }else if( strcmp( token, "DELETE" ) == 0 ) 
        {
        	this->selectF = false;
			this->insertF = false;
			this->updateF = false;
			this->deleteF = true;
        }else if( strcmp( token, "SALIR" ) == 0 )
        {
        	DataManager_Delete( this );
        	abort();
        }
       	
        ///////// SELECT
       	if( this->selectF && i == 0)
       	{	
       		memset( this->sendChain, 0, sizeof( this->sendChain ));
       		size_t lenStudents = DLL_Len( this->students );
			void* ptrStudents[ lenStudents ];

			DLL_GetInformation( this->students, ptrStudents );

			for( size_t i = 0; i < lenStudents; ++i )
			{
				char str[512];
				printf("CONCAT: ");
				ST_Print( ( Student* )ptrStudents[ i ] );
				ST_To_String( ( Student* )ptrStudents[ i ], str, 512 );
				strcat( this->sendChain, str );
				strcat( this->sendChain, "\n" );
			}

			this->sendF = true;
       	}

       	///////// INSERT
        if( this->insertF )
        {
        	memset( this->sendChain, 0, sizeof( this->sendChain ));
        	if( i == 5 ) strcpy( tmpName, token );
        	if( i == 6 ) strcpy( tmpLastName, token );
        	if( i == 7 ) tmpSemester = atoi( token );
        	if( i == 8 ) 
        	{
        		strcpy( tmpProgram, token );
        		DM_Add_Student( this, tmpName, tmpLastName, tmpSemester, tmpProgram );
        		save_Data( this );
        		strcat( this->sendChain, "Elemento Insertado" );
        	}
        }

        ///////// UPDATE
        if( this->updateF )
        {
        	memset( this->sendChain, 0, sizeof( this->sendChain ));
        	if( i == 5 ) strcpy( tmpLastName, token );
        	if( i == 9 ) 
        	{
        		tmpID = atoi( token );
        		DM_Update_Student_LastName( this, tmpID , tmpLastName );
        		save_Data( this );
        		strcat( this->sendChain, "Elemento Actualizado" );
        	}

        	
        }

		///////// DELETE
		if( this->deleteF )
		{
			memset( this->sendChain, 0, sizeof( this->sendChain ));
			if( i == 6 ) 
			{
				tmpID = atoi( token );
				DM_Delete_Student( this, tmpID );
				strcat( this->sendChain, "Elemento Eliminado" );
				save_Data( this );
			}
			
		}

        i++;
       	token = strtok(NULL, " ");
    }
}



#if 0

/**
*	@brief Carga información previa de una DB.
*	@param this Referencia a un objeto DataManager.
*/
void DM_LoadInformation( DataManager* this ){ recover_Data( this ); }



#endif


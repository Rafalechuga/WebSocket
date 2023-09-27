#include "Student.h"

/**
*	@brief Crea un objeto tipo Student
*	@return Referencia a un nuevo .
*/
Student* Student_New( int id, char name[], char fatherLastName[], char motherLastName[], int semester, char program[] ){
	Student* s = ( Student* ) malloc( sizeof( Student ) );

	s->id = id;
	strcpy( s->name, name );
	strcpy( s->fatherLastName, fatherLastName );
	strcpy( s->motherLastName, motherLastName );
	s->semester = semester;
	strcpy( s->program, program );
	return s;
}

/**
*	@brief Destructor del objeto Student.
*	@param this Referencia al objeto a destruir.
*/
void Student_Delete( Student* this ){
	assert( this );
	free( this );
}

/**
*	@brief Convierte un objeto a cadena de texto.
*	@param this Referencia del estudiante  a convertir.
*	@param chain Arreglo donde se guardara el formato de texto.
*	@param len Tamano de la cadena.
*/
void ST_To_String( Student* this, char chain[], size_t len ){
	snprintf( chain, len - 1,
		"%d, %s, %s, %s, %d, %s",
		this->id,
		this->name,
		this->fatherLastName,
		this->motherLastName,
		this->semester,
		this->program
	);
}

/**
*	@brief Imprime en consola un objeto Student.
*	@param this referencia al estudiante a imprir.
*/
void ST_Print( Student* this ){ 
	char str[512];
	ST_To_String( this, str, 512 );
	printf( "%s\n", str ); 
}
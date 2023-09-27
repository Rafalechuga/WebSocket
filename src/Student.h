#ifndef  Student_INC
#define  Student_INC

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "DLL.h"



typedef struct Student
{
	int  id;
	char name[ 32 ];
	char fatherLastName[ 32 ];
	char motherLastName[ 32 ];
	int semester;
	char program[ 32 ];
}Student;

Student* Student_New( int id, char name[], char fatherLastName[], char motherLastName[], int semester, char program[] );
void Student_Delete( Student* this );
void ST_To_String( Student* this, char chain[], size_t len );
void ST_Print( Student* this );

#endif   /* ----- #ifndef Student_INC  ----- */
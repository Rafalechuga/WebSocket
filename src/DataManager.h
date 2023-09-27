#ifndef  DataManager_INC
#define  DataManager_INC

#include <assert.h>
#include <string.h>

#include "DLL.h"
#include "Student.h"
//#include "DataBase.h"


// SELECT 	-> DM_Print_StudentsList
// INSERT 	-> DM_Add_Student
// UPDATE 	-> 
// DELETE 	-> DM_Delete_Student

typedef struct DataManager
{
	DLL* students;
	//DataBase* dataBase;
	size_t lastStudentID;
} DataManager;

DataManager* DataManager_New();

void DataManager_Delete( DataManager* this );
void DM_Print_StudentsList( DataManager* this );
void DM_Get_StudentesList( DataManager* this, void* ptrArr[] );
bool DM_Add_Student( DataManager* this, char name[], char lastName[], int semester, char program[] );
Student* DM_Find_Student( DataManager* this, int id );
void DM_Update_Student_LastName( DataManager* this, int id, char newLastName[] );
void DM_Delete_Student( DataManager* this, int id );


#if 0

void DM_LoadInformation( DataManager* this );


bool DM_Add_CityAxis( DataManager* this, char name1[], char name2[], size_t weight );

City* DM_Find_City( DataManager* this, char name[] );


void DM_Print_CitiesList( DataManager* this );

#endif


#endif   /* ----- #ifndef DataManager_INC  ----- */
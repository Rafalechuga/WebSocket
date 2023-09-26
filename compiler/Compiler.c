#include <stdio.h>
#include <string.h>


void updateFile( ){
	FILE* handler; 
	handler = fopen( "./fonts/H_Files.txt", "r"  );
	if( handler == NULL ) { 
		printf( "Error al abrir archivo\n" ); 
		return;
	}
	
	char newText[ 1024 ] = "";	
	while( !feof( handler ) ){
		char text [ 126 ];
		fgets( text, 126, handler );
		char chain[256];

		size_t len = strlen( text );

		text[ len - 1 ] = '\0';

		snprintf( chain, 255, "-I %s/\n", text );

		strcat( newText, chain );
	}

	fclose( handler );

	handler = fopen( "./fonts/H_Files.txt", "w"  );

	fputs( newText, handler );

	fclose( handler );

	
}

#define STR_LEN 256

int main(){
	
	updateFile( );
	return 0;
}




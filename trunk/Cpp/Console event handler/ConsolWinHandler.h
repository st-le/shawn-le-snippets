#ifndef __CONSOLEWINHANDLER_H__
#define __CONSOLEWINHANDLER_H__

#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>

extern int escape;

BOOL WINAPI ConsoleHandler(DWORD CEvent)
{
	char mesg[128];

	switch(CEvent)
	{
	case CTRL_C_EVENT:
		Beep( 750, 300 ); 
		escape = 1;
		MessageBox(NULL,
			"CTRL+C received!","CEvent",MB_OK);
		break;
	case CTRL_BREAK_EVENT:
		//MessageBox(NULL,
		//	"CTRL+BREAK received!","CEvent",MB_OK);
		break;
	case CTRL_CLOSE_EVENT:
		escape = 1;
		//MessageBox(NULL,
		//	"Program being closed!","CEvent",MB_OK);
		break;
	case CTRL_LOGOFF_EVENT:
		MessageBox(NULL,
			"User is logging off!","CEvent",MB_OK);
		break;
	case CTRL_SHUTDOWN_EVENT:
		MessageBox(NULL,
			"User is logging off!","CEvent",MB_OK);
		break;

	}
	return FALSE;  // TRUE: process terminated; FALSE: process passed to next handler or if no else process is terminated
}


int setWinCloseHandler()
{
	int ret = 0;
	
	if (SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleHandler,TRUE)==FALSE)
		{
			// unable to install handler... 
			// display message to the user
			printf("Unable to install handler!\n");
			return -1;
		}
		
	return ret;
}


#endif
#define _WIN32_WINNT_WINTHRESHOLD  0x0A00 // Windows 10 
#define _WIN32_WINNT_WIN10         0x0A00 // Windows 10  


#include <windows.h>
#include <stdio.h>
#include <comutil.h>
#include "stdafx.h"
#include "windows.h"
#include <fstream>
#include <stdio.h>  
#include <ole2.h>  
#include <conio.h>  
#include <stdlib.h>  
#include <iostream>
#include "stdafx.h"
#include <fstream>
#include <string>
#pragma warning(disable : 4996) //отключение ошибки _CRT_SECURE_NO_WARNINGS

using namespace std;




#import "msado15.dll"  no_namespace rename("EOF", "EndOfFile")

inline void TESTHR(HRESULT x) { if FAILED(x) _com_issue_error(x); };
SERVICE_STATUS ServiceStatus;
SERVICE_STATUS_HANDLE ServiceStatusHandle;

void WINAPI ServiceMain(DWORD argc, LPTSTR *argv);
DWORD ServiceInitialization(DWORD argc, LPTSTR *argv, DWORD *specificError);
void WINAPI ServiceCtrlHandler(DWORD opcode);



int main(int argc, char* argv[])
{
	ofstream(myfile);
	
	
	
	char text[] = "MyService";
	wchar_t wtext[20];
	mbstowcs(wtext, text, strlen(text) + 1);//Plus null
	LPWSTR ptr = wtext;
	
	//ofstream(myfile);
	//myfile.open("D:/New folder/Readerr4.txt");// создаём объект класса ofstream для записи и связываем его с файлом rerer.txt в папке Debug
	//myfile << "Open";
	//myfile.close();
	ofstream(myfile);
	SERVICE_TABLE_ENTRY DispatchTable[] = { { ptr, ServiceMain },{ NULL, NULL } };
	if (!StartServiceCtrlDispatcher(DispatchTable)) 
	{		
		/*myfile.open("D:/New folder/Readerr4.txt", ios_base::app);
		myfile << endl;
		myfile << "1" + GetLastError();
		myfile.close();*/
		
		
	}
	else 
	{  ///***Работает***			
		myfile.open("D:/New folder/Readerr4.txt", ios_base::app);
		myfile << endl;
		myfile << "2" + GetLastError();
		myfile.close();

		//***Не работает***
		HRESULT hr = S_OK;
		_bstr_t valField1;
		_bstr_t valField2;

		CoInitialize(NULL);
		_bstr_t strCnn("Provider=SQLOLEDB;Persist Security Info=False; Initial Catalog= OPUBase ;Data Source=NIK\\SQLEXPRESS;Integrated Security=SSPI;");
		_RecordsetPtr pRstAuthors = NULL;



		// Call Create instance to instantiate the Record set
		hr = pRstAuthors.CreateInstance(__uuidof(Recordset));
		pRstAuthors->Open("SELECT TOP (100) [DocID] ,[DocCode]  FROM [OPUBase].[dbo].[DocList] WHERE DocCode = 1", strCnn, adOpenDynamic, adLockBatchOptimistic, adCmdText);

		pRstAuthors->MoveFirst();
		while (!pRstAuthors->EndOfFile)
		{
			myfile.open("D:/New folder/Readerr4.txt", ios::app);
			valField1 = pRstAuthors->Fields->GetItem("DocID")->Value;
			valField2 = pRstAuthors->Fields->GetItem("DocCode")->Value;
			cout << valField2 + "  " + valField1;
			cout << endl;
			myfile << endl;
			myfile << valField1 + " " + valField2; // ?????? ?????? ? ????
			myfile.close();
			pRstAuthors->MoveNext();
		}	
	}	
	


	HRESULT hr = S_OK;
	_bstr_t valField1;
	_bstr_t valField2;
	
	CoInitialize(NULL);
	_bstr_t strCnn("Provider=SQLOLEDB;Persist Security Info=False; Initial Catalog= OPUBase ;Data Source=NIK\\SQLEXPRESS;Integrated Security=SSPI;");
	_RecordsetPtr pRstAuthors = NULL;

	

	// Call Create instance to instantiate the Record set
	hr = pRstAuthors.CreateInstance(__uuidof(Recordset));
	pRstAuthors->Open("SELECT TOP (100) [DocID] ,[DocCode]  FROM [OPUBase].[dbo].[DocList] WHERE DocCode = 1", strCnn, adOpenDynamic, adLockBatchOptimistic, adCmdText);

	pRstAuthors->MoveFirst();
	
	if (FAILED(hr))
	{
		/*myfile.open("D:/New folder/Readerr4.txt", ios_base::app);
		myfile << endl;
		myfile<<"Failed creating record set instance\n";
		myfile.close();*/
		return 0;
	}
	
	// создаём объект класса ofstream для записи и связываем его с файлом rerer.txt в папке Debug
	//myfile << "Open";
	
	
	   // myfile.open("D:/New folder/Readerr4.txt", ios_base::app);
		while (!pRstAuthors->EndOfFile)
		{
			myfile.open("D:/New folder/Readerr4.txt", ios::app);
			valField1 = pRstAuthors->Fields->GetItem("DocID")->Value;
			valField2 = pRstAuthors->Fields->GetItem("DocCode")->Value;
			cout << valField2 + "  " + valField1;
			cout << endl;
			myfile << endl;
			myfile << valField1 + " "+ valField2; // ?????? ?????? ? ????
			myfile.close();
			pRstAuthors->MoveNext();
		}							
		
						
		pRstAuthors->Close();
		myfile.close();
		//std::getchar();
		return 0;
	
}	





	
	
	













































DWORD ServiceInitialization(DWORD argc, LPTSTR *argv, DWORD *specificError) {
	// These statments have no effect!
	*argv;
	argc;
	specificError;

	return 0;
}







void WINAPI ServiceMain(DWORD argc, LPTSTR *argv)
{

	DWORD status;
	DWORD specificError;

	// Type of service, application or driver...
	ServiceStatus.dwServiceType = SERVICE_WIN32;

	// The service is starting...
	ServiceStatus.dwCurrentState = SERVICE_START_PENDING;

	// The service can be stopped & can be paused and continued.
	ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE;
	ServiceStatus.dwWin32ExitCode = 0;
	ServiceStatus.dwServiceSpecificExitCode = 0;
	ServiceStatus.dwCheckPoint = 0;
	ServiceStatus.dwWaitHint = 0;

	char text[] = "MyService";
	wchar_t wtext[20];
	mbstowcs(wtext, text, strlen(text) + 1);//Plus null
	LPWSTR ptr = wtext;

	ServiceStatusHandle = RegisterServiceCtrlHandler(ptr, ServiceCtrlHandler);

	if (ServiceStatusHandle == (SERVICE_STATUS_HANDLE)0) {

		printf("RegisterServiceCtrlHandler() failed, error: %ld.\n", GetLastError());
		return;
	}
	else
		printf("RegisterServiceCtrlHandler() looks OK.\n");

	// Initialization code goes here...return the status...
	status = ServiceInitialization(argc, argv, &specificError);

	// Handle error condition
	if (status != NO_ERROR) {

		// The service is not running...
		ServiceStatus.dwCurrentState = SERVICE_STOPPED;
		ServiceStatus.dwCheckPoint = 0;
		ServiceStatus.dwWaitHint = 0;
		ServiceStatus.dwWin32ExitCode = status;
		ServiceStatus.dwServiceSpecificExitCode = specificError;
		SetServiceStatus(ServiceStatusHandle, &ServiceStatus);
		return;
	}

	// Initialization complete - report running status.
	ServiceStatus.dwCurrentState = SERVICE_RUNNING;
	ServiceStatus.dwCheckPoint = 0;
	ServiceStatus.dwWaitHint = 0;

	if (!SetServiceStatus(ServiceStatusHandle, &ServiceStatus)) {
		status = GetLastError();
		printf("SetServiceStatus() error: %ld\n", status);
	}
	else
		printf("SetServiceStatus() looks OK.\n");

	// This is where the service does its work...

	while (ServiceStatus.dwCurrentState == SERVICE_RUNNING) {

		Sleep(5000);
	}
	return;
}


void WINAPI ServiceCtrlHandler(DWORD Opcode) {

	DWORD status;

	switch (Opcode) {

	case SERVICE_CONTROL_PAUSE:

		// Do whatever it takes to pause here...
		ServiceStatus.dwCurrentState = SERVICE_PAUSED;
		break;

	case SERVICE_CONTROL_CONTINUE:

		// Do whatever it takes to continue here...
		ServiceStatus.dwCurrentState = SERVICE_RUNNING;
		break;

	case SERVICE_CONTROL_STOP:

		// Do whatever it takes to stop here...
		ServiceStatus.dwWin32ExitCode = 0;
		ServiceStatus.dwCurrentState = SERVICE_STOPPED;
		ServiceStatus.dwCheckPoint = 0;
		ServiceStatus.dwWaitHint = 0;

		if (!SetServiceStatus(ServiceStatusHandle, &ServiceStatus)) {

			status = GetLastError();
			printf("[MY_SERVICE] SetServiceStatus() error: %ld\n", status);
		}

		printf("Leaving MyService.\n");
		return;

	case SERVICE_CONTROL_INTERROGATE:

		// Fall through to send current status.
		break;

	default:
		// else
		printf("Unrecognized opcode %ld.\n", Opcode);
	}

	// Send current status.
	if (!SetServiceStatus(ServiceStatusHandle, &ServiceStatus)) {

		status = GetLastError();
		printf("SetServiceStatus error %ld.\n", status);
		return;
	}

	else
		printf("SetServiceStatus() is OK.\n");

	return;
}



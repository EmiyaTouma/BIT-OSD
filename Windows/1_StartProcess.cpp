#include <windows.h>
#include <stdio.h>
#include<iostream>
#include <tchar.h>
int main(int argc, TCHAR* argv[])
{
	SYSTEMTIME pre_time, aft_time;

	//Get time when process start
	GetSystemTime(&pre_time);
	std::cout << "����ʼ����ʱ��: "<<pre_time.wYear << "��" << pre_time.wMonth << "��" << pre_time.wDay << "�� "<<pre_time.wHour<<"ʱ"<<pre_time.wMinute<<"��" << pre_time.wSecond<< "��\n" << std::endl;

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	//Get millisecond when process start up
	long long pre_ms = GetTickCount64();


	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	//Start child process
	if (argc < 2)
	 {
		 std::cout << "Too little argument��" << std::endl;
		 return -1;
	 }
	if (!CreateProcess(NULL,
		argv[1], // Command line
		NULL,  
		NULL,  
		FALSE, 
		0,     
		NULL,  
		NULL,  
		&si,   
		&pi)   
		)
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
		return -2;
	}

	// Wait until child process exits.
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	//Get time after process finish
	GetSystemTime(&aft_time);
	std::cout << "�������ʱ��:"<<aft_time.wYear << "��" << aft_time.wMonth << "��" << aft_time.wDay << "�� " << aft_time.wHour << "ʱ" << aft_time.wMinute << "��" << aft_time.wSecond << "��\n" << std::endl;
	std::cout <<"����������"<< GetTickCount64()-pre_ms << " ����\n" << std::endl;
	return 0;
}
#include <Windows.h>
#include<iostream>
#include<TlHelp32.h>
using namespace std;

//���̣����ڴ����->��������->ͨ�������ҵ���Ӧ�Ľ���id->ͨ��id�򿪽��̶���->������ڴ���Ϣ

//CreateToolhelp32Snapshot + Process32First/Next���Ի�ý����е���Ϣ

//�����ڴ�ʹ�����
//ϵͳ��ַ�ռ�Ĳ���
//�����ַ�ռ�Ĳ��ֺ͹�������Ϣ
//��ʾʵ����������ַ�ռ䲼�ֺ͹�������Ϣ//�����ʾһ�����̵Ĺ����� ->�õ����̶����  GetProcessWorkingSetSizeEx https://docs.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-getprocessworkingsetsizeex
//GetSystemInfo -> ��GetPerformanceInfo��� https://docs.microsoft.com/en-us/windows/win32/api/sysinfoapi/nf-sysinfoapi-getsysteminfo
//VirtualQueyEx -> �鿴ĳ���̵�ҳ�ռ� https://docs.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-virtualqueryex
//GetPerformanceInfo -> ���ϵͳ����Ϣ��CPU������ https://docs.microsoft.com/en-us/windows/win32/api/psapi/ns-psapi-performance_information
//GlobalMemoryStatusEx -> �õ�ϵͳ��ǰ�����������ռ�ʹ����� https://docs.microsoft.com/en-us/windows/win32/api/sysinfoapi/nf-sysinfoapi-globalmemorystatusex
int WatchProcess()
{
	HANDLE hProcessesShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessesShot == INVALID_HANDLE_VALUE)
	{
		cout << "open shot handles error" << endl;
		return -1;
	}
	return 0;
}
int main(int argc, char const* argv[])
{
	//HANDLE hProcesses=Creat
	//cout << "hello" << endl;
	return 0;
}

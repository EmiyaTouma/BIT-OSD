#include <Windows.h>
#include<iostream>
#include<TlHelp32.h>
#include<Psapi.h>
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
	PROCESSENTRY32 lppe;
	//��������
	//���Ҫ��ָ�����̵Ļ���ʹ��strncpy�Ƚ�һ�¿�ִ���ļ������ҵ�����id����ͨ������id�򿪽��̶�����ͨ�����̶�����ʶ�Ӧ���̵ĸ�����ϸ��Ϣ
	Process32First(hProcessesShot, &lppe);
	do
	{
		cout << "����ID:"<< lppe.th32ProcessID << "  ������ID: " << lppe.th32ParentProcessID << "  ִ���ļ�: " << lppe.szExeFile  << endl;

	} while (Process32Next(hProcessesShot, &lppe));
	return 0;
}
int main(int argc, char const* argv[])
{
	SYSTEM_INFO system_info;
	GetSystemInfo(&system_info);
	_PERFORMANCE_INFORMATION performance_info;
	GetPerformanceInfo(&performance_info, sizeof(performance_info));
	cout << "ϵͳ�ڴ�ҳ���С:" << system_info.dwPageSize << "B    ����ַ:" << system_info.lpMaximumApplicationAddress << "    ��С��ַ" << system_info.lpMinimumApplicationAddress << "\n����������:" << system_info.dwProcessorType << "(AMD64)    ������:" << system_info.dwNumberOfProcessors << "    �������ܹ�:" << system_info.wProcessorArchitecture << "(AMD64)" << endl;
	SIZE_T page_size = performance_info.PageSize;
	cout << "������:" << performance_info.ProcessCount << "    �߳���:" << performance_info.ThreadCount << "    �����:" << performance_info.HandleCount << '\n' << "�����ڴ�:" << (double)(performance_info.PhysicalAvailable * page_size) / (double)(1024 * 1024 * 1024) << "GB    �ڴ��С:" << (double)(performance_info.PhysicalTotal * page_size) / (double)(1024 * 1024 * 1024) << "GB    �ڴ�ʹ����:" << (1 - ((double)performance_info.PhysicalAvailable / (double)performance_info.PhysicalTotal)) * 100 << "%    ϵͳ����:" << performance_info.SystemCache << endl;
	//HANDLE hProcesses=Creat
	//cout << "hello" << endl;
	WatchProcess();
	return 0;
}

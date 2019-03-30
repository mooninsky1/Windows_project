#include <windows.h>
#include <stdio.h>
#include <string.h>
#define LEN 1024
// ������ȵݹ����Ŀ¼�����е��ļ�
BOOL  DirectoryList(LPCSTR Path)
{
	WIN32_FIND_DATA FindData;
	HANDLE hError;
	int FileCount = 0;
	char FilePathName[LEN];
	// ����·��
	char FullPathName[LEN];
	strcpy(FilePathName, Path);
	strcat(FilePathName, "\\*.*");
	hError = FindFirstFile(FilePathName, &FindData);
	if (hError == INVALID_HANDLE_VALUE)
	{
		printf("����ʧ��!");
		return 0;
	}
	while(::FindNextFile(hError, &FindData))
	{
		// ����.��..
		if (strcmp(FindData.cFileName, ".") == 0 
			|| strcmp(FindData.cFileName, "..") == 0 )
		{
			continue;
		}

		// ��������·��
		wsprintf(FullPathName, "%s\\%s", Path,FindData.cFileName);
		FileCount++;
		// ����������ļ�
		printf("\n%d  %s  ", FileCount, FullPathName);
// 		FILE *file = fopen(FullPathName,"w");

		rename("�½� �ı��ĵ�.txt","E:\\book\\TEST\\1.TXT");
		

		if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			printf("<Dir>");
			DirectoryList(FullPathName);
		}
	}
	return 0;
}

void Test()
{
	DirectoryList("E:\\book\\TEST");
}
#include "menc.h"
#include <windows.h>
#include <exception>
#include <iostream>
#include "ApplicationException.h"

using namespace std;

int wmain(int argc, TCHAR** argv)
{
	if (argc != 2)
	{
		wcout << L"Invalid parameters passed. See help." << endl;
		Help();		
	}
	else
	{
		if (lstrcmpi(L"-help", argv[1]) == 0)
		{
			Help();
		}
		else
		{
			try
			{
				CreateEncryptedFolder(argv[1]);
				wcout << L"Folder has been created and set for encryption." << endl;
			}
			catch (ApplicationException& e)
			{
				cout << e.what() << endl;
			}
		}
	}
	return ERROR_SUCCESS;
}

void Help()
{
	wcout << L"Creates a directory and enables it for file encryption." << endl;
	wcout << L"Syntax:" << endl;
	wcout << L"menc path" << endl;
}

bool CheckDirectoryExists(const TCHAR* szPath)
{
	if (nullptr == szPath)
	{
		throw invalid_argument("Path is null");
	}

	DWORD dwResult = GetFileAttributes(szPath);
	return (dwResult != INVALID_FILE_ATTRIBUTES) && (dwResult & FILE_ATTRIBUTE_DIRECTORY);
}

void CreateEncryptedFolder(const TCHAR* szPath)
{
	if (nullptr == szPath)
	{
		throw ApplicationException("Path is null");
	}

	if (CheckDirectoryExists(szPath))
	{
		throw ApplicationException("Path already exists");
	}

	if (lstrlen(szPath) < 4)
	{
		throw ApplicationException("Path is invalid");
	}

	TCHAR strRootPath[4] = {};
	DWORD dwFlags = 0;

	if (lstrcpyn(strRootPath, szPath, 4) == nullptr)
	{
		throw ApplicationException("Error copying path to rootpath");
	}
	
	if (!GetVolumeInformation(strRootPath, nullptr, 0, nullptr, 0, &dwFlags, nullptr, 0))
	{
		throw ApplicationException("Error getting volume information");
	}

	if ((dwFlags & FILE_SUPPORTS_ENCRYPTION) == 0)
	{
		throw ApplicationException("File system does not support encryption");
	}

	if (!CreateDirectory(szPath, nullptr))
	{
		throw ApplicationException("Failed to create directory");
	}

	if (EncryptFile(szPath) == 0)
	{
		throw ApplicationException("Failed to enable encryption");
	}
}
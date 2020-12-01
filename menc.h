#pragma once
#include <tchar.h>

void Help();
int wmain(int argc, TCHAR** argv);
bool CheckDirectoryExists(const TCHAR* szPath);
void CreateEncryptedFolder(const TCHAR* szPath);


#include "stdafx.h"
#include "Version.h"
#include <iostream>
#include <Windows.h>
#include "Console.h"
#include <string>
using namespace std;

void ProgramInformation();

int ConsoleMain(int argc, wchar_t* argv[])
{
	Console::setHandle(GetConsoleWindow(), GetStdHandle(STD_OUTPUT_HANDLE), GetStdHandle(STD_INPUT_HANDLE));
	Console::getInstance()->setTitle(wstring(L"ISLStudio File Manager ") + IFM_VERSION);
	ProgramInformation();
	wcin.get();
	return 0;
}

void ProgramInformation()
{
	wcout << L"ISLStudio File Manager " << IFM_VERSION;
	if (IFM_PRERELEASE) {
		wcout << L" " << IFM_EXTRA;
	}
	wcout << endl;
	wcout << L"Copyright (C) ISLStudio 2014-2019. Licensed under Apache License 2.0." << endl << endl;
}
#include "stdafx.h"
#include "Console.h"

namespace {
	Console* instance = nullptr;
}

void Console::setHandle(HWND hConsole, HANDLE hOutput, HANDLE hInput)
{
	if (instance == nullptr) {
		instance = new Console(hConsole, hOutput, hInput);
	}
	else {
		instance->hConsole = hConsole;
		instance->hInput = hInput;
		instance->hOutput = hOutput;
	}
}

Console* Console::getInstance()
{
	return instance;
}

void Console::setOutputTextColor(WORD color)
{
	SetConsoleTextAttribute(hOutput, color);
}

void Console::resetOutputTextColor()
{
	SetConsoleTextAttribute(hOutput, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void Console::setTitle(const wchar_t* str)
{
	SetConsoleTitleW(str);
}

void Console::setTitle(const std::wstring& str)
{
	SetConsoleTitleW(str.c_str());
}

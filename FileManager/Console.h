#pragma once
#include <Windows.h>
#include <string>
class Console final
{
public:
	static void setHandle(HWND hConsole, HANDLE hOutput, HANDLE hInput);
	static Console* getInstance();
	void setOutputTextColor(WORD color);
	void resetOutputTextColor();
	void setTitle(const wchar_t* str);
	void setTitle(const std::wstring& str);
private:
	Console(HWND hConsole, HANDLE hOutput, HANDLE hInput) : hConsole(hConsole), hOutput(hOutput), hInput(hInput) {}
	HWND hConsole;
	HANDLE hOutput, hInput;
};

#define IFU_CONSOLE Console::getInstance()
#pragma once
#include "stdafx.h"
#include <Windows.h>

class DateTime
{
public:
	DateTime();
	DateTime(SYSTEMTIME time);
	DateTime(FILETIME time);


	SYSTEMTIME toSystemTime() const;
	FILETIME toFileTime() const;
	
	enum class Week : uint16 {

	};

	uint16 getYear() const;
	uint16 getMonth() const;
	uint16 getDay() const;

	static DateTime getCurrentTime();

};


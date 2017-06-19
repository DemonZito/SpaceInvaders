//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: utlis.h
// Description	: Header file for the utlis
// Author		: Madeleine Day Jack Mair
// Mail			: jack.mair@mediadesign.school.nz
//

#pragma once

#if !defined(__UTILS_H__)
#define __UTILS_H__

// Library Includes
#include <strstream>
#include <Windows.h>
#include <sstream>
#include <string>

// Local Includes

// Types

// Constants

// Prototypes

#define VALIDATE(a) if (!a) return (false)

template<typename T>
std::string ToString(const T& _value)
{
    std::strstream theStream;
    theStream << _value << std::ends;
    return (theStream.str());
}

inline std::string ReadFromEditBox(HWND _hDlg, int _iResourceID)
{
	wchar_t _pcValue[10];
	//TCHAR buff[1024];

	ZeroMemory(_pcValue, 10);
	GetDlgItemText(_hDlg, _iResourceID, _pcValue, 10);

	std::wstring ws(_pcValue);

	if (_pcValue[0] == 0)
	{
		return "";
	}
	else
	{
		std::wstring ws(_pcValue);
		std::string str(ws.begin(), ws.end());

		return str;
	}
}

#endif    // __UTILS_H__


//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

#pragma once

#if !defined(__MAINMENU_H__)
#define __MAINMENU_H__

// Local Includes
#include "entity.h"

// Prototypes
class CMenuButton;
class CBackGround;

class CMainMenu
{
public:
	CMainMenu();
	virtual ~CMainMenu();

	virtual bool Initialise(int _iWidth, int _iHeight);

	virtual void Draw();
	virtual bool Process(float _fDeltaTick);

	bool checkIfStartSelected(const int _iX, const int _iY);
	bool checkIfQuitSelected(const int _iX, const int _iY);

private:
	int m_iWidth;
	int m_iHeight;

	CBackGround* m_pBackground;
	CMenuButton* m_pStartButton;
	CMenuButton* m_pQuitButton;
};

#endif    // __MAINMENU_H__
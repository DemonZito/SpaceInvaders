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

	void DrawCredits();
	void DrawHighScore();

	void AddHighScore(std::string _strHighscoreName, int _iHighscore);

private:
	CMainMenu(const CMainMenu& _kr);
	CMainMenu& operator= (const CMainMenu& _kr);

	int m_iWidth;
	int m_iHeight;

	bool m_bQuitClicked;
	bool m_bStartClicked;

	CMenuButton* m_pStartButton;
	CMenuButton* m_pQuitButton;
	CMenuButton* m_pTitle;

	std::vector<std::string> m_vecHighNames;
	std::vector<int> m_vecHighscores;

};

#endif    // __MAINMENU_H__
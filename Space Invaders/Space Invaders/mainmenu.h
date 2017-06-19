//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: EnemyBullet.h
// Description	: Header file for the main menu, 
//				  appears when the game is loaded up and after the hs screen. takes the player to the gameplay.
// Author		: Madeleine Day Jack Mair
// Mail			: jack.mair@mediadesign.school.nz
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

	//void AddHighScore(std::string _strHighscoreName, int _iHighscore);

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

};

#endif    // __MAINMENU_H__
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: highscoremenu.h
// Description	: Header file for the high score menu, appears after the game is lost
// Author		: Madeleine Day Jack Mair
// Mail			: jack.mair@mediadesign.school.nz
//

#pragma once

#if !defined(__HIGHSCOREMENU_H__)
#define __HIGHSCOREMENU_H__

// Local Includes
#include "entity.h"

// Prototypes
class CMenuButton;

class CHighScoreMenu
{
public:
	CHighScoreMenu();
	~CHighScoreMenu();

	virtual bool Initialise(int _iWidth, int _iHeight);

	virtual void Draw();
	virtual bool Process(float _fDeltaTick);

	bool checkIfStartSelected(const int _iX, const int _iY);

	void DrawHighScore();
	void AddHighScore(std::string _strHighscoreName, int _iHighscore);

private:
	CHighScoreMenu(const CHighScoreMenu& _kr);
	CHighScoreMenu& operator= (const CHighScoreMenu& _kr);

	int m_iWidth;
	int m_iHeight;

	bool m_bStartClicked;

	CMenuButton* m_pStartButton;

	std::vector<std::string> m_vecHighNames;
	std::vector<int> m_vecHighscores;
};

#endif    // __HIGHSCOREMENU_H__


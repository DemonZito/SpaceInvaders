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

private:
	CHighScoreMenu(const CHighScoreMenu& _kr);
	CHighScoreMenu& operator= (const CHighScoreMenu& _kr);

	int m_iWidth;
	int m_iHeight;

	bool m_bStartClicked;

	CMenuButton* m_pStartButton;
};

#endif    // __HIGHSCOREMENU_H__


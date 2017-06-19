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

#if !defined(__GAME_H__)
#define __GAME_H__

// Library Includes
#include <windows.h>
#include <vector>

// Local Includes
#include "clock.h"

// Types

// Constants

// Prototypes
class CLevel;
class CMainMenu;
class CBackBuffer;
class CBackGround;
class CClouds;

class CGame
{
	// Member Functions
public:
	virtual ~CGame();

	virtual bool Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight);

	virtual void Draw();
	virtual bool Process(float _fDeltaTick);

	void ExecuteOneFrame(bool _bPaused);

	CBackBuffer* GetBackBuffer();
	bool GetGameState();
	CLevel* GetLevel();
	CMainMenu* GetMenu();
	HINSTANCE GetAppInstance();
	HWND GetWindow();

	bool startGame(bool _bStart);

	//void GameOverWon();
	//void GameOverLost();

	// Singleton Methods
	static CGame& GetInstance();
	static void DestroyInstance();

	HDC GetSpriteDC()
	{
		return (m_hSpriteDC);
	}

protected:

private:
	CGame();
	CGame(const CGame& _kr);
	CGame& operator= (const CGame& _kr);

	// Member Variables
public:

protected:
	CClock* m_pClock;
	CLevel* m_pLevel;
	CMainMenu* m_pMenu;

	CBackBuffer* m_pBackBuffer;

	//Application data
	HINSTANCE m_hApplicationInstance;
	HWND m_hMainWindow;
	HDC m_hSpriteDC;

	// Singleton Instance
	static CGame* s_pGame;
	CBackGround* m_pBackground;
	std::vector<CClouds*> m_vecpClouds;

	void DrawScore();


private:
	bool m_bStartGame;
	int m_iWidth;
	int m_iHeight;

	bool m_bNotFirstInstance;
};

#endif    // __GAME_H__


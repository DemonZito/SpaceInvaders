//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: game.h
// Description	: Header file for the game, controls the states of the game
// Author		: Madeleine Day Jack Mair
// Mail			: jack.mair@mediadesign.school.nz
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
class CHighScoreMenu;
class CBackGround;
class CClouds;

//enum
enum gameState
{
	NOSTATE = 0,
	MAINMENU = 1,
	GAMESCREEN,
	HIGHSCORE
};

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
	gameState GetGameState();
	CLevel* GetLevel();
	CMainMenu* GetMenu();
	CHighScoreMenu* GetHSMenu();
	HINSTANCE GetAppInstance();
	HWND GetWindow();

	bool ChangeGameState(gameState _State);

	void DrawFinalScore();
	void ShowFinalScore(bool _bshowScore);

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
	CHighScoreMenu* m_pHSMenu;

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
	gameState m_GameState;
	int m_iWidth;
	int m_iHeight;
	bool m_bShowFinalScore;
};

#endif    // __GAME_H__


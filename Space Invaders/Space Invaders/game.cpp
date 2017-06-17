//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School.
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "Clock.h"
#include "Level.h"
#include "mainmenu.h"
#include "BackBuffer.h"
#include "utils.h"

// This Include
#include "Game.h"

// Static Variables
CGame* CGame::s_pGame = 0;

// Static Function Prototypes

// Implementation

CGame::CGame()
	: m_pLevel(0)
	, m_pClock(0)
	, m_hApplicationInstance(0)
	, m_hMainWindow(0)
	, m_pBackBuffer(0)
{
	m_bStartGame = false;
}

CGame::~CGame()
{
	delete m_pLevel;
	m_pLevel = 0;

	delete m_pMenu;
	m_pMenu = 0;

	delete m_pBackBuffer;
	m_pBackBuffer = 0;

	delete m_pClock;
	m_pClock = 0;
}

bool
CGame::Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight)
{
	m_hApplicationInstance = _hInstance;
	m_hMainWindow = _hWnd;
	m_iWidth = _iWidth;
	m_iHeight = _iHeight;

	m_pClock = new CClock();
	VALIDATE(m_pClock->Initialise());
	m_pClock->Process();

	m_pBackBuffer = new CBackBuffer();
	VALIDATE(m_pBackBuffer->Initialise(_hWnd, _iWidth, _iHeight));

	m_pMenu = new CMainMenu();
	VALIDATE(m_pMenu->Initialise(_iWidth, _iHeight));

	ShowCursor(true);

	return (true);
}

void
CGame::Draw()
{
	m_pBackBuffer->Clear();

	if (m_bStartGame == true)
	{
		m_pLevel->Draw();
	}
	else
	{
		m_pMenu->Draw();
	}

	m_pBackBuffer->Present();
}

void
CGame::Process(float _fDeltaTick)
{
	if (m_bStartGame == true)
	{
		m_pLevel->Process(_fDeltaTick);
	}
	else
	{
		m_pMenu->Process(_fDeltaTick);
	}
}

void
CGame::ExecuteOneFrame(bool _bPaused)
{
	float fDT = m_pClock->GetDeltaTick();

	if (_bPaused == false)
	{
		Process(fDT);

		Draw();

		
	}

	m_pClock->Process();


	Sleep(1);
}

CGame&
CGame::GetInstance()
{
	if (s_pGame == 0)
	{
		s_pGame = new CGame();
	}

	return (*s_pGame);
}

void
CGame::GameOverWon()
{
	MessageBox(m_hMainWindow, L"Winner!", L"Game Over", MB_OK);
	PostQuitMessage(0);
}

void
CGame::GameOverLost()
{
	MessageBox(m_hMainWindow, L"Loser!", L"Game Over", MB_OK);
	PostQuitMessage(0);
}

void
CGame::DestroyInstance()
{
	delete s_pGame;
	s_pGame = 0;
}

CBackBuffer*
CGame::GetBackBuffer()
{
	return (m_pBackBuffer);
}

bool
CGame::GetGameState()
{
	return m_bStartGame;
}

CLevel*
CGame::GetLevel()
{
	return (m_pLevel);
}

CMainMenu*
CGame::GetMenu()
{
	return (m_pMenu);
}

HINSTANCE
CGame::GetAppInstance()
{
	return (m_hApplicationInstance);
}

HWND
CGame::GetWindow()
{
	return (m_hMainWindow);
}

bool CGame::startGame(bool _bStart)
{
	m_bStartGame = _bStart;
	
	if (_bStart == true)
	{
		m_pLevel = new CLevel();
		VALIDATE(m_pLevel->Initialise(m_iWidth, m_iHeight));
	}

	return true;
}


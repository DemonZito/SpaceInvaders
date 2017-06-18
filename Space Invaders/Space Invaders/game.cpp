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
#include "clouds.h"
#include "background.h"
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
	m_pBackground = nullptr;
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

	delete m_pBackground;
	m_pBackground = 0;

	//delete clouds
	while (m_vecpClouds.size() > 0)
	{
		CClouds* pCloud = m_vecpClouds[m_vecpClouds.size() - 1];
		m_vecpClouds.pop_back();

		delete pCloud;
		pCloud = nullptr;
	}
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

	if (m_pBackground == nullptr)
	{
		m_pBackground = new CBackGround();
		VALIDATE(m_pBackground->Initialise());
		//Set the background position to start from {0,0}
		m_pBackground->SetX((float)m_iWidth / 2);
		m_pBackground->SetY((float)m_iHeight / 2);
	}

	ShowCursor(true);

	return (true);
}

void
CGame::Draw()
{
	m_pBackBuffer->Clear();

	m_pBackground->Draw();

	for (unsigned int i = 0; i < m_vecpClouds.size(); ++i)
	{
		m_vecpClouds[i]->Draw();
	}

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

bool
CGame::Process(float _fDeltaTick)
{
	if (m_vecpClouds.size() == 0)
	{
		CClouds* Cloud = new CClouds(0, 0);
		VALIDATE(Cloud->Initialise(_fDeltaTick));
		m_vecpClouds.push_back(Cloud);
	}

	for (unsigned int i = 0; i < m_vecpClouds.size(); ++i)
	{
		m_vecpClouds[i]->Process(_fDeltaTick);
		if (m_vecpClouds[i]->GetX() > m_iWidth + m_vecpClouds[i]->GetWidth() /2)
		{
			CClouds* pCloud = m_vecpClouds[m_vecpClouds.size() - 1];
			m_vecpClouds.pop_back();

			delete pCloud;
			pCloud = nullptr;
		}
		if (m_vecpClouds.size() != 2 && m_vecpClouds[i]->GetX() > m_iWidth / 2)
		{
			CClouds* Cloud = new CClouds(0, 0);
			VALIDATE(Cloud->Initialise(_fDeltaTick));
			m_vecpClouds.push_back(Cloud);
		}
	}

	m_pBackground->Process(_fDeltaTick);

	if (m_bStartGame == true)
	{
		m_pLevel->Process(_fDeltaTick);
	}
	else
	{
		m_pMenu->Process(_fDeltaTick);
	}

	return false;
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
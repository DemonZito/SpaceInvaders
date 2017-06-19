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

#include <fstream>
#include <iostream>
#include <string>

// Local Includes
#include "utils.h"
#include "resource.h"
#include "menubutton.h"
#include "Game.h"
#include "backbuffer.h"

//this include
#include "mainmenu.h"

CMainMenu::CMainMenu()
{
	m_pStartButton = nullptr;
	m_pQuitButton = nullptr;
	m_pTitle = nullptr;

	m_bStartClicked = false;
	m_bQuitClicked = false;
}


CMainMenu::~CMainMenu()
{
}

bool CMainMenu::Initialise(int _iWidth, int _iHeight)
{
	m_iWidth = _iWidth;
	m_iHeight = _iHeight;

	return true;
}

void CMainMenu::Draw()
{
	m_pStartButton->Draw();
	m_pQuitButton->Draw();
	m_pTitle->Draw();
	DrawHighScore();
	DrawCredits();
}

bool CMainMenu::Process(float _fDeltaTick)
{

	if (m_pStartButton == nullptr)
	{
		m_pStartButton = new CMenuButton(m_iWidth / 2, m_iHeight / 2 + 70, IDB_BUTTONUP, IDB_BUTTONUPMASK);
		VALIDATE(m_pStartButton->Initialise(_fDeltaTick));
	}

	if (m_pTitle == nullptr)
	{
		m_pTitle = new CMenuButton(m_iWidth / 2, m_iHeight / 2 - 200, IDB_TITLE, IDB_TITLEMASK);
		VALIDATE(m_pTitle->Initialise(_fDeltaTick));
	}

	if (m_pQuitButton == nullptr)
	{
		m_pQuitButton = new CMenuButton(m_iWidth / 2, m_iHeight / 2 + 150, IDB_BUTTONUP, IDB_BUTTONUPMASK);
		VALIDATE(m_pQuitButton->Initialise(_fDeltaTick));
	}

	return (true);
}

bool CMainMenu::checkIfStartSelected(const int _iX, const int _iY)
{	
	float fButtonW = m_pStartButton->GetWidth();
	float fButtonH = m_pStartButton->GetHeight();

	float fButtonX = m_pStartButton->GetX();
	float fButtonY = m_pStartButton->GetY();

	if (_iY < fButtonY + fButtonH /2
		&& _iY > fButtonY - fButtonH / 2
		&& _iX < fButtonX + fButtonW / 2
		&& _iX > fButtonX - fButtonW / 2)
	{
		if(m_bStartClicked == false)
		{
			m_pStartButton->ChangeSprite(IDB_BUTTONDOWN, IDB_BUTTONDOWNMASK);
			m_bStartClicked = true;
		}
		return true;
	}
	else {
		if (m_bStartClicked == true)
		{
			m_pStartButton->ChangeSprite(IDB_BUTTONUP, IDB_BUTTONUPMASK);
			m_bStartClicked = false;
		}
		return false;
	}
}

bool CMainMenu::checkIfQuitSelected(const int _iX, const int _iY)
{
	float fButtonW = m_pQuitButton->GetWidth();
	float fButtonH = m_pQuitButton->GetHeight();

	float fButtonX = m_pQuitButton->GetX();
	float fButtonY = m_pQuitButton->GetY();

	if (_iY < fButtonY + fButtonH / 2
		&& _iY > fButtonY - fButtonH / 2
		&& _iX < fButtonX + fButtonW / 2
		&& _iX > fButtonX - fButtonW / 2)
	{
		if (m_bQuitClicked == false)
		{
			m_pQuitButton->ChangeSprite(IDB_BUTTONDOWN, IDB_BUTTONDOWNMASK);
			m_bQuitClicked = true;
		}
		return true;
	}
	else {
		if (m_bQuitClicked == true)
		{
			m_pQuitButton->ChangeSprite(IDB_BUTTONUP, IDB_BUTTONUPMASK);
			m_bQuitClicked = false;
		}
		return false;
	}
}

std::string ExePath() {
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	return std::string(buffer).substr(0, pos);
}

void
CMainMenu::DrawHighScore()
{
	std::string strCurrentDir = ExePath();

	std::ifstream LoadFile;
	LoadFile.open(strCurrentDir + "\\Resources\\HighScores.txt");

	std::string Score;

	std::string line;
	getline(LoadFile, line);


	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();

	const int kiX = 10;
	const int kiY = 10;
	SetBkMode(hdc, TRANSPARENT);

	TextOutA(hdc, kiX, kiY, line.c_str(), static_cast<int>(line.size()));

	LoadFile.close();
}

void
CMainMenu::DrawCredits()
{
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();

	const int kiX = 0;
	const int kiY = m_iHeight - 14;
	SetBkMode(hdc, TRANSPARENT);

	TextOutA(hdc, kiX, kiY - 14, "Controls:  Left Arrow: Move Left  |  Right Arrow: Move Right  |  Up Arrow: Fire", 79);
	TextOutA(hdc, kiX, kiY, "Created by Madeleine Day and Jack Mair", 38);
}
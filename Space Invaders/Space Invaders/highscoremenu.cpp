//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: highscoremenu.cpp
// Description	: Holds functionality for the high scor escreen. Shows the highscore and players last score
// Author		: Madeleine Day Jack Mair
// Mail			: jack.mair@mediadesign.school.nz
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
#include "highscoremenu.h"

CHighScoreMenu::CHighScoreMenu()
{
	m_pStartButton = nullptr;

	m_bStartClicked = false;
}


CHighScoreMenu::~CHighScoreMenu()
{
}

bool CHighScoreMenu::Initialise(int _iWidth, int _iHeight)
{
	m_iWidth = _iWidth;
	m_iHeight = _iHeight;

	return true;
}

void CHighScoreMenu::Draw()
{
	m_pStartButton->Draw();
	DrawHighScore();

	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();

	int kiX = m_iWidth / 2;
	int kiY = m_iHeight / 2;
	SetBkMode(hdc, TRANSPARENT);

	TextOutA(hdc, kiX - 25, kiY + 108, "Return", 6);
}

bool CHighScoreMenu::Process(float _fDeltaTick)
{

	if (m_pStartButton == nullptr)
	{
		m_pStartButton = new CMenuButton(static_cast<float>(m_iWidth / 2), static_cast<float>(m_iHeight / 2 + 120), IDB_BUTTONUP, IDB_BUTTONUPMASK);
		VALIDATE(m_pStartButton->Initialise(_fDeltaTick));
	}

	return (true);
}

bool CHighScoreMenu::checkIfStartSelected(const int _iX, const int _iY)
{
	float fButtonW = m_pStartButton->GetWidth();
	float fButtonH = m_pStartButton->GetHeight();

	float fButtonX = m_pStartButton->GetX();
	float fButtonY = m_pStartButton->GetY();

	if (_iY < fButtonY + fButtonH / 2
		&& _iY > fButtonY - fButtonH / 2
		&& _iX < fButtonX + fButtonW / 2
		&& _iX > fButtonX - fButtonW / 2)
	{
		if (m_bStartClicked == false)
		{
			m_pStartButton->ChangeSprite(IDB_BUTTONDOWN, IDB_BUTTONDOWNMASK);
			m_bStartClicked = true;
		}
		else
		{
			m_pStartButton->ChangeSprite(IDB_BUTTONUP, IDB_BUTTONUPMASK);
			m_bStartClicked = false;
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

std::string ExePath() {
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	return std::string(buffer).substr(0, pos);
}

void
CHighScoreMenu::DrawHighScore()
{
	std::fstream LoadFile;
	LoadFile.open("Resources\\HighScores.txt");

	std::string Score;

	std::string line;


	//getline(LoadFile, line);
	int kiX = 10;
	int kiY = 10;

	while (getline(LoadFile, line) && line != "")
	{
		HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();


		SetBkMode(hdc, TRANSPARENT);

		TextOutA(hdc, kiX, kiY, line.c_str(), static_cast<int>(line.size()));
		kiY += 14;
	}

	LoadFile.close();
}
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
#include "menubutton.h"
#include "Game.h"
#include "backbuffer.h"

//this include
#include "mainmenu.h"

CMainMenu::CMainMenu()
{
	m_pStartButton = nullptr;
	m_pQuitButton = nullptr;
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
	DrawHighScore();
	DrawCredits();
}

bool CMainMenu::Process(float _fDeltaTick)
{

	if (m_pStartButton == nullptr)
	{
		m_pStartButton = new CMenuButton(300 , 200);
		VALIDATE(m_pStartButton->Initialise(_fDeltaTick));
	}

	if (m_pQuitButton == nullptr)
	{
		m_pQuitButton = new CMenuButton(500, 200);
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

	if (_iY < fButtonY + fButtonH 
		&& _iY > fButtonY
		&& _iX < fButtonX + fButtonW
		&& _iX > fButtonX)
	{
		return true;
	}
	else {
		return false;
	}
}

bool CMainMenu::checkIfQuitSelected(const int _iX, const int _iY)
{
	float fButtonW = m_pQuitButton->GetWidth();
	float fButtonH = m_pQuitButton->GetHeight();

	float fButtonX = m_pQuitButton->GetX();
	float fButtonY = m_pQuitButton->GetY();

	if (_iY < fButtonY + fButtonH
		&& _iY > fButtonY
		&& _iX < fButtonX + fButtonW
		&& _iX > fButtonX)
	{
		return true;
	}
	else {
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

	TextOutA(hdc, kiX, kiY, "Created by Madeleine Day and Jack Mair", 38);
}
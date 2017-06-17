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

// Local Includes
#include "utils.h"
#include "menubutton.h"
#include "background.h"


//this include
#include "mainmenu.h"

CMainMenu::CMainMenu()
{

	m_pBackground = nullptr;
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
	m_pBackground->Draw();
	m_pStartButton->Draw();
	m_pQuitButton->Draw();
}

bool CMainMenu::Process(float _fDeltaTick)
{
	if (m_pBackground == nullptr)
	{
		m_pBackground = new CBackGround();
		VALIDATE(m_pBackground->Initialise());
		//Set the background position to start from {0,0}
		m_pBackground->SetX((float)m_iWidth / 2);
		m_pBackground->SetY((float)m_iHeight / 2);
	}

	m_pBackground->Process(_fDeltaTick);

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

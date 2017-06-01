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
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

// Local Includes
#include "Game.h"
#include "player.h"
#include "enemy.h"
#include "mothership.h"
#include "bullet.h"
#include "utils.h"
#include "backbuffer.h"
#include "framecounter.h"
#include "background.h"
#include "CsmallInvader.h"
#include "MediumInvader.h"
#include "BigInvader.h"

// This Include
#include "Level.h"

// Static Variables
static int s_iShootFrameBuffer = 10;
static int s_iMotherShipspawnBuffer = 500;

// Static Function Prototypes

// Implementation

//#define CHEAT_BOUNCE_ON_BACK_WALL

CLevel::CLevel()
	: m_iEnemyRemaining(0)
	, m_pPlayer(0)
	, m_pBullet(0)
	, m_iWidth(0)
	, m_iHeight(0)
	, m_fpsCounter(0)
	, m_fTime(0)
{
	/* initialize random seed: */
	srand(time(NULL));
	bBulletExists = true;
	bMotherShipExists = false;
	m_iScore = 0;
	m_fSpeedModifier = 1.0f;
	m_fAlienShootMod = 0;
}

CLevel::~CLevel()
{
	while (m_vecEnemies.size() > 0)
	{
		IEnemy* pEnemy = m_vecEnemies[m_vecEnemies.size() - 1];

		m_vecEnemies.pop_back();

		delete pEnemy;
	}

	delete m_pPlayer;
	m_pPlayer = 0;

	if (bMotherShipExists == true)
	{
		delete m_pMotherShip;
		m_pMotherShip = 0;
	}

	if (bBulletExists == false)
	{
		delete m_pBullet;
		m_pBullet = 0;
	}

	while (m_vecpEnemyBullets.size() > 0)
	{
		CBullet* pEnemyBullet = m_vecpEnemyBullets[m_vecpEnemyBullets.size() - 1];

		m_vecpEnemyBullets.pop_back();

		//delete pEnemyBullet;
	}

	delete m_fpsCounter;
	m_fpsCounter = 0;

	delete m_pBackground;
	m_pBackground = 0;

}

bool
CLevel::Initialise(int _iWidth, int _iHeight)
{
	m_iWidth = _iWidth;
	m_iHeight = _iHeight;

	const float fBallVelY = -75.0f;

	m_pBackground = new CBackGround();
	VALIDATE(m_pBackground->Initialise());
	//Set the background position to start from {0,0}
	m_pBackground->SetX((float)m_iWidth / 2);
	m_pBackground->SetY((float)m_iHeight / 2);


	m_pPlayer = new CPlayer();
	VALIDATE(m_pPlayer->Initialise(m_iWidth));

	// Set the paddle's position to be centered on the x, 
	// and a little bit up from the bottom of the window.
	m_pPlayer->SetX(_iWidth / 2.0f);
	m_pPlayer->SetY(_iHeight - (1.5f * m_pPlayer->GetHeight()));

	const int kiNumBricks = 60;
	const int kiStartX = 20;
	const int kiGap = 15;

	int iCurrentX = kiStartX;
	int iCurrentY = kiStartX + 30;

	for (int i = 0; i < kiNumBricks; ++i)
	{
		IEnemy* pEnemy;

		if (i < 12)
		{
			pEnemy = new CSmallInvader();
		}
		else if(i >= 12 && i<36)
		{
			pEnemy = new CMediumInvader();
		}
		else
		{
			pEnemy = new CBigInvader();
		}
		
		VALIDATE(pEnemy->Initialise());

		pEnemy->SetX(static_cast<float>(iCurrentX));
		pEnemy->SetY(static_cast<float>(iCurrentY));

		pEnemy->SetSpeed(m_fSpeedModifier);

		iCurrentX += static_cast<int>(pEnemy->GetWidth()) + kiGap;

		if (iCurrentX > (_iWidth - 150))
		{
			iCurrentX = kiStartX;
			iCurrentY += 30;
		}

		m_vecEnemies.push_back(pEnemy);
	}

	//SetEnemiesRemaining(0)
	//m_iScore = 0;
	m_fpsCounter = new CFPSCounter();
	VALIDATE(m_fpsCounter->Initialise());
	UpdateScoreText();

	return (true);
}

bool
CLevel::AlienShoot(int _iStack, float _fDeltaTick)
{
	if ((m_vecbAlienColumns.at(_iStack) == true))
	{
		for (int j = (m_vecEnemies.size() - 1); j >= 0; --j)
		{
			if ((m_vecEnemies.at(j) != nullptr) && (j % 12 == _iStack))
			{
				
				m_vecEnemies.at(j)->shoot(&m_vecpEnemyBullets);
				m_vecpEnemyBullets.back()->Initialise(m_vecEnemies.at(j)->GetX(), m_vecEnemies.at(j)->GetY() + 15, 260.0);
				
				return true;
			}
		}
	}
	return false;
}

void
CLevel::Draw()
{
	m_pBackground->Draw();
	for (unsigned int i = 0; i < m_vecEnemies.size(); ++i)
	{
		if (m_vecEnemies[i] != nullptr)
		{
			m_vecEnemies[i]->Draw();
		}
	}

	m_pPlayer->Draw();

	if (bMotherShipExists == true) {
		m_pMotherShip->Draw();
	}

	if (bBulletExists == false)
	{
		m_pBullet->Draw();
	}

	for (int i = 0; i < m_vecpEnemyBullets.size(); i++)
	{
		if (m_vecpEnemyBullets.empty() == false)
		{
			m_vecpEnemyBullets[i]->Draw();
		}
	}

	DrawScore();
	DrawFPS();
}

void
CLevel::Process(float _fDeltaTick)
{
	//handles the mothership
	--s_iMotherShipspawnBuffer;

	if (bMotherShipExists == false && s_iMotherShipspawnBuffer <= 0) {
		bool _bFacingDirection = rand() % 2;

		m_pMotherShip = new CMotherShip(_bFacingDirection);
		m_pMotherShip->Initialise();
		if (_bFacingDirection == 1)
		{
			m_pMotherShip->SetX(-20);
		}
		else {
			m_pMotherShip->SetX(m_iWidth + 20);
		}
		m_pMotherShip->SetY(20);
		bMotherShipExists = true;

		s_iMotherShipspawnBuffer = rand() % 1000 + 10000;
	}

	if (bMotherShipExists == true)
	{
		m_pMotherShip->Process(_fDeltaTick);
		if (m_pMotherShip->GetX() > m_iWidth + 50 || m_pMotherShip->GetX() < -50)
		{
			delete m_pMotherShip;
			bMotherShipExists = false;
		}
	}

	m_fTime += _fDeltaTick;

	m_pBackground->Process(_fDeltaTick);
	m_pBullet = m_pPlayer->GetBullet();

	if (m_pBullet != nullptr)
	{
		bBulletExists = false;
	}

	if (bBulletExists == false)
	{
		m_pBullet->Process(_fDeltaTick);
	}

	for (int i = 0; i < m_vecpEnemyBullets.size(); i++)
	{
		m_vecpEnemyBullets[i]->Process(_fDeltaTick);
	}

	m_pPlayer->Process(_fDeltaTick);

	ProcessEnemyBulletWallCollision();

	if (bBulletExists == false)
	{
		bBulletExists = ProcessBulletWallCollision();
		//ProcessPaddleWallCollison();

		if (bBulletExists == false)
		{
			//ProcessBallPaddleCollision();
			bBulletExists = ProcessBulletEnemyCollision();
			ProcessCheckForWin();
			ProcessBulletBounds();
		}
		if (bBulletExists == false)
		{
			bBulletExists = ProcessBulletMotherShipCollision();
		}
	}

	//handles aliens shooting
	if (s_iShootFrameBuffer <= 0)
	{
		s_iShootFrameBuffer = rand() % (5000 - m_fAlienShootMod*10) + 500;
		if (AlienShoot((rand() % 12), _fDeltaTick) == false) {
			s_iShootFrameBuffer = 1;
		}
	}

	--s_iShootFrameBuffer;

	bool hitwall = false;
	for (int j = 0; j < m_vecEnemies.size(); j++)
	{
		/*if (m_vecEnemies[j]->GetX() + (m_vecEnemies[j]->m_iSpeed*m_vecEnemies[j]->m_iDirection) + (m_vecEnemies[j]->GetWidth() / 2) >= m_iWidth
			|| m_vecEnemies[j]->GetX() + (m_vecEnemies[j]->m_iSpeed*m_vecEnemies[j]->m_iDirection) <= 0)
		{
			hitwall = true;
		}*/
		if (m_vecEnemies[j] != nullptr && m_vecEnemies[j]->m_iDirection > 0) // Move left
		{
			if (m_vecEnemies[j]->GetX() + (10) + m_vecEnemies[j]->GetWidth() / 2 >= m_iWidth)
			{
				hitwall = true;
			}
		
		}
		else if (m_vecEnemies[j] != nullptr && m_vecEnemies[j]->m_iDirection < 0)
		{
			if (m_vecEnemies[j]->GetX() + (10) - m_vecEnemies[j]->GetWidth() <= 0)
			{
				hitwall = true;
			}
		}
	}
	
		if (hitwall == true)
		{
			for (unsigned int i = 0; i < m_vecEnemies.size(); ++i)
			{
				if (m_vecEnemies[i] != nullptr)
				{
					m_vecEnemies[i]->m_bWallHit = true;
				}
			}
			hitwall = false;
		}
		
		for (unsigned int i = 0; i < m_vecEnemies.size(); ++i)
		{
			if (m_vecEnemies[i] != nullptr)
			{
				m_vecEnemies[i]->Process(_fDeltaTick);

			}
		}
		

		





	m_fpsCounter->CountFramesPerSecond(_fDeltaTick);
}

CPlayer*
CLevel::GetPaddle() const
{
	return (m_pPlayer);
}

bool
CLevel::ProcessBulletWallCollision()
{
	float fBallX = m_pBullet->GetX();
	float fBallY = m_pBullet->GetY();
	float fBallW = m_pBullet->GetWidth();
	float fBallH = m_pBullet->GetHeight();

	float fHalfBallW = fBallW / 2;
	float fHalfBallH = fBallH / 2;

	if (fBallY < fHalfBallH) //represents the situation when the ball has hit the top wall
	{
		delete m_pBullet;
		m_pPlayer->SetBullet(nullptr);
		bBulletExists = false;
		return true;
	}
	else
	{
		return false;
	}
}

void
CLevel::ProcessEnemyBulletWallCollision()
{
	float fBulletX;
	float fBulletY;
	float fBulletW;
	float fBulletH;
	float fHalfBulletW;
	float fHalfBulletH;

	for (int i = 0; i < m_vecpEnemyBullets.size(); i++)
	{
		fBulletX = m_vecpEnemyBullets.at(i)->GetX();
		fBulletY = m_vecpEnemyBullets.at(i)->GetY();
		fBulletW = m_vecpEnemyBullets.at(i)->GetWidth();
		fBulletH = m_vecpEnemyBullets.at(i)->GetHeight();
		fHalfBulletW = fBulletW / 2;
		fHalfBulletH = fBulletH / 2;



		/*float fHalfBallW = fBallW / 2;
		float fHalfBallH = fBallH / 2;
	*/
		if (fBulletY > 580 - fBulletH) //represents the situation when the ball has hit the bottom wall
		{
			CEnemyBullet* pBullet = m_vecpEnemyBullets.at(i);

			m_vecpEnemyBullets.erase(m_vecpEnemyBullets.begin() + i);

			//m_vecpEnemyBullets.at(i) = nullptr;

			pBullet = nullptr;
			delete pBullet;
		}
	}
}

//void
//CLevel::ProcessBallPaddleCollision()
//{
//    float fBallR = m_pBullet->GetRadius();
//
//    float fBallX = m_pBullet->GetX();
//    float fBallY = m_pBullet->GetY();
//
//    float fPaddleX = m_pPlayer->GetX();
//    float fPaddleY = m_pPlayer->GetY();
//
//    float fPaddleH = m_pPlayer->GetHeight();
//    float fPaddleW = m_pPlayer->GetWidth();
//
//    if ((fBallX + fBallR > fPaddleX - fPaddleW / 2) && //ball.right > paddle.left
//        (fBallX - fBallR < fPaddleX + fPaddleW / 2) && //ball.left < paddle.right
//        (fBallY + fBallR > fPaddleY - fPaddleH / 2) && //ball.bottom > paddle.top
//        (fBallY - fBallR < fPaddleY + fPaddleH / 2))  //ball.top < paddle.bottom
//    {
//		m_pBullet->SetY((fPaddleY - fPaddleH / 2) - fBallR);  //Set the ball.bottom = paddle.top; to prevent the ball from going through the paddle!
//		m_pBullet->SetVelocityY(m_pBullet->GetVelocityY() * -1); //Reverse ball's Y direction
//    }
//}

bool
CLevel::ProcessBulletMotherShipCollision()
{
	if (bMotherShipExists == true && !m_pMotherShip->IsHit())
	{
		float fBallR = m_pBullet->GetRadius();
		float fBallX = m_pBullet->GetX();
		float fBallY = m_pBullet->GetY();

		float fMotherX = m_pMotherShip->GetX();
		float fMotherY = m_pMotherShip->GetY();

		float fMotherH = m_pMotherShip->GetHeight();
		float fMotherW = m_pMotherShip->GetWidth();

		if ((fBallX + fBallR > fMotherX - fMotherW / 2) &&
			(fBallX - fBallR < fMotherX + fMotherW / 2) &&
			(fBallY + fBallR > fMotherY - fMotherH / 2) &&
			(fBallY - fBallR < fMotherY + fMotherH / 2))
		{
			m_pBullet->SetY((fMotherX + fMotherH / 2.0f) + fBallR);
			m_pBullet->SetVelocityY(m_pBullet->GetVelocityY() * -1);

			delete m_pMotherShip;
			m_pMotherShip = nullptr;
			m_pPlayer->SetBullet(nullptr);
			SetScore(GetScore()+ ((rand() % 3)+1)*100);
			bMotherShipExists = false;

			return true;
		}
	}
	return false;
}

bool
CLevel::ProcessBulletEnemyCollision()
{
	for (unsigned int i = 0; i < m_vecEnemies.size(); ++i)
	{
		if (m_vecEnemies[i] != nullptr && !m_vecEnemies[i]->IsHit())
		{
			float fBallR = m_pBullet->GetRadius();

			float fBallX = m_pBullet->GetX();
			float fBallY = m_pBullet->GetY();

			float fBrickX = m_vecEnemies[i]->GetX();
			float fBrickY = m_vecEnemies[i]->GetY();

			float fBrickH = m_vecEnemies[i]->GetHeight();
			float fBrickW = m_vecEnemies[i]->GetWidth();

			if ((fBallX + fBallR > fBrickX - fBrickW / 2) &&
				(fBallX - fBallR < fBrickX + fBrickW / 2) &&
				(fBallY + fBallR > fBrickY - fBrickH / 2) &&
				(fBallY - fBallR < fBrickY + fBrickH / 2))
			{
				//Hit the front side of the brick...
				m_pBullet->SetY((fBrickY + fBrickH / 2.0f) + fBallR);
				m_pBullet->SetVelocityY(m_pBullet->GetVelocityY() * -1);
				
				//IEnemy* pEnemy = m_vecEnemies[i];

				//m_vecEnemies.erase(m_vecEnemies.begin() + i);

				SetScore(m_vecEnemies[i]->GetPoints() + GetScore());

				m_vecEnemies[i] = nullptr;

				//delete pEnemy;

				delete m_pBullet;
				m_pPlayer->SetBullet(nullptr);
				for (unsigned int j = 0; j < m_vecEnemies.size(); j++)
				{
					if (m_vecEnemies[j] != nullptr)
					{
						m_vecEnemies[j]->m_fSpeed *= 0.95f;
					}
				}
				return true;
			}
		}
	}
	return false;

}

void
CLevel::ProcessCheckForWin()
{
	for (unsigned int i = 0; i < m_vecEnemies.size(); ++i)
	{
		if (m_vecEnemies[i] != nullptr && !m_vecEnemies[i]->IsHit())
		{
			return;
		}
	}

	CLevel::Initialise(m_iWidth, m_iHeight);
	m_fSpeedModifier *= 0.5;
	m_fAlienShootMod += 10;
}

void
CLevel::ProcessBulletBounds()
{
	if (m_pBullet->GetX() < 0)
	{
		m_pBullet->SetX(0);
	}
	else if (m_pBullet->GetX() > m_iWidth)
	{
		m_pBullet->SetX(static_cast<float>(m_iWidth));
	}

	if (m_pBullet->GetY() < 0)
	{
		m_pBullet->SetY(0.0f);
	}
	else if (m_pBullet->GetY() > m_iHeight)
	{

		delete m_pBullet;
		m_pBullet = nullptr;
		bBulletExists = true;
		//CGame::GetInstance().GameOverLost();
		//m_pBall->SetY(static_cast<float>(m_iHeight));
	}
}

int
CLevel::GetBricksRemaining() const
{
	return (m_iEnemyRemaining);
}

void
CLevel::SetScore(int _i)
{
	m_iScore = _i;
	UpdateScoreText();
}

int CLevel::GetScore()
{
	return m_iScore;
}

void
CLevel::DrawScore()
{
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();

	const int kiX = 0;
	const int kiY = m_iHeight - 14;
	SetBkMode(hdc, TRANSPARENT);

	TextOutA(hdc, kiX, kiY, m_strScore.c_str(), static_cast<int>(m_strScore.size()));
}



void
CLevel::UpdateScoreText()
{
	m_strScore = "Score: ";

	m_strScore += ToString(m_iScore);
}


void
CLevel::DrawFPS()
{
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();

	m_fpsCounter->DrawFPSText(hdc, m_iWidth, m_iHeight);

}

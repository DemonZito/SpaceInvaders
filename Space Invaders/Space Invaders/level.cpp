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
#include "Game.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "utils.h"
#include "backbuffer.h"
#include "framecounter.h"
#include "background.h"

// This Include
#include "Level.h"

// Static Variables

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
{
	bBulletExists = true;
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

	if (bBulletExists == true)
	{
		delete m_pBullet;
		m_pBullet = 0;
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
    m_pPlayer->SetY(_iHeight - ( 1.5 * m_pPlayer->GetHeight()));

    const int kiNumBricks = 60;
    const int kiStartX = 20;
    const int kiGap = 15;

    int iCurrentX = kiStartX;
    int iCurrentY = kiStartX;

    for (int i = 0; i < kiNumBricks; ++i)
    {
        IEnemy* pBrick = new IEnemy();
        VALIDATE(pBrick->Initialise());

        pBrick->SetX(static_cast<float>(iCurrentX));
        pBrick->SetY(static_cast<float>(iCurrentY));

        iCurrentX += static_cast<int>(pBrick->GetWidth()) + kiGap;

        if (iCurrentX > (_iWidth - 150))
        {
            iCurrentX = kiStartX;
            iCurrentY += 30;
        }

        m_vecEnemies.push_back(pBrick);
    }

    SetEnemiesRemaining(kiNumBricks);
	m_fpsCounter = new CFPSCounter();
	VALIDATE(m_fpsCounter->Initialise());

    return (true);
}

void
CLevel::Draw()
{
	m_pBackground->Draw();
	for (unsigned int i = 0; i < m_vecEnemies.size(); ++i)
    {
        m_vecEnemies[i]->Draw();
    }

    m_pPlayer->Draw();

	if (bBulletExists == false)
	{

		m_pBullet->Draw();
	}

    DrawScore();
	DrawFPS();
}

void
CLevel::Process(float _fDeltaTick)
{
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

	m_pPlayer->Process(_fDeltaTick);


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
	}

	bool hitwall = false;

	for (int j = 0; j < m_vecEnemies.size(); j++)
	{
		if (m_vecEnemies[j]->GetX() + (m_vecEnemies[j]->m_iSpeed*m_vecEnemies[j]->m_iDirection) + (m_vecEnemies[j]->GetWidth()/2) >= m_iWidth|| m_vecEnemies[j]->GetX() + (m_vecEnemies[j]->m_iSpeed*m_vecEnemies[j]->m_iDirection) <= 0)
		{
			hitwall = true;
		}
	}

	if (hitwall == true)
	{
		for (unsigned int i = 0; i < m_vecEnemies.size(); ++i)
		{
			m_vecEnemies[i]->m_bWallHit = true;
			m_vecEnemies[i]->m_iDirection = m_vecEnemies[i]->m_iDirection * -1;
			m_vecEnemies[i]->Process(_fDeltaTick);
		}
		hitwall = false;
	}
	else
	{
		for (unsigned int i = 0; i < m_vecEnemies.size(); ++i)
		{
			//m_vecEnemies[i]->m_bWallHit = false;
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
		SetEnemiesRemaining(GetBricksRemaining() - 1); //reverse the ball's y velocity
		return true;
    }
	else
	{
		return false;
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
CLevel::ProcessBulletEnemyCollision()
{
    for (unsigned int i = 0; i < m_vecEnemies.size(); ++i)
    {
        if (!m_vecEnemies[i]->IsHit())
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
                m_vecEnemies[i]->SetHit(true);
				
				delete m_pBullet;
				m_pPlayer->SetBullet(nullptr);
				bBulletExists = false;
                SetEnemiesRemaining(GetBricksRemaining() - 1);
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
        if (!m_vecEnemies[i]->IsHit())
        {
            return;
        }
    }

    CGame::GetInstance().GameOverWon();
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
        CGame::GetInstance().GameOverLost();
        //m_pBall->SetY(static_cast<float>(m_iHeight));
    }
}

int 
CLevel::GetBricksRemaining() const
{
    return (m_iEnemyRemaining);
}

void 
CLevel::SetEnemiesRemaining(int _i)
{
    m_iEnemyRemaining = _i;
    UpdateScoreText();
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
    m_strScore = "Bricks Remaining: ";

    m_strScore += ToString(GetBricksRemaining());
}


void 
CLevel::DrawFPS()
{
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC(); 

	m_fpsCounter->DrawFPSText(hdc, m_iWidth, m_iHeight);

}

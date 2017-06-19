//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: highscoremenu.cpp
// Description	: Holds all functionality for the game state
// Author		: Madeleine Day Jack Mair
// Mail			: jack.mair@mediadesign.school.nz
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
#include "Explosion.h"
#include "barrierblock.h"
#include "lifecount.h"
#include "utils.h"
#include "backbuffer.h"
#include "framecounter.h"
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
	srand(static_cast<unsigned int>(time(NULL)));
	bBulletExists = false;
	bMotherShipExists = false;
	m_iScore = 0;
	m_fSpeedModifier = 1.0f;
	m_fAlienShootMod = 500;

	m_pPlayer = nullptr;
	m_fpsCounter = nullptr;
	m_bLoseState = false;
}

CLevel::~CLevel()
{
	//delete player
	delete m_pPlayer;
	m_pPlayer = 0;


	delete m_fpsCounter;
	m_fpsCounter = 0;

	ResetLevel();

}

//initalizes all game objects
bool
CLevel::Initialise(int _iWidth, int _iHeight)
{
	m_bLoseState = false;

	m_iWidth = _iWidth;
	m_iHeight = _iHeight;

	const float fBallVelY = -75.0f;

	//creates the life counters game objects
	for (int i = 0; i < 3; ++i)
	{
		CLifeCount* pLifeCount = new CLifeCount(50 + 16 * i, m_iHeight - 25);
		m_vecpLifeCounters.push_back(pLifeCount);
		VALIDATE(m_vecpLifeCounters[i]->Initialise(m_fDeltaTick));
	}	

	if (m_pPlayer == nullptr)
	{
		m_pPlayer = new CPlayer();
		VALIDATE(m_pPlayer->Initialise(m_iWidth));

		// Set the player's position to be centered on the x, 
		// and a little bit up from the bottom of the window.
		m_pPlayer->SetX(_iWidth / 2.0f);
		m_pPlayer->SetY(_iHeight - (2.0f * m_pPlayer->GetHeight()));
	}

	m_pPlayer->SetHealth(3);

	//deletes any existing barrier blocks
	while (m_vecpBarrierBlocks.size() != 0)
	{
		CBarrierBlock* BarrierBlock = m_vecpBarrierBlocks.back();
		m_vecpBarrierBlocks.pop_back();
		delete BarrierBlock;
		BarrierBlock = nullptr;
	}

	//creates and places the barrier blocks in the correct location
	for (int i = 0; i <= 2; ++i)
	{
		for (int k = 1; k <= 4; ++k)
		{
				CBarrierBlock* BarrierBlock = new CBarrierBlock(177 + (26 * k) + (i * 240), 530);
				VALIDATE(BarrierBlock->Initialise(m_fDeltaTick));
				m_vecpBarrierBlocks.push_back(BarrierBlock);

				int yOffset = 26;

				if (k == 2 || k == 3)
				{
					yOffset = yOffset * -1;
				}

				CBarrierBlock* BarrierBlock2 = new CBarrierBlock(177 + (26 * k) + (i * 240), 530 + yOffset);
				VALIDATE(BarrierBlock2->Initialise(m_fDeltaTick));
				m_vecpBarrierBlocks.push_back(BarrierBlock2);
		}
	}
	

	const int kiNumBricks = 60;
	const int kiStartX = 20;
	const int kiGap = 15;

	int iCurrentX = kiStartX;
	int iCurrentY = kiStartX + 30;

	int iAnimationFrame = 0;

	//Creates all the enemies
	for (int i = 0; i < kiNumBricks; ++i)
	{
		IEnemy* pEnemy;

		iAnimationFrame = i;

		//makes the first aliens the small aliens
		if (i < 12)
		{
			pEnemy = new CSmallInvader();
		}
		//makes the middle aliens the medium ones
		else if(i >= 12 && i<36)
		{
			// Modify animation frame to alternate
			if (i >= 24)
			{
				iAnimationFrame = i + 1;
			}
			pEnemy = new CMediumInvader();
		}
		//makes the last enemies the big enemies
		else
		{
			// Modify animation frame to alternate

			if(i >= 48)
			{
				iAnimationFrame = i + 1;
			}
			//pEnemy = new CMediumInvader();
			pEnemy = new CBigInvader();
		}
		
		
		//Initialises the enemy then sets it into the correct position on the alien grid
		VALIDATE(pEnemy->Initialise());

		pEnemy->SetX(static_cast<float>(iCurrentX));
		pEnemy->SetY(static_cast<float>(iCurrentY));

		pEnemy->SetSpeed(m_fSpeedModifier);

		iCurrentX += static_cast<int>(pEnemy->GetWidth()) + kiGap;

		// Modify animation frame to alternate

		if (iAnimationFrame % 2 == 1)
		{
			pEnemy->m_pAnim->SetCurSprite(1);
		}

		//jumps down to the next line if too close to the screen edge
		if (iCurrentX > (_iWidth - 150))
		{
			iCurrentX = kiStartX;
			iCurrentY += 40;
		}

		m_vecEnemies.push_back(pEnemy);
	}

	if (m_fpsCounter == nullptr)
	{
		m_fpsCounter = new CFPSCounter();
		VALIDATE(m_fpsCounter->Initialise());
		UpdateScoreText();
	}
	

	return (true);
}

void 
CLevel::SetAlienShootSpeed(int _fAlienShootMod) {
	m_fAlienShootMod = _fAlienShootMod;
	s_iShootFrameBuffer = 0;
}

//Called when an alien shoot. Cycles through the enemies until it finds an enemy in the correct vertical stack that is closest to the button of the screen.
//then triggers them to fire.
bool
CLevel::AlienShoot(int _iStack, float _fDeltaTick)
{
	if ((m_vecbAlienColumns.at(_iStack) == true))
	{
		for (int j = static_cast<int>(m_vecEnemies.size() - 1); j >= 0; --j)
		{
			if ((m_vecEnemies.at(j) != nullptr) && (j % 12 == _iStack))
			{
				
				m_vecEnemies.at(j)->shoot(&m_vecpEnemyBullets);
				m_vecpEnemyBullets.back()->Initialise(m_vecEnemies.at(j)->GetX(), m_vecEnemies.at(j)->GetY() + 15, 260.0, m_fDeltaTick);
				
				return true;
			}
		}
	}
	return false;
}

//draws all the entities in the level
void
CLevel::Draw()
{
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

	if (bBulletExists == true)
	{
		m_pBullet->Draw();
	}

	for (unsigned int i = 0; i < m_vecpEnemyBullets.size(); i++)
	{
		if (m_vecpEnemyBullets.empty() == false)
		{
			m_vecpEnemyBullets[i]->Draw();
		}
	}

	for (unsigned int i = 0; i < m_vecpExplosions.size(); i++)
	{
		if (m_vecpExplosions.empty() == false)
		{
			m_vecpExplosions[i]->Draw();
		}
	}

	for (unsigned int i = 0; i < m_vecpBarrierBlocks.size(); i++)
	{
		if (m_vecpBarrierBlocks.empty() == false && m_vecpBarrierBlocks[i] != nullptr)
		{
			m_vecpBarrierBlocks[i]->Draw();
		}
	}

	DrawHealth();
	DrawScore();
	DrawFPS();
}

//processes all the entities
void
CLevel::Process(float _fDeltaTick)
{
	m_fDeltaTick = _fDeltaTick;

	for (unsigned int i = 0; i < m_vecpExplosions.size(); i++)
	{
		if (rand() % 200 == 0)
		{
			CExplosion* Explosion = m_vecpExplosions[0];
			m_vecpExplosions.erase(m_vecpExplosions.begin());

			delete Explosion;
			Explosion = nullptr;
		}
	}
	
	for (unsigned int i = 0; i < m_vecpEnemyBullets.size(); i++)
	{
		m_vecpEnemyBullets[i]->Process(_fDeltaTick);
	}
	//handles the mothership
	--s_iMotherShipspawnBuffer;

	if (bMotherShipExists == false && s_iMotherShipspawnBuffer <= 0) {
		int _bFacingDirection = rand() % 2;

		m_pMotherShip = new CMotherShip();
		
		m_pMotherShip->Initialise();

		if (_bFacingDirection == 1)
		{
			m_pMotherShip->m_iDirection = 1;
			m_pMotherShip->SetX(-20);
		}
		else 
		{
			m_pMotherShip->m_iDirection = -1;
			m_pMotherShip->SetX(static_cast<float>(m_iWidth + 20));
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

	m_pBullet = m_pPlayer->GetBullet();

	if (m_pBullet != nullptr)
	{
		bBulletExists = true;
	}

	if (bBulletExists == true)
	{
		m_pBullet->Process(_fDeltaTick);
	}

	
	m_pPlayer->Process(_fDeltaTick);

	ProcessEnemyBulletWallCollision();
	ProcessBulletPlayerCollision(_fDeltaTick);

	if (bBulletExists == true)
	{
		bBulletExists = ProcessBulletWallCollision();
		//ProcessPaddleWallCollison();

		if (bBulletExists == true)
		{
			//ProcessBallPaddleCollision();
			bBulletExists = ProcessBulletEnemyCollision(_fDeltaTick);
			ProcessCheckForWin();
			ProcessBulletBounds();
		}

		if (bBulletExists == true)
		{
			bBulletExists = ProcessBulletMotherShipCollision(_fDeltaTick);
		}

		if (bBulletExists == true)
		{
			bBulletExists = ProcessBulletEnemyBulletCollision(_fDeltaTick);
		}

		if (bBulletExists == true)
		{
			bBulletExists = ProcessBulletBlockBarrierCollision(_fDeltaTick);
		}
	}

	ProcessEnemyBulletBarrierBlockCollision(_fDeltaTick);
	ProcessEnemyBodiesBarrierBlockCollision(_fDeltaTick);
	ProcessCheckForLose();

	//handles aliens shooting
	if (s_iShootFrameBuffer <= 0)
	{
		s_iShootFrameBuffer = rand() % (m_fAlienShootMod);
		//s_iShootFrameBuffer = rand() % (5000 - m_fAlienShootMod * 10) + 500;
		if (AlienShoot((rand() % 12), _fDeltaTick) == false) {
			s_iShootFrameBuffer = 1;
		}
	}

	--s_iShootFrameBuffer;

	// Movement

	bool hitwall = false;
	for (size_t j = 0; j < m_vecEnemies.size(); j++)
	{
		if (m_vecEnemies[j] != nullptr && m_vecEnemies[j]->m_iDirection > 0) // Move left
		{
			if (m_vecEnemies[j]->GetX() + m_vecEnemies[j]->GetWidth() >= m_iWidth)
			{
				hitwall = true;
			}
		
		}
		else if (m_vecEnemies[j] != nullptr && m_vecEnemies[j]->m_iDirection < 0)
		{
			if (m_vecEnemies[j]->GetX() - m_vecEnemies[j]->GetWidth()/2 <= 0)
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

//Get the player member variable
CPlayer*
CLevel::GetPaddle() const
{
	return (m_pPlayer);
}

//Get the enemies vector member variable
std::vector<IEnemy*> CLevel::GetEnemies() const
{
	return m_vecEnemies;
}

//Reset the level. Called after you kill all the enemies and it needs to respawn them
void CLevel::ResetLevel()
{
	while (m_vecEnemies.size() > 0)
	{
		IEnemy* pEnemy = m_vecEnemies[m_vecEnemies.size() - 1];

		m_vecEnemies.pop_back();

		delete pEnemy;
		pEnemy = 0;
	}

	while (m_vecpBarrierBlocks.size() > 0)
	{
		CBarrierBlock* pBarrier = m_vecpBarrierBlocks[m_vecpBarrierBlocks.size() - 1];
		m_vecpBarrierBlocks.pop_back();

		delete pBarrier;
		pBarrier = nullptr;
	}

	while (m_vecpLifeCounters.size() > 0)
	{
		CLifeCount* pLifeCount = m_vecpLifeCounters[m_vecpLifeCounters.size() - 1];
		m_vecpLifeCounters.pop_back();

		delete pLifeCount;
		pLifeCount = nullptr;
	}

	while (m_vecpExplosions.empty() == false)
	{
		CExplosion* pTempExplosion = m_vecpExplosions.back();
		m_vecpExplosions.pop_back();

		delete pTempExplosion;
		pTempExplosion = 0;
	}

	while (m_vecpEnemyBullets.size() != 0)
	{
		CBullet* pEnemyBullet = m_vecpEnemyBullets[m_vecpEnemyBullets.size() - 1];

		m_vecpEnemyBullets.pop_back();

		if (pEnemyBullet != nullptr)
		{
			delete pEnemyBullet;
		}
		pEnemyBullet = nullptr;
	}

	if (m_pBullet != nullptr)
	{
		m_pPlayer->DeleteBullet();
		m_pBullet = nullptr;
		bBulletExists = false;
	}

	if (bMotherShipExists == true)
	{
		delete m_pMotherShip;
		m_pMotherShip = 0;
		bMotherShipExists = false;
	}
}

//Check to see if the player bullet and the top wall collided. destroy bullet if true
bool
CLevel::ProcessBulletWallCollision()
{
	float fBallX = m_pBullet->GetX();
	float fBallY = m_pBullet->GetY();
	float fBallW = m_pBullet->GetWidth();
	float fBallH = m_pBullet->GetHeight();

	float fHalfBallW = fBallW / 2;
	float fHalfBallH = fBallH / 2;

	if (fBallY < fHalfBallH) //represents the situation when the bullet has hit the top wall.
	{
		m_pPlayer->DeleteBullet();
		m_pBullet = nullptr;

		bBulletExists = false;
		return false;
	}
	else
	{
		return true;
	}
}

//Check to see if the enemy bullet and the ground floor collided. destroy bullet if true
void
CLevel::ProcessEnemyBulletWallCollision()
{
	float fBulletX;
	float fBulletY;
	float fBulletW;
	float fBulletH;
	float fHalfBulletW;
	float fHalfBulletH;

	for (size_t i = 0; i < m_vecpEnemyBullets.size(); i++) //cycles through all bullets in the vector
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
		if (fBulletY > (m_iHeight) - fBulletH) //represents the situation when the bullet has hit the bottom wall
		{
			CEnemyBullet* pBullet = m_vecpEnemyBullets.at(i);

			m_vecpEnemyBullets.erase(m_vecpEnemyBullets.begin() + i);

			//m_vecpEnemyBullets.at(i) = nullptr;

			delete pBullet;
			pBullet = nullptr;
		}
	}
}

//Check to see if the player bullet and an enemy bullet collided. destroy both if true
bool CLevel::ProcessBulletEnemyBulletCollision(float _fDeltaTick) {
	for (unsigned int i = 0; i < m_vecpEnemyBullets.size(); ++i) // cycles through all bullets in the vector
	{
		float fEnemyBulletR = m_vecpEnemyBullets[i]->GetRadius();

		float fEnemyBulletX = m_vecpEnemyBullets[i]->GetX();
		float fEnemyBulletY = m_vecpEnemyBullets[i]->GetY();

		float fBulletX = m_pBullet->GetX();
		float fBulletY = m_pBullet->GetY();

		float fBulletR = m_pBullet->GetRadius();

		if ((fEnemyBulletX + fEnemyBulletR > fBulletX - fBulletR / 2) &&
			(fEnemyBulletX - fEnemyBulletR < fBulletX + fBulletR / 2) &&
			(fEnemyBulletY + fEnemyBulletR > fBulletY - fBulletR / 2) &&
			(fEnemyBulletY - fEnemyBulletR < fBulletY + fBulletR / 2))
		{
			//Hit the front side of the bullet...
			m_vecpEnemyBullets[i]->SetY((fBulletY + fBulletR / 2.0f) + fEnemyBulletR);
			m_vecpEnemyBullets[i]->SetVelocityY(m_vecpEnemyBullets[i]->GetVelocityY() * -1);

			m_pBullet->SetY((fEnemyBulletX + fEnemyBulletR / 2.0f) + fBulletR);
			m_pBullet->SetVelocityY(m_pBullet->GetVelocityY() * -1);

			delete m_pBullet;

			m_pBullet = 0;
			m_pPlayer->SetBullet(nullptr);

			CEnemyBullet* pBullet = m_vecpEnemyBullets.at(i);

			m_vecpEnemyBullets.erase(m_vecpEnemyBullets.begin() + i);

			//m_vecpEnemyBullets.at(i) = nullptr;

			//trigger an explosion
			CExplosion* Explosion = new CExplosion(pBullet->GetX(), pBullet->GetY());
			VALIDATE(Explosion->Initialise(_fDeltaTick));
			m_vecpExplosions.push_back(Explosion);

			delete pBullet;
			pBullet = nullptr;
			

			//reduce the player's health
		
			return false;
		}
	}
	return true;
}

//Check to see if an enemy bullet and the player collided
bool CLevel::ProcessBulletPlayerCollision(float _fDeltaTick) {
	for (unsigned int i = 0; i < m_vecpEnemyBullets.size(); ++i)
	{
		if (m_vecpEnemyBullets[i] != nullptr && !m_pPlayer->IsHit())
		{
			float fBulletR = m_vecpEnemyBullets[i]->GetRadius();

			float fBulletX = m_vecpEnemyBullets[i]->GetX();
			float fBulletY = m_vecpEnemyBullets[i]->GetY();

			float fPlayerX = m_pPlayer->GetX();
			float fPlayerY = m_pPlayer->GetY();

			float fPlayerH = m_pPlayer->GetHeight();
			float fPlayerW = m_pPlayer->GetWidth();

			if ((fBulletX + fBulletR > fPlayerX - fPlayerW / 2) &&
				(fBulletX - fBulletR < fPlayerX + fPlayerW / 2) &&
				(fBulletY + fBulletR > fPlayerY - fPlayerH / 2 + 18) && //has a slight offset so the bullet must hit the body of the player, not their turret
				(fBulletY - fBulletR < fPlayerY + fPlayerH / 2))
			{
				//Hit the front side of the brick...
				m_vecpEnemyBullets[i]->SetY((fPlayerY + fPlayerH / 2.0f) + fBulletR);
				m_vecpEnemyBullets[i]->SetVelocityY(m_vecpEnemyBullets[i]->GetVelocityY() * -1);

				CEnemyBullet* pBullet = m_vecpEnemyBullets.at(i);

				m_vecpEnemyBullets.erase(m_vecpEnemyBullets.begin() + i);

				
				//trigger an explosion
				CExplosion* Explosion = new CExplosion(m_pPlayer->GetX(), m_pPlayer->GetY());
				VALIDATE(Explosion->Initialise(_fDeltaTick));
				m_vecpExplosions.push_back(Explosion);
				
				//pBullet = nullptr;
				delete pBullet;
				pBullet = nullptr;
				
				//reduce the player's health
				m_pPlayer->LoseLife();
				if (m_pPlayer->GetLives() == 0)
				{
					//CGame::GetInstance().GameOverLost();
					m_bLoseState = true;
				}
				return false;
			}
		}
	}
	return true;
}

//Check to see if the player bullet and a mothership collided
bool
CLevel::ProcessBulletMotherShipCollision(float _fDeltaTick)
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

			//trigger an explosion
			CExplosion* Explosion = new CExplosion(m_pMotherShip->GetX(), m_pMotherShip->GetY());
			VALIDATE(Explosion->Initialise(_fDeltaTick));
			m_vecpExplosions.push_back(Explosion);
			
			delete m_pBullet;
			m_pPlayer->SetBullet(nullptr);

			delete m_pMotherShip;
			m_pMotherShip = nullptr;

			SetScore(GetScore()+ ((rand() % 3)+1)*100);
			bMotherShipExists = false;
			return false;
		}
	}
	return true;
}

//Check to see if the player bullet and an enemy collided
bool
CLevel::ProcessBulletEnemyCollision(float _fDeltaTick)
{
	for (unsigned int i = 0; i < m_vecEnemies.size(); ++i)
	{
		if (m_vecEnemies[i] != nullptr && !m_vecEnemies[i]->IsHit())
		{
			float fBulletWidth = m_pBullet->GetRadius();
			float fBulletHeight = m_pBullet->GetHeight()/2;

			float fBulletX = m_pBullet->GetX();
			float fBulletY = m_pBullet->GetY();

			float fEnemyX = m_vecEnemies[i]->GetX();
			float fEnemyY = m_vecEnemies[i]->GetY();

			float fEnemyH = m_vecEnemies[i]->GetHeight();
			float fEnemyW = m_vecEnemies[i]->GetWidth();

			if ((fBulletX + fBulletWidth > fEnemyX - fEnemyW / 2 + 20) &&
				(fBulletX - fBulletWidth < fEnemyX + fEnemyW / 2) &&
				(fBulletY + fBulletHeight > fEnemyY - fEnemyH / 2) &&
				(fBulletY - fBulletHeight < fEnemyY + fEnemyH / 2))
			{
				//Hit the front side of the brick...
				m_pBullet->SetY((fEnemyY + fEnemyH / 2.0f) + fBulletWidth);
				m_pBullet->SetVelocityY(m_pBullet->GetVelocityY() * -1);
				
				//IEnemy* pEnemy = m_vecEnemies[i];

				//m_vecEnemies.erase(m_vecEnemies.begin() + i);

				SetScore(m_vecEnemies[i]->GetPoints() + GetScore());

				IEnemy* pEnemy = m_vecEnemies[i];

				//trigger an explosion
				CExplosion* Explosion = new CExplosion(pEnemy->GetX(), pEnemy->GetY());
				VALIDATE(Explosion->Initialise(_fDeltaTick));
				m_vecpExplosions.push_back(Explosion);

				delete pEnemy;

				m_vecEnemies[i] = nullptr;

				//delete pEnemy;

				delete m_pBullet;
				m_pPlayer->SetBullet(nullptr);

				for (unsigned int j = 0; j < m_vecEnemies.size(); j++)
				{
					if (m_vecEnemies[j] != nullptr)
					{
						m_vecEnemies[j]->m_fSpeed *= 0.97f;
						if (m_vecEnemies[j]->m_pAnim != nullptr)
						{
							m_vecEnemies[j]->m_pAnim->SetSpeed(m_vecEnemies[j]->m_fSpeed);
						}
					}
				}

				return false;
			}
		}
	}
	return true;

}

//Check to see if an enemy bullet and a barrier block collided. destroy both if true
bool 
CLevel::ProcessEnemyBulletBarrierBlockCollision(float _fDeltaTick)
{
	for (unsigned int barrier = 0; barrier < m_vecpBarrierBlocks.size(); ++barrier)
	{
		for (unsigned int bullet = 0; bullet < m_vecpEnemyBullets.size(); ++bullet)
		{
			if (m_vecpBarrierBlocks[barrier] != nullptr && m_vecpEnemyBullets[bullet] != nullptr)
			{
				float fBulletR = m_vecpEnemyBullets[bullet]->GetRadius();
				float fBulletX = m_vecpEnemyBullets[bullet]->GetX();
				float fBulletY = m_vecpEnemyBullets[bullet]->GetY();

				float fBarrierH = m_vecpBarrierBlocks[barrier]->GetHeight();
				float fBarrierW = m_vecpBarrierBlocks[barrier]->GetWidth();
				float fBarrierX = m_vecpBarrierBlocks[barrier]->GetX();
				float fBarrierY = m_vecpBarrierBlocks[barrier]->GetY();

				if ((fBulletX + fBulletR > fBarrierX - fBarrierW / 2) &&
					(fBulletX - fBulletR < fBarrierX + fBarrierW / 2) &&
					(fBulletY + fBulletR > fBarrierY - fBarrierH / 2) &&
					(fBulletY - fBulletR < fBarrierY + fBarrierH / 2))
				{
					//Hit the front side of the barrier...
					m_vecpEnemyBullets[bullet]->SetY((fBarrierY + fBarrierH / 2.0f) + fBulletR);
					m_vecpEnemyBullets[bullet]->SetVelocityY(m_vecpEnemyBullets[bullet]->GetVelocityY() * -1);

					CBarrierBlock* pBarrier = m_vecpBarrierBlocks.at(barrier);

					//m_vecpBarrierBlocks.erase(m_vecpBarrierBlocks.begin() + barrier);


					//trigger an explosion
					CExplosion* Explosion = new CExplosion(pBarrier->GetX(), pBarrier->GetY());
					VALIDATE(Explosion->Initialise(_fDeltaTick));
					m_vecpExplosions.push_back(Explosion);

					m_vecpBarrierBlocks.at(barrier) = nullptr;

					delete pBarrier;
					pBarrier = nullptr;

					CEnemyBullet* pBullet = m_vecpEnemyBullets.at(bullet);

					m_vecpEnemyBullets.erase(m_vecpEnemyBullets.begin() + bullet);

					//pBullet = nullptr;
					delete pBullet;
					pBullet = nullptr;
				}
			}

		}
	}

	return true;
}

//Check to see if an enemy body and an block collided. destroy the barrier if true
bool
CLevel::ProcessEnemyBodiesBarrierBlockCollision(float _fDeltaTick)
{
	for (unsigned int barrier = 0; barrier < m_vecpBarrierBlocks.size(); ++barrier)
	{
		for (unsigned int enemy = 0; enemy < m_vecEnemies.size(); ++enemy)
		{
			if (m_vecpBarrierBlocks[barrier] != nullptr && m_vecEnemies[enemy] != nullptr && !m_vecEnemies[enemy]->IsHit())
			{
				float fEnemyR = m_vecEnemies[enemy]->GetWidth()/2;
				float fEnemyX = m_vecEnemies[enemy]->GetX();
				float fEnemyY = m_vecEnemies[enemy]->GetY();

				float fBarrierH = m_vecpBarrierBlocks[barrier]->GetHeight();
				float fBarrierW = m_vecpBarrierBlocks[barrier]->GetWidth();
				float fBarrierX = m_vecpBarrierBlocks[barrier]->GetX();
				float fBarrierY = m_vecpBarrierBlocks[barrier]->GetY();

				if ((fEnemyX + fEnemyR > fBarrierX - fBarrierW / 2) &&
					(fEnemyX - fEnemyR < fBarrierX + fBarrierW / 2) &&
					(fEnemyY + fEnemyR > fBarrierY - fBarrierH / 2) &&
					(fEnemyY - fEnemyR < fBarrierY + fBarrierH / 2))
				{

					CBarrierBlock* pBarrier = m_vecpBarrierBlocks.at(barrier);

					//trigger an explosion
					CExplosion* Explosion = new CExplosion(pBarrier->GetX(), pBarrier->GetY());
					VALIDATE(Explosion->Initialise(_fDeltaTick));
					m_vecpExplosions.push_back(Explosion);

					m_vecpBarrierBlocks.at(barrier) = nullptr;

					delete pBarrier;
					pBarrier = nullptr;
				}
			}

		}
	}

	return true;
}


//Check to see if the player bullet and a barrier block collided. destroy both if true
bool
CLevel::ProcessBulletBlockBarrierCollision(float _fDeltaTick)
{
	for (unsigned int i = 0; i < m_vecpBarrierBlocks.size(); ++i)
	{
		if (m_vecpBarrierBlocks[i] != nullptr)
		{
			float fBulletWidth = m_pBullet->GetRadius();

			float fBulletX = m_pBullet->GetX();
			float fBulletY = m_pBullet->GetY();

			float fBlockX = m_vecpBarrierBlocks[i]->GetX();
			float fBlockY = m_vecpBarrierBlocks[i]->GetY();

			float fBlockH = m_vecpBarrierBlocks[i]->GetHeight();
			float fBlockW = m_vecpBarrierBlocks[i]->GetWidth();

			if ((fBulletX + fBulletWidth > fBlockX - fBlockW / 2) &&
				(fBulletX - fBulletWidth < fBlockX + fBlockW / 2) &&
				(fBulletY + fBulletWidth > fBlockY - fBlockH / 2) &&
				(fBulletY - fBulletWidth < fBlockY + fBlockH / 2))
			{
				//Hit the front side of the brick...
				m_pBullet->SetY((fBlockY + fBlockH / 2.0f) + fBulletWidth);
				m_pBullet->SetVelocityY(m_pBullet->GetVelocityY() * -1);

				//IEnemy* pEnemy = m_vecEnemies[i];

				//m_vecEnemies.erase(m_vecEnemies.begin() + i);

				CBarrierBlock* pBlock = m_vecpBarrierBlocks[i];

				//trigger an explosion
				CExplosion* Explosion = new CExplosion(pBlock->GetX(), pBlock->GetY());
				VALIDATE(Explosion->Initialise(_fDeltaTick));
				m_vecpExplosions.push_back(Explosion);


				m_vecpBarrierBlocks[i] = nullptr;

				delete pBlock;

				//delete pEnemy;

				delete m_pBullet;
				m_pPlayer->SetBullet(nullptr);

				return false;
			}
		}
	}
	return true;

}

//check if the aliens have touched the player or reached a certain distance at the bottom of the screen
void
CLevel::ProcessCheckForLose()
{
	for (unsigned int i = 0; i < m_vecEnemies.size(); ++i)
	{

		if (m_vecEnemies[i] != nullptr && !m_vecEnemies[i]->IsHit())
		{
			float fEnemyR = m_vecEnemies[i]->GetWidth()/2;

			float fEnemyX = m_vecEnemies[i]->GetX();
			float fEnemyY = m_vecEnemies[i]->GetY();

			float fPlayerX = m_pPlayer->GetX();
			float fPlayerY = m_pPlayer->GetY();

			float fPlayerH = m_pPlayer->GetHeight();
			float fPlayerW = m_pPlayer->GetWidth();

			if ((fEnemyX + fEnemyR > fPlayerX - fPlayerW / 2) &&
				(fEnemyX - fEnemyR < fPlayerX + fPlayerW / 2) &&
				(fEnemyY + fEnemyR > fPlayerY - fPlayerH / 2 + 18) &&
				(fEnemyY - fEnemyR < fPlayerY + fPlayerH / 2) || m_vecEnemies[i]->GetY() > m_iHeight - 60)
			{
				while (m_pPlayer->GetLives() > 0)
				{
					m_pPlayer->LoseLife();
					if (m_pPlayer->GetLives() == 0)
					{
						m_bLoseState = true;
					}
				}
			}
		}
	}
}

//check if all aliens have died. Calls reset level if they have and increases starting speed of the enemy movement
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

	ResetLevel();

	//m_pPlayer->SetHealth(3);
	CLevel::Initialise(m_iWidth, m_iHeight);
	m_fSpeedModifier *= 0.7f;
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
		//m_pPlayer->SetBullet(nullptr);
		m_pPlayer->DeleteBullet();

		bBulletExists = false;
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

CBullet * CLevel::GetPlayerBullet()
{
	return m_pBullet;
}

CPlayer * CLevel::GetPlayer()
{
	return m_pPlayer;
}

bool CLevel::GetLoseState()
{
	return m_bLoseState;
}

void CLevel::SetLoseState(bool _bLoseState)
{
	m_bLoseState = _bLoseState;
}


void CLevel::DrawHealth()
{
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();
	const int kiX = 0;
	const int kiY = m_iHeight - 28;
	SetBkMode(hdc, TRANSPARENT);

	TextOutA(hdc, kiX, kiY, "Health:", 7);

	for (int i = 0; i < m_pPlayer->GetLives(); ++i)
	{
		m_vecpLifeCounters[i]->Draw();
	}
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

void
CLevel::SetEnemySpeed(float Speed)
{
	for (unsigned int i = 0; i < m_vecEnemies.size(); ++i)
	{
		if (m_vecEnemies.at(i) != nullptr)
		{
			m_vecEnemies.at(i)->SetSpeed(Speed);
			m_vecEnemies.at(i)->m_pAnim->SetSpeed(Speed);
		}
	}
}
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

#pragma once

#if !defined(__LEVEL_H__)
#define __LEVEL_H__

// Library Includes
#include <vector>
#include <string>

// Local Includes
#include "entity.h"
// Types

// Constants

// Prototypes
class CBullet;
class CEnemyBullet;
class CPlayer;
class CExplosion;
class CBarrierBlock;
//class CMotherShip;
class IEnemy;
class CFPSCounter;
class CBackGround;

class CLevel
{
	// Member Functions
public:
	CLevel();
	virtual ~CLevel();

	virtual bool Initialise(int _iWidth, int _iHeight);

	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	void SetAlienShootSpeed(int _fAlienShootMod);

	CPlayer* GetPaddle() const;

	int GetBricksRemaining() const;

	void SetPlayerBulletSpeed(int _fPlayerBulletSpeed);

protected:
	bool ProcessBulletWallCollision();
	//void ProcessPaddleWallCollison();
	// void ProcessBallPaddleCollision();
	bool ProcessBulletPlayerCollision(float _fDeltaTick);
	void ProcessEnemyBulletWallCollision();
	bool ProcessBulletEnemyCollision(float _fDeltaTick);
	bool ProcessBulletMotherShipCollision(float _fDeltaTick);
	bool ProcessBulletEnemyBulletCollision(float _fDeltaTick);
	bool ProcessBulletBlockBarrierCollision(float _fDeltaTick);
	//void ProcessPlayerWallCollison();
	//	bool ProcessBulletEnemyCollision();

	void ProcessCheckForWin();

	void ProcessBulletBounds();

	void UpdateScoreText();
	void DrawScore();
	void DrawFPS();

	void SetScore(int _i);
	int GetScore();

private:
	CLevel(const CLevel& _kr);
	CLevel& operator= (const CLevel& _kr);

	// Member Variables
public:
	CBullet* GetPlayerBullet();
	CPlayer* GetPlayer();
protected:
	CBullet* m_pBullet;
	CBackGround* m_pBackground;
	CPlayer* m_pPlayer;
	IEnemy* m_pMotherShip;
	std::vector<IEnemy*> m_vecEnemies;
	std::vector<bool> m_vecbAlienColumns = { true , true ,true, true, true, true, true, true, true, true, true, true };
	std::vector<CEnemyBullet*> m_vecpEnemyBullets;
	std::vector<CExplosion*> m_vecpExplosions;
	std::vector<CBarrierBlock*> m_vecpBarrierBlocks;
	CFPSCounter* m_fpsCounter;

	int m_iWidth;
	int m_iHeight;

	float m_fDeltaTick;

	int m_iEnemyRemaining;

	std::string m_strScore;

private:
	bool bBulletExists;
	bool bMotherShipExists;
	bool AlienShoot(int _iStack, float _fDeltaTick);
	float m_fTime;
	int m_iScore;
	float m_fSpeedModifier;

	//Debug values
	int m_fAlienShootMod;
};

#endif    // __LEVEL_H__

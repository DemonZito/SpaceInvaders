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

// Types

// Constants

// Prototypes
class CBullet;
class CEnemyBullet;
class CPlayer;
class CMotherShip;
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

	CPlayer* GetPaddle() const;

	int GetBricksRemaining() const;

protected:
	bool ProcessBulletWallCollision();
	//void ProcessPaddleWallCollison();
	// void ProcessBallPaddleCollision();
	void ProcessEnemyBulletWallCollision();
	bool ProcessBulletEnemyCollision();
	bool ProcessBulletMotherShipCollision();
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
	CBullet* m_pBullet;
protected:
	CBackGround* m_pBackground;
	CPlayer* m_pPlayer;
	CMotherShip* m_pMotherShip;
	std::vector<IEnemy*> m_vecEnemies;
	std::vector<bool> m_vecbAlienColumns = { true , true ,true, true, true, true, true, true, true, true, true, true };
	std::vector<CEnemyBullet*> m_vecpEnemyBullets;
	CFPSCounter* m_fpsCounter;

	int m_iWidth;
	int m_iHeight;

	int m_iEnemyRemaining;

	std::string m_strScore;

private:
	bool bBulletExists;
	bool bMotherShipExists;
	bool AlienShoot(int _iStack, float _fDeltaTick);
	float m_fTime;
	int m_iScore;
	float m_fSpeedModifier;
	int m_fAlienShootMod;
};

#endif    // __LEVEL_H__

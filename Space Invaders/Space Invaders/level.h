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
class CPlayer;
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
    void ProcessBallWallCollision();
	void ProcessPaddleWallCollison();
    void ProcessBallPaddleCollision();
    bool ProcessBallBrickCollision();

    void ProcessCheckForWin();

    void ProcessBallBounds();

    void UpdateScoreText();
    void DrawScore();
	void DrawFPS();

    void SetBricksRemaining(int _i);

private:
    CLevel(const CLevel& _kr);
    CLevel& operator= (const CLevel& _kr);

    // Member Variables
public:

protected:
	CBackGround* m_pBackground;
    CBullet* m_pBall;
    CPlayer* m_pPaddle;
    std::vector<IEnemy*> m_vecBricks;
	CFPSCounter* m_fpsCounter;

    int m_iWidth;
    int m_iHeight;

    int m_iBricksRemaining;

    std::string m_strScore;

private:
	bool bBulletExists;
};

#endif    // __LEVEL_H__

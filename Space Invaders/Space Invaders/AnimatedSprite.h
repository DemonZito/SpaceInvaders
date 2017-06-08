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

#if !defined(__ANIMATEDSPRITE_H__)
#define __ANIMATEDSPRITE_H__

// Library Includes
#include <vector>
#include "windows.h"

// Local Includes
#include "Sprite.h"

// Types

// Constants

// Prototypes
class CAnimatedSprite : public CSprite
{
	// Member Variables
public:

	void SetCurSprite(int);


protected:
	std::vector<int> m_vectorFrames;

	int m_iCurrentSprite;

	int m_iFrameWidth;

	float m_fFrameSpeed;
	float m_fTimeElapsed;

private:

	// Member Functions
public:
	CAnimatedSprite();
	virtual ~CAnimatedSprite();

	virtual bool Deinitialise();
	virtual bool Initialise(int _iResourceID, int _iMaskResourceID);

	virtual void DrawAnimated();
	virtual void Process(float _fDeltaTick);

	void AddFrame(int _iX);
	void SetSpeed(float _fSpeed);

	void SetWidth(int _iW);
	int GetWidth();


	int GetFrameWidth();
	int GetHeight();

protected:

private:

};

#endif	// __ANIMATEDSPRITE_H__


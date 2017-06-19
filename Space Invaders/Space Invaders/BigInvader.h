//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: BigInvader.h
// Description	: Header file for the big invader, the highest scoring aleins at the top of the block
// Author		: Madeleine Day Jack Mair
// Mail			: jack.mair@mediadesign.school.nz
//
#pragma once

#if !defined(__BIGINVADER_H__)
#define __BIGINVADER_H__

#include "enemy.h"

//class CAnimatedSprite;

class CBigInvader : public IEnemy
{
public:
	~CBigInvader();
	bool Initialise();
	int GetPoints();
	void Draw();
	//void Process(float _fDeltaTick);
private:
};
#endif


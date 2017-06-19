//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: MediumInvader.h
// Description	: Header file for the medium invaders, aliens that appear in the middle of the alien stack
// Author		: Madeleine Day Jack Mair
// Mail			: jack.mair@mediadesign.school.nz
//
#pragma once

#if !defined(__MEDIUMINVADER_H__)
#define __MEDIUMINVADER_H__

#include "enemy.h"

class CMediumInvader : public IEnemy
{
public:
	~CMediumInvader();
	bool Initialise();
	int GetPoints();
	void Draw();
};

#endif


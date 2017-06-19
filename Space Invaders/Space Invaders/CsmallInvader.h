//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: CSmallInvader.h
// Description	: Header file for the medium invader, the medium scoring aleins at the middle of the block
// Author		: Madeleine Day Jack Mair
// Mail			: jack.mair@mediadesign.school.nz
//
#pragma once

#if !defined(__CSMALLINVADER_H__)
#define __CSMALLINVADER_H__

#include "enemy.h"

class CSmallInvader : public IEnemy
{
public:
	~CSmallInvader();
	bool Initialise();
	int GetPoints();
	void Draw();
};
#endif


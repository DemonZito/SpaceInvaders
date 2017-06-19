//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: clouds.h
// Description	: Header file for the ambient clouds in the background
// Author		: Madeleine Day Jack Mair
// Mail			: jack.mair@mediadesign.school.nz
//
#pragma once

#if !defined(__CLOUDS_H__)
#define __CLOUDS_H__

// Library Includes

// Local Includes
#include "entity.h"

class CClouds : public CEntity
{
public:
	CClouds(const float _iX, const float _iY);
	virtual ~CClouds();

	virtual bool Initialise(float _fDeltaTick);

	virtual void Draw();

	void Process(float _fDeltaTick);
};

#endif    // __CLOUDS_H__


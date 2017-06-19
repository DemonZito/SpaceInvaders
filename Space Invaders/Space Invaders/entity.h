//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: Entity.h
// Description	: Header file for entities, all game objects inheret from this
// Author		: Madeleine Day Jack Mair
// Mail			: jack.mair@mediadesign.school.nz
//

#pragma once

#if !defined(__ENTITY_H__)
#define __ENTITY_H__

// Library Includes

// Local Includes
#include "AnimatedSprite.h"
// Types

// Constants

// Prototypes
class CSprite;
//class CAnimatedSprite;

class CEntity
{
	// Member Functions
public:
	CEntity();
	virtual ~CEntity();

	virtual bool Initialise(const int _kiSpriteID, const int _kiMaskID);

	virtual void Draw() = 0;
	virtual void Process(float _fDeltaTick);

	void SetX(float _f);
	void SetY(float _f);

	float GetX() const;
	float GetY() const;

	float GetHeight() const;
	float GetWidth() const;

	void SetWidth(int _iWidth);
	void SetHeight(int _iHeight);

	CAnimatedSprite* m_pAnim;

protected:

private:
	CEntity(const CEntity& _kr);
	CEntity& operator= (const CEntity& _kr);

	// Member Variables
public:

protected:
	CSprite* m_pSprite;
	

	
	float m_fX;
	float m_fY;

private:

};


#endif    // __ENTITY_H__

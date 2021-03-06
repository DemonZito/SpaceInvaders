//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: sprite.h
// Description	: Header file for the sprite, non-animated entities use this for their sprite
// Author		: Madeleine Day Jack Mair
// Mail			: jack.mair@mediadesign.school.nz
//

#pragma once

#if !defined(__SPRITE_H__)
#define __SPRITE_H__

// Library Includes
#include "windows.h"

// Local Includes

// Types

// Constants

// Prototypes
class CSprite
{
    // Member Functions
public:
    CSprite();
    ~CSprite();

    bool Initialise(int _iResourceID, int _iMaskResourceID);
	bool Deinitialise();

    void Draw();
    void Process(float _fDeltaTick);

    virtual int GetWidth() const;
    virtual int GetHeight() const;

	void SetWidth(int _iWidth);
	void SetHeight(int _iHeight);

    int GetX() const;
    int GetY() const;
    void SetX(int _i);
    void SetY(int _i);

    void TranslateRelative(int _iX, int _iY);
    void TranslateAbsolute(int _iX, int _iY);

	void SetDestSizeW(int _iSizeW);
	void SetDestSizeH(int _iSizeH);

protected:


private:
    CSprite(const CSprite& _kr);
    CSprite& operator= (const CSprite& _kr);

    // Member Variables
public:

protected:
    //Center handle
    int m_iX;
    int m_iY;

    HBITMAP m_hSprite;
    HBITMAP m_hMask;

    BITMAP m_bitmapSprite;
    BITMAP m_bitmapMask;

    static HDC s_hSharedSpriteDC;
    static int s_iRefCount;

private:
	int m_iDestSizeW = 0;
	int m_iDestSizeH = 0;
};

#endif    // __SPRITE_H__

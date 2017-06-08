#pragma once
#include "enemy.h"

//class CAnimatedSprite;

class CBigInvader : public IEnemy
{
public:

	bool Initialise();
	int GetPoints();
	void Draw();
	//void Process(float _fDeltaTick);
private:
};


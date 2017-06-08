#pragma once
#include "enemy.h"

class CMediumInvader : public IEnemy
{
public:
	~CMediumInvader();
	bool Initialise();
	int GetPoints();
	void Draw();
};


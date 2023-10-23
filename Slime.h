#pragma once
#include "EnemyBase.h"
class Slime :public EnemyBase
{
private:

public:
	Slime();

	void Update();
	void Draw();

	void X();
	void Y();
};


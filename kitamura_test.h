#pragma once

#include "scene.h"
#include "weapon.h"
#include "Player.h"

class kitamura_test : public Scene{
private:
	int state = 0; // ó‘Ô
	weapon wp;
	Player p;
public:
	kitamura_test() {
		state = 0;
	};

	~kitamura_test() {};

	virtual Scene* update() override;

	virtual void draw() const override;

};


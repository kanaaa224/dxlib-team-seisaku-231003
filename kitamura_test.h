#pragma once

#include "scene.h"
#include "weapon.h"

class kitamura_test : public Scene{
private:
	int state = 0; // ó‘Ô
	weapon wp;
public:
	kitamura_test() {
		state = 0;
	};

	~kitamura_test() {};

	virtual Scene* update() override;

	virtual void draw() const override;

};


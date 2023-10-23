#include"scene_weapon.h"
#include"inputCtrl.h"

Weapon_Selection::Weapon_Selection()
{
	interval = 0;
	cursor_num = 0;
	cursor_x = 0;
}

Weapon_Selection::~Weapon_Selection()
{

}

Scene* Weapon_Selection::update()
{

	return this;
}

void Weapon_Selection::draw() const
{

}

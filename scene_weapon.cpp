#include"scene_weapon.h"
#include"inputCtrl.h"
#include"weapon.h"

Weapon_Selection::Weapon_Selection()
{
	interval = 0;
	cursor_num = 0;
	cursor_x = 0;

	sword_image = LoadGraph("resources/images/game_ken.png");
	cursor_image = LoadGraph("resources/images/computer_cursor_finger_black.png");
}

Weapon_Selection::~Weapon_Selection()
{

}

void Weapon_Selection::update(weapon* _weapon, bool &flg)
{

	if (interval < INTERVAL)
	{
		interval++;
	}

	cursor_x = cursor_num * 300;

	if (InputCtrl::GetStickRatio(L).x > 0.8 && interval >= 15)
	{
		cursor_num++;
		interval = 0;
		if (cursor_num >= SELECT_WEAPON)
		{
			cursor_num = 0;
		}
	}

	if (InputCtrl::GetStickRatio(L).x < -0.8 && interval >= 15)
	{
		cursor_num--;
		interval = 0;
		if (cursor_num < 0)
		{
			cursor_num = SELECT_WEAPON - 1;
		}
	}

	if (InputCtrl::GetButtonState(XINPUT_BUTTON_A))
	{
		if (cursor_num == 0)
		{
			_weapon->SetWeaponType(dagger);
			flg = true;
		}
		else if (cursor_num == 1)
		{
			_weapon->SetWeaponType(sword);
			flg = true;
		}
		else
		{
			_weapon->SetWeaponType(greatSword);
			flg = true;
		}
	}
}

void Weapon_Selection::draw() const
{
	DrawRotaGraph(400, 200, .5f, .25f, sword_image, TRUE);
	DrawRotaGraph(700, 200, .5f, .25f, sword_image, TRUE);
	DrawRotaGraph(1000, 200, .5f, .25f, sword_image, TRUE);

	DrawRotaGraph(200 + cursor_x, 700, 1.f, .25f, cursor_image, TRUE);
}

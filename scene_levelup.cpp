#include "scene_levelup.h"

WeaponLevelUp::WeaponLevelUp()
{
	test = 0;
}

WeaponLevelUp::~WeaponLevelUp()
{

}

// 更新
void WeaponLevelUp::update()
{
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_Y) == PRESS)
	{
		test++;
	}

}

// 描画
void WeaponLevelUp::draw() const
{
	DrawBox(0, 0, 960, 600, 0xa0a0a0, TRUE);
	SetFontSize(30);
	DrawFormatString(100, 300, 0x000000, "レベルアップ");
	DrawFormatString(0, 0, 0x000000, "test : %d", test);

}

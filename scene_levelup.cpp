#include "scene_levelup.h"

WeaponLevelUp::WeaponLevelUp()
{
	test = 0;
	initial_cursor_position = 0;
}

WeaponLevelUp::~WeaponLevelUp()
{

}

// 更新
void WeaponLevelUp::update()
{
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS)
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
	SetFontSize(20);
	DrawFormatString(0, 0, 0x000000, "Xボタン：閉じる");
	DrawFormatString(0, 20, 0x000000, "Aボタン：加算");
	DrawFormatString(0, 40, 0x000000, "test : %d", test);

}

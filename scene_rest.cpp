#include"scene_rest.h"
#include"inputCtrl.h"
#include"Player.h"

Rest::Rest()
{
	interval = 0;
	cursor_num = 0;


	cursor_image = LoadGraph("resources/images/computer_cursor_finger_black.png");
	bonfire_image = LoadGraph("resources/images/bonfire.png");
}

Rest::~Rest()
{

}

void Rest::update(Player* player, bool& flg)
{
	if (interval < 60)
	{
		interval++;
	}
	else
	{
		interval = 0;
	}

	if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS || InputCtrl::GetKeyState(KEY_INPUT_SPACE) == PRESS)
	{
		if (cursor_num == 0)
		{
			player->SetPlayer_HP(-100);
			flg = true;
		}
	}

}

void Rest::draw() const
{
	DrawGraph(650, 450, bonfire_image, FALSE);

	DrawGraph(700, 600, cursor_image, FALSE);
	SetFontSize(32);
	DrawString(750, 600, "‹xŒe‚·‚é", 0xffffff);
	SetFontSize(16);
}

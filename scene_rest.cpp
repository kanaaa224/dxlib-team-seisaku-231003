#include"scene_rest.h"
#include"main.h"
#include"Player.h"

Rest::Rest()
{
	interval = 0;
	cursor_num = 0;


	cursor_image = LoadGraph("resources/images/computer_cursor_finger_black.png");
	bonfire_image = LoadGraph("resources/images/bonfire.png");
	button_image = LoadGraph("resources/images/button_a.png");

	is_select = false;
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
			if (interval > 1)
			{
				player->SetPlayer_HP(-100);
				is_select = true;

			}
		}
	}
	
	if (is_select)
	{
		if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS || InputCtrl::GetKeyState(KEY_INPUT_SPACE) == PRESS)
		{
			flg = true;
		}
	}

}

void Rest::draw() const
{
	DrawRotaGraph(640, 300, .7f, 0, bonfire_image, TRUE);
	DrawRotaGraph(480, 630, .5f, 1.6f, cursor_image, TRUE);
	DrawGraph(1150, 650, button_image, TRUE);
	DrawString(1194, 662, "Œˆ’è\n", 0xffffff);

	if (is_select != true)
	{
		SetFontSize(48);
		DrawString(570, 600, "‹xŒe‚·‚é", 0xffffff);
		SetFontSize(16);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 230);
		DrawBox(0, (SCREEN_WIDTH / 3), SCREEN_WIDTH, (SCREEN_HEIGHT / 3) * 2, 0x000000, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		SetFontSize(48);
		DrawString((SCREEN_WIDTH / 2) - 48 * 5, (SCREEN_HEIGHT / 2), "HP‚ª‘S‰ñ•œ‚µ‚Ü‚µ‚½", 0xffffff);
		SetFontSize(16);
	}
}

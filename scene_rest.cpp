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
	DrawRotaGraph(640, 400, .7f, 0, bonfire_image, TRUE);
	DrawRotaGraph(480, 630, .5f, 1.6f, cursor_image, TRUE);
	SetFontSize(48);
	DrawString(570, 600, "‹xŒe‚·‚é", 0xffffff);
	SetFontSize(16);
}

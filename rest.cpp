//#include "rest.h"
#include "main.h"

//#include"Player.h"
//#include"game_ui.h"

Rest::Rest(GameUI* ui)
{
	this->ui = ui;

	cursor_interval = 0;
	interval = 0;
	cursor_num = 0;


	cursor_image = LoadGraph("resources/images/computer_cursor_finger_black.png");
	bonfire_image = LoadGraph("resources/images/bonfirelit.png");
	button_image = LoadGraph("resources/images/button_a.png");

	SoundManager::SetBGM("bgm_breakstage");
	SoundManager::SetBGM("bgm_breaktime");
	SoundManager::SetVolumeBGM("bgm_breaktime", 50);

	is_select = false;
	is_ok = false;
	rest_buf_flg = false;
}

Rest::~Rest()
{
	DeleteGraph(cursor_image);
	DeleteGraph(bonfire_image);
	DeleteGraph(button_image);
}

void Rest::update(Player* player, int& mode, int& stage)
{
	SoundManager::PlaySoundBGM("bgm_breakstage");
	SoundManager::PlaySoundBGM("bgm_breaktime");

	ui->setHP(player->GetPlayer_HP(), 100, (int)(player->GetPlayer_HP()));
	ui->update();

	cursor_x = cursor_num * 400;

	if (cursor_interval < 15)
	{
		cursor_interval++;
	}

	if (is_select)
	{
		if (interval < 120)
		{
			interval++;
		}
		else
		{
			is_ok = true;
			stage++;
			mode = GameSceneMode::map;
			Init();
			SoundManager::StopSoundBGMs();
		}
	}
	else
	{
		//左スティックを右に
		if ((InputCtrl::GetStickRatio(L).x > 0.8 || InputCtrl::GetButtonState(XINPUT_BUTTON_DPAD_RIGHT)) && cursor_interval >= 15)
		{
			cursor_num++;
			cursor_interval = 0;
			if (cursor_num > 1)
			{
				cursor_num = 0;
			}
		}

		//左スティックを左に
		if ((InputCtrl::GetStickRatio(L).x < -0.8 || InputCtrl::GetButtonState(XINPUT_BUTTON_DPAD_LEFT)) && cursor_interval >= 15)
		{
			cursor_num--;
			cursor_interval = 0;
			if (cursor_num < 0)
			{
				cursor_num = 1;
			}
		}

		if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS || InputCtrl::GetKeyState(KEY_INPUT_SPACE) == PRESS)
		{
			if (cursor_num == 0)
			{
				player->SetPlayer_HP(-100);
				is_select = true;
			}
			else if (cursor_num == 1);
			{
				rest_buf_flg = true;
				is_select = true;
			}
		}

	}
}

void Rest::draw() const
{
	ui->drawHP();

	DrawRotaGraph(640, 300, .7f, 0, bonfire_image, TRUE);
	DrawRotaGraph(280 + cursor_x, 630, .5f, 1.6f, cursor_image, TRUE);
	DrawGraph(1150, 650, button_image, TRUE);
	DrawString(1194, 662, "決定\n", 0xffffff);

	if (is_select != true)
	{
		SetFontSize(48);
		DrawString(370, 600, "休憩する", 0xffffff);
		DrawString(770, 600, "祈る", 0xffffff);
		SetFontSize(16);
	}
	else
	{
		if (cursor_num == 0)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 230);
			DrawBox(0, (SCREEN_HEIGHT / 3), SCREEN_WIDTH, (SCREEN_HEIGHT / 3) * 2, 0x000000, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			SetFontSize(48);
			DrawString((SCREEN_WIDTH / 2) - 48 * 4.5, (SCREEN_HEIGHT / 2) - 24, "HPが全回復しました", 0xffffff);
			SetFontSize(16);
		}
		else if (cursor_num == 1)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 230);
			DrawBox(0, (SCREEN_HEIGHT / 3), SCREEN_WIDTH, (SCREEN_HEIGHT / 3) * 2, 0x000000, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			SetFontSize(48);
			DrawString((SCREEN_WIDTH / 2) - 48 * 4.5, (SCREEN_HEIGHT / 2) - 24, "バフを獲得しました", 0xffffff);
			SetFontSize(16);
		}
	}
}

void Rest::Init()
{
	interval = 0;

	is_select = false;
	is_ok = false;

}

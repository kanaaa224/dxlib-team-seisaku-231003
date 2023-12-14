//#include "rest.h"
#include "main.h"

//#include"Player.h"
//#include"game_ui.h"

Rest::Rest()
{
	cursor_interval = 0;
	scene_interval = 0;
	select_interval = 0;
	cursor_num = 0;
	anim_cnt = 0;
	bonfire_anim = 0;

	cursor_image = LoadGraph("resources/images/武器/片手剣.png");
	for (int i = 0; i < 4; i++)
	{
		string path = "resources/images/Rest/bonfire0" + std::to_string(i) + ".png";
		bonfire_image[i] = LoadGraph(path.c_str());
	}
	button_image = LoadGraph("resources/images/button_a.png");

	logo_dicision_image = LoadGraph("resources/images/Logo/UI/logo_dicision.png");
	logo_rest_image = LoadGraph("resources/images/Logo/UI/logo_rest.png");
	logo_pray_image = LoadGraph("resources/images/Logo/UI/logo_pray.png");
	logo_cure_image = LoadGraph("resources/images/Logo/UI/logo_cure.png");
	logo_buf_image = LoadGraph("resources/images/Logo/UI/logo_buf.png");

	is_select = false;
	rest_buf_flg = false;
}

Rest::~Rest()
{
	DeleteGraph(cursor_image);
	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(bonfire_image[i]);
	}
	DeleteGraph(button_image);
	DeleteGraph(logo_dicision_image);
	DeleteGraph(logo_rest_image);
	DeleteGraph(logo_pray_image);
	DeleteGraph(logo_cure_image);
	DeleteGraph(logo_buf_image);
}

void Rest::update(Player* player, int& mode, int& stage, int& restCnt,int& hp)
{
	SoundManager::PlaySoundBGM("bgm_breakstage", false);
	SoundManager::PlaySoundBGM("bgm_breaktime", false);

	cursor_x = cursor_num * 445;

	if (++anim_cnt % 7 == 0)
	{
		bonfire_anim++;
		if (bonfire_anim >= 4)
		{
			bonfire_anim = 0;
		}
	}

	if (cursor_interval < 15)
	{
		cursor_interval++;
	}

	if (is_select)
	{
		if (scene_interval < 120)
		{
			scene_interval++;
		}
		else
		{
			stage++;
			mode = GameSceneMode::map;
			Init();
			SoundManager::StopSoundBGMs();
			SoundManager::SetSoundBGMsPosition(0);
		}
	}
	else
	{
		//左スティックを右に
		if ((InputCtrl::GetStickRatio(L).x > 0.8 || InputCtrl::GetButtonState(XINPUT_BUTTON_DPAD_RIGHT)) && cursor_interval >= 15)
		{
			//カーソルの移動音
			SoundManager::PlaySoundSE("se_system_select_syu", false);
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
			//カーソルの移動音
			SoundManager::PlaySoundSE("se_system_select_syu", false);
			cursor_num--;
			cursor_interval = 0;
			if (cursor_num < 0)
			{
				cursor_num = 1;
			}
		}

		if (++select_interval > 30)
		{
			if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS || InputCtrl::GetKeyState(KEY_INPUT_SPACE) == PRESS)
			{
				if (cursor_num == 0)
				{
					//回復の音
					SoundManager::PlaySoundSE("se_system_healing");
					player->SetPlayerHP(100);
					hp = static_cast<int>(MAX_HP);
					is_select = true;
				}
				else if (cursor_num == 1)
				{
					//祝福の音
					SoundManager::PlaySoundSE("se_system_blessing");
					rest_buf_flg = true;
					is_select = true;
					restCnt = 2;
				}
			}
		}
	}
}

void Rest::draw() const
{
	DrawRotaGraph(640, 300, 1.2, 0, bonfire_image[bonfire_anim], TRUE);
	DrawRotaGraph(280 + cursor_x, 610, .15, 1, cursor_image, TRUE);
	DrawGraph(1150, 650, button_image, TRUE);
	DrawRotaGraph(1210, 667, 0.1, 0, logo_dicision_image, TRUE);

	if (is_select != true)
	{
		DrawRotaGraph(470, 600, 0.2, 0, logo_rest_image, TRUE);
		DrawRotaGraph(870, 600, 0.2, 0, logo_pray_image, TRUE);
	}
	else
	{
		if (cursor_num == 0)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 230);
			DrawBox(0, (SCREEN_HEIGHT / 3), SCREEN_WIDTH, (SCREEN_HEIGHT / 3) * 2, 0x000000, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			DrawRotaGraph((SCREEN_WIDTH / 2) + 40, (SCREEN_HEIGHT / 2), 0.5, 0, logo_cure_image, TRUE);
		}
		else if (cursor_num == 1)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 230);
			DrawBox(0, (SCREEN_HEIGHT / 3), SCREEN_WIDTH, (SCREEN_HEIGHT / 3) * 2, 0x000000, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			DrawRotaGraph((SCREEN_WIDTH / 2) + 40, (SCREEN_HEIGHT / 2), 0.5, 0, logo_buf_image, TRUE);
		}
	}
}

void Rest::Init()
{
	scene_interval = 0;
	select_interval = 0;

	cursor_num = 0;

	is_select = false;
}

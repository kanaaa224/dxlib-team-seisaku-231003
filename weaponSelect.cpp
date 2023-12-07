//#include "weaponSelect.h"
#include "main.h"

Weapon_Selection::Weapon_Selection(const bool selected)
{
	cnt = 0;
	interval = 0;
	cursor_num = 0;
	select_num = 0;
	cursor_x = 0;
	image_shift = 0;

	dagger_image = LoadGraph("resources/images/武器/短剣.png");
	sword_image = LoadGraph("resources/images/武器/片手剣.png");
	great_sword_image = LoadGraph("resources/images/武器/大剣.png");

	spear_image = LoadGraph("resources/images/武器/槍.png");
	frail_image = LoadGraph("resources/images/武器/フレイル.png");
	book_image = LoadGraph("resources/images/武器/本.png");

	button_image = LoadGraph("resources/images/button_a.png");
	cursor_image = LoadGraph("resources/images/武器/片手剣.png");
	logo_choice_image = LoadGraph("resources/images/Logo/UI/logo_choice.png");
	logo_dicision_image = LoadGraph("resources/images/Logo/UI/logo_dicision.png");

	logo_dagger_iamge = LoadGraph("resources/images/Logo/WeaponName/logo_dagger_white.png");
	logo_sword_image = LoadGraph("resources/images/Logo/WeaponName/logo_sword_white.png");
	logo_great_sword_image = LoadGraph("resources/images/Logo/WeaponName/logo_greatsword_white.png");
	logo_spear_image = LoadGraph("resources/images/Logo/WeaponName/logo_spear_white.png");
	logo_frail_image = LoadGraph("resources/images/Logo/WeaponName/logo_frail_white.png");
	logo_book_image = LoadGraph("resources/images/Logo/WeaponName/logo_book_white.png");

	SoundManager::SetBGM("bgm_weaponselection");
	SoundManager::SetVolumeBGM("bgm_weaponselection", 65);
	SetLoopPosSoundMem(56400, SoundManager::GetBGMHandle("bgm_weaponselection"));

	SoundManager::SetSE("se_system_normal_decision");		//タイトル以外のカーソル決定音
	SoundManager::SetSE("se_system_select_syu");			//カーソル移動音
	SoundManager::SetVolumeSEs(50);

	is_selecting = false;
}

Weapon_Selection::~Weapon_Selection()
{
	DeleteGraph(dagger_image);
	DeleteGraph(sword_image);
	DeleteGraph(great_sword_image);
	DeleteGraph(spear_image);
	DeleteGraph(frail_image);
	DeleteGraph(book_image);
	DeleteGraph(button_image);
	DeleteGraph(cursor_image);
	DeleteGraph(logo_choice_image);
	DeleteGraph(logo_dicision_image);
	DeleteGraph(logo_dagger_iamge);
	DeleteGraph(logo_sword_image);
	DeleteGraph(logo_great_sword_image);
	DeleteGraph(logo_spear_image);
	DeleteGraph(logo_frail_image);
	DeleteGraph(logo_book_image);
}

void Weapon_Selection::update(weapon* _weapon, second_weapon* _second_weapon, bool& is_weapon_select, int& mode)
{
	SoundManager::PlaySoundBGM("bgm_weaponselection");

	//１５ｆのインターバルを設ける
	if (interval < INTERVAL)
	{
		interval++;
	}

	//カウントする
	if (cnt < SCREEN_FPS)
	{
		cnt++;
	}
	else
	{
		cnt = 0;
	}

	if (is_selecting != true)
	{
		cursor_x = cursor_num * 300;
		image_shift = cursor_num * 50;
		if (cursor_num == 1)
		{
			image_shift -= 30;
		}
	}
	else
	{
		cursor_x = cursor_num * 400;
	}

	//左スティックを右に
	if ((InputCtrl::GetStickRatio(L).x > 0.8 || InputCtrl::GetButtonState(XINPUT_BUTTON_DPAD_RIGHT)) && interval >= 15)
	{
		//カーソルの移動音
		SoundManager::PlaySoundSE("se_system_select_syu", false);
		//音がなっているなら
		if(CheckSoundMem(SoundManager::GetBGMHandle("se_system_select_syu")))
		{
			cursor_num++;
			interval = 0;
			//武器を選択していないなら３つまで
			if (is_selecting != true)
			{
				if (cursor_num >= SELECT_WEAPON)
				{
					cursor_num = 0;
				}
			}
			//武器を選択したなら２つまで
			else
			{
				if (cursor_num > 1)
				{
					cursor_num = 0;
				}
			}
		}
	}

	//左スティックを左に
	if ((InputCtrl::GetStickRatio(L).x < -0.8 || InputCtrl::GetButtonState(XINPUT_BUTTON_DPAD_LEFT)) && interval >= 15)
	{
		//カーソルの移動音
		SoundManager::PlaySoundSE("se_system_select_syu", false);
		//音がなっているなら
		if (CheckSoundMem(SoundManager::GetBGMHandle("se_system_select_syu")))
		{
			cursor_num--;
			interval = 0;
			//武器を選択していないなら３つまで
			if (is_selecting != true)
			{
				if (cursor_num < 0)
				{
					cursor_num = SELECT_WEAPON - 1;
				}
			}
			//武器を選択したなら２つまで
			else
			{
				if (cursor_num < 0)
				{
					cursor_num = 1;
				}
			}
		}
	}

	bool switch_flg = is_weapon_select;

	//武器を選択していないなら
	if (is_selecting != true)
	{
		if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS || InputCtrl::GetKeyState(KEY_INPUT_SPACE) == PRESS)
		{
			//カーソルの決定音
			SoundManager::PlaySoundSE("se_system_normal_decision", false);
			//音がなっているなら
			if (CheckSoundMem(SoundManager::GetBGMHandle("se_system_select_syu")))
			{
				//まだ武器を選択したことがないなら
				if (is_weapon_select != true)
				{
					if (cursor_num == 0)
					{
						_weapon->SetWeaponType(dagger);
						select_num = 0;
					}
					else if (cursor_num == 1)
					{
						_weapon->SetWeaponType(sword);
						select_num = 1;
					}
					else
					{
						_weapon->SetWeaponType(greatSword);
						select_num = 2;
					}
				}
				//武器を選択したことがあるなら
				else
				{
					if (cursor_num == 0)
					{
						_second_weapon->SetWeaponType(spear);
						select_num = 0;
					}
					else if (cursor_num == 1)
					{
						_second_weapon->SetWeaponType(frail);
						select_num = 1;
					}
					else
					{
						_second_weapon->SetWeaponType(book);
						select_num = 2;
					}
				}
			}
			//武器を選択した状態にする
			//is_selecting = true;
			//カーソルを「はい」の位置にする
			cursor_num = 0;
			//武器選択画面はなし
			is_weapon_select = true;
			SoundManager::StopSoundBGMs();
			SoundManager::SetSoundBGMsPosition(0);
			if (switch_flg)
			{
				mode = GameSceneMode::map;
			}
			else
			{
				mode = GameSceneMode::main;
			}
		}
	}
}

void Weapon_Selection::draw(bool flg) const
{
	//武器を選択していないなら
	if (is_selecting != true)
	{		
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 230);
		DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0x000000, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		if (flg != true)
		{
			DrawRotaGraph(350 + cursor_x, 600, .15, 5.7, cursor_image, TRUE);

			DrawRotaGraph(670, 20, 0.25, 0, logo_choice_image, TRUE);

			if (cursor_num == 0)
			{
				DrawRotaGraph(350, 450, 0.25, 0, logo_dagger_iamge, TRUE);
				DrawRotaGraph(350, 310 + sin(M_PI * 2 / SCREEN_FPS * cnt) * 10, .35f, .0625f, dagger_image, TRUE);

				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);

				DrawRotaGraph(650, 450, 0.25, 0, logo_sword_image, TRUE);
				DrawRotaGraph(650, 280, .40f, .0625f, sword_image, TRUE);

				DrawRotaGraph(950, 450, 0.25, 0, logo_great_sword_image, TRUE);
				DrawRotaGraph(950, 250, .55f, .0625f, great_sword_image, TRUE);

				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			else if (cursor_num == 1)
			{
				DrawRotaGraph(650, 450, 0.25, 0, logo_sword_image, TRUE);
				DrawRotaGraph(650, 280 + sin(M_PI * 2 / SCREEN_FPS * cnt) * 10, .40f, .0625f, sword_image, TRUE);

				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);

				DrawRotaGraph(350, 450, 0.25, 0, logo_dagger_iamge, TRUE);
				DrawRotaGraph(350, 310, .35f, .0625f, dagger_image, TRUE);

				DrawRotaGraph(950, 450, 0.25, 0, logo_great_sword_image, TRUE);
				DrawRotaGraph(950, 250, .55f, .0625f, great_sword_image, TRUE);

				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			else
			{
				DrawRotaGraph(950, 450, 0.25, 0, logo_great_sword_image, TRUE);
				DrawRotaGraph(950, 250 + sin(M_PI * 2 / SCREEN_FPS * cnt) * 10, .55f, .0625f, great_sword_image, TRUE);

				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);

				DrawRotaGraph(650, 450, 0.25, 0, logo_sword_image, TRUE);
				DrawRotaGraph(650, 280, .40f, .0625f, sword_image, TRUE);

				DrawRotaGraph(350, 450, 0.25, 0, logo_dagger_iamge, TRUE);
				DrawRotaGraph(350, 310, .35f, .0625f, dagger_image, TRUE);

				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}
		else
		{
			DrawRotaGraph(330 + cursor_x + image_shift, 600, .15, 5.7, cursor_image, TRUE);

			DrawRotaGraph(670, 20, 0.25, 0, logo_choice_image, TRUE);

			if (cursor_num == 0)
			{
				DrawRotaGraph(320, 450, 0.25, 0, logo_spear_image, TRUE);
				DrawRotaGraph(330, 300 + sin(M_PI * 2 / SCREEN_FPS * cnt) * 10, .4f, .2f, spear_image, TRUE);

				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);

				DrawRotaGraph(650, 450, 0.25, 0, logo_frail_image, TRUE);
				DrawRotaGraph(690, 330, .35f, .2925f, frail_image, TRUE);

				DrawRotaGraph(1030, 450, 0.25, 0, logo_book_image, TRUE);
				DrawRotaGraph(1020, 335, .25f, 0.f, book_image, TRUE);

				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			else if (cursor_num == 1)
			{
				DrawRotaGraph(650, 450, 0.25, 0, logo_frail_image, TRUE);
				DrawRotaGraph(690, 330 + sin(M_PI * 2 / SCREEN_FPS * cnt) * 10, .35f, .2925f, frail_image, TRUE);

				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);

				DrawRotaGraph(320, 450, 0.25, 0, logo_spear_image, TRUE);
				DrawRotaGraph(330, 300, .4f, .2f, spear_image, TRUE);

				DrawRotaGraph(1030, 450, 0.25, 0, logo_book_image, TRUE);
				DrawRotaGraph(1020, 335, .25f, 0.f, book_image, TRUE);

				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			else
			{
				DrawRotaGraph(1030, 450, 0.25, 0, logo_book_image, TRUE);
				DrawRotaGraph(1020, 335 + sin(M_PI * 2 / SCREEN_FPS * cnt) * 10, .25f, 0.f, book_image, TRUE);

				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);

				DrawRotaGraph(650, 450, 0.25, 0, logo_frail_image, TRUE);
				DrawRotaGraph(690, 330, .35f, .2925f, frail_image, TRUE);

				DrawRotaGraph(320, 450, 0.25, 0, logo_spear_image, TRUE);
				DrawRotaGraph(330, 300, .4f, .2f, spear_image, TRUE);

				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}
	}

	DrawGraph(1150, 650, button_image, TRUE);
	DrawRotaGraph(1210, 667, 0.1, 0, logo_dicision_image, TRUE);

}

#include "main.h"

Blacksmith::Blacksmith()
{
	// 画像の読込
	img_cursor = LoadGraph("resources/images/levelup_cursor.png");
	img_chooce = LoadGraph("resources/images/blacksmith_choose.png");
	img_hammer = LoadGraph("resources/images/hammer.png");
	img_spark = LoadGraph("resources/images/spark.png");
	img_exclamation_mark = LoadGraph("resources/images/mark_exclamation_white.png");
	img_arrow = LoadGraph("resources/images/arrow.png");
	img_button_b = LoadGraph("resources/images/button_b.png");
	img_button_a = LoadGraph("resources/images/button_a01.png");
	img_background = LoadGraph("resources/images/stageimage2.png");

	// 武器画像
	img_sword = LoadGraph("resources/images/武器/片手剣.png");
	img_dagger = LoadGraph("resources/images/武器/短剣.png");
	img_great_sword = LoadGraph("resources/images/武器/大剣.png");
	img_spear = LoadGraph("resources/images/武器/槍.png");
	img_frail = LoadGraph("resources/images/武器/フレイル.png");
	img_book = LoadGraph("resources/images/武器/本.png");
	img_question_mark = LoadGraph("resources/images/mark_question.png");

	// 構造体初期化
	weapon1_info = { 0, none, 0, 0, 0, false };
	weapon2_info = { 1, none, 0, 0, 0, false };

	// 変数の初期化
	interval = 0;
	cursor_x = 370;
	cursor_y = 320;
	weapon_number = weapon1_info.num;

	// 画像パラメータ
	img_x = 380;
	img_y = 350;

	action_selection = false;
	action_number = levelup;
	restore_cursor_position = true;
	cursor_action = state_first;
	box_color = 0x696868;
	box_color_hover = 0xb0b0b0;
	value = 80;
}

Blacksmith::~Blacksmith()
{
	DeleteGraph(img_cursor);
	DeleteGraph(img_chooce);
	DeleteGraph(img_hammer);
	DeleteGraph(img_spark);
	DeleteGraph(img_exclamation_mark);
	DeleteGraph(img_arrow);
	DeleteGraph(img_button_b);
	DeleteGraph(img_button_a);
	DeleteGraph(img_background);
	DeleteGraph(img_sword);
	DeleteGraph(img_dagger);
	DeleteGraph(img_great_sword);
	DeleteGraph(img_spear);
	DeleteGraph(img_frail);
	DeleteGraph(img_book);
	DeleteGraph(img_question_mark);
}

// 更新
void Blacksmith::update(weapon* weapon, second_weapon* second_weapon, WeaponLevelUp* weapon_levelup, Player* player, int& point, int& mode, int& stage)
{
	SoundManager::PlaySoundBGM("bgm_smith");

	// 15fのインターバル
	if (interval < 15)
	{
		interval++;
	}

	// 行動選択
	if (action_selection == false)
	{
		// カーソル左右移動
		CursorMove();

		// Aボタンで決定
		if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS)
		{
			//カーソルの決定音
			SoundManager::PlaySoundSE("se_system_normal_decision");
			action_selection = true;

			if (action_number == reset_level)
			{
				cursor_action = state_weapon;
				// カーソル位置を武器1の上に変更
				cursor_x = img_x;
				cursor_y = 160;
			}
		}

		// Bボタンで出る
		if (InputCtrl::GetButtonState(XINPUT_BUTTON_B) == PRESS)
		{
			weapon_levelup->SetIsBlacksmith(false);
			stage++;
			SoundManager::StopSoundBGM("bgm_smith");
			SoundManager::SetSoundBGMsPosition(0);
			mode = GameSceneMode::map;
		}
	}
	else
	{
		if (action_number == levelup)
		{
			// 最終強化 or レベルアップ
			weapon_levelup->SetIsBlacksmith(true);
			weapon_levelup->update(weapon, second_weapon, player, restore_cursor_position, point);

			// レベルアップ画面で武器の選択をしていた場合
			if (weapon_levelup->GetIsCloseLevelUp() == true)
			{
				// Bボタンで行動選択に戻る
				if (InputCtrl::GetButtonState(XINPUT_BUTTON_B) == PRESS)
				{
					//カーソルのキャンセル音
					SoundManager::PlaySoundSE("se_system_cancel", false);

					// レベルアップ画面の変数初期化
					// レベルアップ画面を閉じたときに初期化しないと画像の表示位置がおかしくなってしまう
					weapon_levelup->Init(weapon, second_weapon, player, restore_cursor_position);

					action_selection = false;
				}
			}
		}
		else
		{
			// レベルの振り直し、ポイントの返却


			// 武器の種類のセット
			weapon1_info.type = weapon->GetWeaponType();
			weapon2_info.type = second_weapon->GetWeaponType();

			// 初期設定
			Init(weapon, second_weapon, weapon_levelup);

			// カーソル左右移動
			CursorMove();

			// 武器の決定
			if (weapon_number == weapon1_info.num && weapon1_info.level != 0)
			{
				weapon1_info.can_reset = true;

				// 過去にレベルアップしたことがある場合選択できる
				if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS)
				{
					//カーソルの決定音
					SoundManager::PlaySoundSE("se_system_normal_decision");
					ResetLevel(weapon, second_weapon, weapon_levelup, &weapon1_info, point);
				}
			}
			else if (weapon2_info.num != none && weapon2_info.level_hierarchy != 0)
			{
				weapon2_info.can_reset = true;

				if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS)
				{
					ResetLevel(weapon, second_weapon, weapon_levelup, &weapon2_info, point);
				}
			}
			else
			{
				if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS)
				{
					//カーソルのNG音
					SoundManager::PlaySoundSE("se_system_ng", false);
				}
			}

			// Bボタンで行動選択に戻る
			if (InputCtrl::GetButtonState(XINPUT_BUTTON_B) == PRESS)
			{
				//カーソルのキャンセル音
				SoundManager::PlaySoundSE("se_system_cancel", false);

				cursor_action = state_first;
				action_number = levelup;
				weapon_number = weapon1_info.num;
				cursor_x = 370;
				cursor_y = 320;
				action_selection = false;
			}
		}
	}
}

// 描画
void Blacksmith::draw(WeaponLevelUp* weapon_levelup) const
{
	// 背景
	//DrawBox(0, 0, 1280, 720, 0x808080, TRUE);
	DrawGraph(0, 0, img_background, TRUE);

	if (action_selection == false)
	{
		// 行動選択時の描画
		FirstDraw(weapon_levelup);
	}
	else
	{
		// 行動選択済み
		if (action_number == levelup)
		{
			// 最終強化 or レベルアップ時の画像、テキストの表示
			weapon_levelup->draw();
		}
		else
		{
			// レベルリセット画面描画
			DrawResetLevel(weapon_levelup);
		}
	}


#ifdef _DEBUG	
	// テスト表示
	//SetFontSize(20);
	//DrawFormatString(160, 30, 0x000000, "W1レベル階層 : %d", weapon1_level_hierarchy);
	//DrawFormatString(160, 50, 0x000000, "W2level (State): %d", weapon2_level);
	//DrawFormatString(160, 70, 0x000000, "W2レベル階層 : %d", weapon2_level_hierarchy);

	//DrawFormatString(0, 0, 0x000000, "action_number：%d", action_number);
	//DrawFormatString(0, 20, 0x000000, "GetWeaponSelection：%d", weapon_levelup->GetIsCloseLevelUp());
	//DrawFormatString(0, 40, 0x000000, "action_selection：%d", action_selection);
	//DrawFormatString(0, 60, 0x000000, "weapon_selection：%d", weapon_selection);
	//DrawFormatString(0, 80, 0x000000, "action_number：%d", action_number);
	//DrawFormatString(0, 100, 0x000000, "cursor_x：%d", cursor_x);
	//DrawFormatString(0, 120, 0x000000, "cursor_y：%d", cursor_y);
	//DrawFormatString(0, 200, 0x000000, "weapon_number %d", weapon_number);
	//DrawFormatString(0, 220, 0x000000, "cursor_action %d", cursor_action);
	//DrawFormatString(0, 240, 0x000000, "cursor_x %d", cursor_x);
	//DrawFormatString(0, 260, 0x000000, "cursor_y %d", cursor_y);
	//DrawFormatString(0, 280, 0x000000, "action_number %d", action_number);

//	DrawFormatString(0, 0, 0x000000, "カーソル位置: %d - %d", InputCtrl::GetMouseCursor().x, InputCtrl::GetMouseCursor().y);
#endif

}

// 初期設定
void Blacksmith::Init(weapon* weapon, second_weapon* second_weapon, WeaponLevelUp* weapon_levelup)
{
	// 現在の武器レベルのセット
	weapon1_info.level = weapon->GetWeaponLevel();
	weapon2_info.level = second_weapon->GetWeaponLevel();

	// レベル階層のセット
	weapon1_info.level_hierarchy = weapon_levelup->GetWeapon1LevelHierarchy();
	weapon2_info.level_hierarchy = weapon_levelup->GetWeapon2LevelHierarchy();
}

// カーソル左右移動処理
void Blacksmith::CursorMove()
{
	if (InputCtrl::GetStickRatio(L).x > 0.8 && interval >= 15)
	{
		//カーソルの移動音
		SoundManager::PlaySoundSE("se_system_select_syu", false);

		//左スティックを右に
		interval = 0;

		if (cursor_action == state_first)
		{
			cursor_x = 900;
			action_number = reset_level;
		}
		else
		{
			cursor_x = img_x + 510;
			weapon_number = weapon2_info.num;
		}
	}
	else if (InputCtrl::GetStickRatio(L).x < -0.8 && interval >= 15)
	{
		//カーソルの移動音
		SoundManager::PlaySoundSE("se_system_select_syu", false);

		//左スティックを左に
		interval = 0;

		if (cursor_action == state_first)
		{
			cursor_x = 370;
			action_number = levelup;
		}
		else
		{
			cursor_x = img_x;
			weapon_number = weapon1_info.num;
		}
	}
}

// レベルリセット
void Blacksmith::ResetLevel(weapon* weapon, second_weapon* second_weapon, WeaponLevelUp* weapon_levelup, weapon_information* info, int& point)
{
	// レベルリセット
	if (info->num == weapon1_info.num)
	{
		// 武器1
		weapon->SetWeaponLevel(0);
		weapon_levelup->Weapon1LevelInit();
	}
	else
	{
		// 武器2
		second_weapon->SetWeaponLevel(0);
		weapon_levelup->Weapon2LevelInit();
	}

	// ポイントの返却
	if (info->level_hierarchy >= 4)
	{
		weapon_levelup->SetLevelUpPoint(point, 3);
	}
	else
	{
		weapon_levelup->SetLevelUpPoint(point, info->level_hierarchy - 1);
	}

	info->can_reset = false;

	// 初期設定
	Init(weapon, second_weapon, weapon_levelup);
}

// 行動選択時の描画
void Blacksmith::FirstDraw(WeaponLevelUp* weapon_levelup) const
{
	// カーソル画像
	DrawRotaGraph(cursor_x , 100, 0.1f, 0.0f, img_cursor, TRUE);

	SetFontSize(50);
	if (action_number == levelup)
	{		
		DrawBox(170, 130, 570, 590, box_color_hover, TRUE);
		DrawBox(710, 130, 1110, 590, box_color, TRUE);

		DrawRotaGraph(430, 280, 0.5f, 0.0f, img_hammer, TRUE);
		DrawRotaGraph(250, 370, 0.2f, 0.0f, img_spark, TRUE);
		DrawFormatString(210, 520, 0x000000, "レベルアップ");

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, value);

		DrawRotaGraph(1030, 210, 0.2f, 0.0f, img_sword, TRUE);
		DrawRotaGraph(900, 300, 0.2f, M_PI / -4.0f, img_arrow, TRUE);
		DrawRotaGraph(800, 400, 1.0f, 0.0f, img_chooce, TRUE);
		DrawFormatString(740, 520, 0x000000, "レベルリセット");
		
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else
	{
		DrawBox(170, 130, 570, 590, box_color, TRUE);
		DrawBox(710, 130, 1110, 590, box_color_hover, TRUE);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, value);

		DrawRotaGraph(430, 280, 0.5f, 0.0f, img_hammer, TRUE);
		DrawRotaGraph(250, 370, 0.2f, 0.0f, img_spark, TRUE);
		DrawFormatString(210, 520, 0x000000, "レベルアップ");

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		DrawRotaGraph(1030, 210, 0.2f, 0.0f, img_sword, TRUE);
		DrawRotaGraph(900, 300, 0.2f, M_PI / -4.0f, img_arrow, TRUE);
		DrawRotaGraph(800, 400, 1.0f, 0.0f, img_chooce, TRUE);
		DrawFormatString(740, 520, 0x000000, "レベルリセット");
	}

	// 最終強化できる場合
	if (weapon_levelup->GetWeapon1LevelHierarchy() == MAX_LEVEL_HIERARCHY || weapon_levelup->GetWeapon2LevelHierarchy() == MAX_LEVEL_HIERARCHY)
	{
		// ビックリマーク
		DrawRotaGraph(170, 130, 0.2f, 0.0f, img_exclamation_mark, TRUE);
	}

	DrawBox(1020, 660, 1240, 710, box_color_hover, TRUE);

	DrawRotaGraph(1050, 685, 0.25f, 0.0f, img_button_a, TRUE);
	DrawRotaGraph(1150, 685, 0.25f, 0.0f, img_button_b, TRUE);

	SetFontSize(20);
	DrawFormatString(1080, 675, 0x000000, "決定");
	DrawFormatString(1180, 675, 0x000000, "出る");
}

// レベルリセット画面描画
void Blacksmith::DrawResetLevel(WeaponLevelUp* weapon_levelup) const
{
	DrawBox(490, 35, 790, 110, box_color_hover, TRUE);

	SetFontSize(35);
	DrawFormatString(510, 45, 0x000000, "レベルリセット");
	SetFontSize(15);
	DrawFormatString(530, 85, 0xb00000, "武器のレベルが0になります");

	SetFontSize(20);
	if (weapon_number == weapon1_info.num)
	{
		DrawBox(230, 200, 530, 600, box_color_hover, TRUE);
		DrawBox(740, 200, 1040, 600, box_color, TRUE);

		// 武器1の画像、テキスト
		DrawWeapon1Images();
		DrawWeapon1ResetText();

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, value);
		
		// 武器2の画像、テキスト
		DrawWeapon2Images();
		DrawWeapon2ResetText();

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else
	{
		DrawBox(230, 200, 530, 600, box_color, TRUE);
		DrawBox(740, 200, 1040, 600, box_color_hover, TRUE);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, value);

		// 武器1の画像、テキスト
		DrawWeapon1Images();
		DrawWeapon1ResetText();

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		// 武器2の画像、テキスト
		DrawWeapon2Images();
		DrawWeapon2ResetText();
	}

	// カーソル画像
	DrawRotaGraph(cursor_x, cursor_y, 0.1f, 0.0f, img_cursor, TRUE);

	DrawBox(1020, 660, 1240, 710, box_color_hover, TRUE);

	DrawRotaGraph(1050, 685, 0.25f, 0.0f, img_button_a, TRUE);
	DrawRotaGraph(1150, 685, 0.25f, 0.0f, img_button_b, TRUE);

	//SetFontSize(20);
	DrawFormatString(1080, 675, 0x000000, "決定");
	DrawFormatString(1180, 675, 0x000000, "戻る");
}

// 武器1の画像描画
void Blacksmith::DrawWeapon1Images() const
{
	// 武器1の画像
	switch (weapon1_info.type)
	{
	case sword:			// 片手剣
		DrawRotaGraph(img_x, img_y, 0.28f, 0.0f, img_sword, TRUE);
		DrawFormatString(290, 520, 0x000000, "片手剣");
		break;
	case dagger:		// 短剣
		DrawRotaGraph(img_x, img_y, 0.28f, 0.0f, img_dagger, TRUE);
		DrawFormatString(290, 520, 0x000000, "短剣");
		break;
	case greatSword:	// 大剣
		DrawRotaGraph(img_x, img_y, 0.4f, 0.0f, img_great_sword, TRUE);
		DrawFormatString(290, 520, 0x000000, "大剣");
		break;
	default:
		DrawRotaGraph(img_x, img_y, 0.2f, 0.0f, img_question_mark, TRUE);
		DrawFormatString(290, 520, 0x000000, "武器がありません");
		break;
	}
}

// 武器2の画像描画
void Blacksmith::DrawWeapon2Images() const
{
	// 武器2の画像
	switch (weapon2_info.type)
	{
	case spear:			// 槍
		DrawRotaGraph(img_x + 510, img_y, 0.34f, 0.0f, img_spear, TRUE);
		DrawFormatString(800, 520, 0x000000, "槍");
		break;
	case frail:			// フレイル
		DrawRotaGraph(img_x + 510, img_y, 0.34f, 0.0f, img_frail, TRUE);
		DrawFormatString(800, 520, 0x000000, "フレイル");
		break;
	case book:			// 魔導書
		DrawRotaGraph(img_x + 510, img_y, 0.28f, 0.0f, img_book, TRUE);
		DrawFormatString(800, 520, 0x000000, "魔導書");
		break;
	default:
		DrawRotaGraph(img_x + 510, img_y, 0.2f, 0.0f, img_question_mark, TRUE);
		DrawFormatString(800, 520, 0x000000, "武器がありません");
		break;
	}
}

// 武器1の情報のテキスト
void Blacksmith::DrawWeapon1ResetText() const
{
	DrawFormatString(290, 540, 0x000000, "Lv. %d", weapon1_info.level);

	if (weapon1_info.can_reset == false)
	{
		DrawFormatString(290, 560, 0xb00000, "レベルリセット不可");
	}
	else
	{
		if (weapon1_info.level_hierarchy > 0 && weapon1_info.level_hierarchy <= 3)
		{
			DrawFormatString(290, 560, 0x000000, "返却ポイント： %d", weapon1_info.level_hierarchy - 1);
		}
		else if (weapon1_info.level_hierarchy > 3)
		{
			DrawFormatString(290, 560, 0x000000, "返却ポイント： 3");
		}
	}
}

// 武器2の情報のテキスト
void Blacksmith::DrawWeapon2ResetText() const
{
	// 武器2
	DrawFormatString(800, 540, 0x000000, "Lv. %d", weapon2_info.level);
	if (weapon2_info.can_reset == false)
	{
		DrawFormatString(800, 560, 0xb00000, "レベルリセット不可");
	}
	else
	{
		if (weapon2_info.level_hierarchy > 0 && weapon2_info.level_hierarchy <= 3)
		{
			DrawFormatString(800, 560, 0x000000, "返却ポイント： %d", weapon2_info.level_hierarchy - 1);
		}
		else if (weapon2_info.level_hierarchy > 3)
		{
			DrawFormatString(800, 560, 0x000000, "返却ポイント： 3");
		}
	}
}
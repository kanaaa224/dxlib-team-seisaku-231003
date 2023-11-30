#include "main.h"

WeaponLevelUp::WeaponLevelUp()
{
	// 画像の読込
	img_tree_diagram = LoadGraph("resources/images/tree_diagram01.png");
	img_cursor = LoadGraph("resources/images/levelup_cursor.png");
	img_branch_point = LoadGraph("resources/images/branch_point.png");
	img_chooce = LoadGraph("resources/images/levelup_choose.png");
	img_button_a = LoadGraph("resources/images/button_a01.png");
	img_button_b = LoadGraph("resources/images/button_b.png");
	img_button_x = LoadGraph("resources/images/button_x.png");

	// 武器画像
	img_sword = LoadGraph("resources/images/武器/片手剣.png");
	img_dagger= LoadGraph("resources/images/武器/短剣.png");
	img_great_sword = LoadGraph("resources/images/武器/大剣.png");
	img_spear = LoadGraph("resources/images/武器/槍.png");
	img_frail = LoadGraph("resources/images/武器/フレイル.png");
	img_book = LoadGraph("resources/images/武器/本.png");
	img_question_mark = LoadGraph("resources/images/mark_question.png");

	// 構造体初期化
	weapon1_info = { 0, none, 0, 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f };
	weapon2_info = { 1, none, 0, 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f };

	// 変数の初期化
	interval = 0;
	cursor_x = 580;
	cursor_y = 120;
	level_cursor_pos = 85;
	lv_point = 0;
	weapon_number = weapon1_info.num;
	weapon_selection = false;

	is_blacksmith = false;
	is_close_level_up = false;

	// 画像パラメータ
	img_x = 580;
	img_y = 160;
	img_branch_point_x = cursor_x;
	img_branch_point_y = 260;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			branch_point_x[i][j] = cursor_x;
			branch_point_y[i][j] = img_branch_point_y;
			is_chooce[i][j] = false;
		}
	}

	w_p_speed = 0.0f;
	w_p_avoidancecooltime = 0.0f;
	w_p_upperlimitlimit = 0.0f;

	p_speed = 0.0f;
	p_avoidancecooltime = 0.0f;
	p_upperlimitlimit = 0.0f;

	frail_radiusX = 0.0f;
	frail_radiusY = 0.0f;
	tmp_frail_radiusX = 0.0f;
	tmp_frail_radiusY = 0.0f;

	//close = false;
	close_mode = 2;

	// テスト
	fp = NULL;
	for (int i = 0; i < 2; i++)
	{
		sample[i] = { 0 };
	}
}

WeaponLevelUp::~WeaponLevelUp()
{

}

// 更新
void WeaponLevelUp::update(weapon* weapon, second_weapon* second_weapon, Player* player, bool& restor_cursor_position, int& point)
{	
	// テスト
	sample[0].type = weapon1_info.type;
	sample[0].level = weapon1_info.level;

	sample[1].type = weapon2_info.type;
	sample[1].level = weapon2_info.level;

	// ファイル書き込み
	fopen_s(&fp, "resources/dat/test.txt", "w");

	if (fp)
	{
		for (int i = 0; i < 2; i++)
		{
			fprintf(fp, "%1d %1d %d\n", sample[i].type, sample[i].level, sample[i].damage);
		}
		//ファイルクローズ
		fclose(fp);
	}
	//////////////////////////////

	// weaponからのプレイヤー情報
	// カーソル移動で更新される値
	w_p_speed = weapon->GetP_Speed();
	w_p_avoidancecooltime = weapon->GetP_AvoidanceCooltime();
	w_p_upperlimitlimit = weapon->GetP_Upperlimitlimit();

	weapon1_info.cool_time = weapon->GetMaxCoolTime();
	weapon1_info.damege = weapon->GetDamage();
	weapon1_info.attack_range = weapon->GetMaxRot();

	weapon2_info.cool_time = second_weapon->GetMaxCoolTime();
	weapon2_info.damege = second_weapon->GetDamage();
	weapon2_info.attack_range = second_weapon->GetMaxRot();

	frail_radiusX = second_weapon->GetP_aiming_radiusX();
	frail_radiusY = second_weapon->GetP_aiming_radiusY();

	lv_point = point;

	// カーソルの位置を元に戻す
	if (restor_cursor_position == true)
	{
		// 初期化
		Init(weapon, second_weapon, restor_cursor_position);
		// playerからのプレイヤー情報
		p_speed = player->GetPlayer_Speed();
		p_avoidancecooltime = player->GetAvoidance_limit();
		p_upperlimitlimit = player->GetPlayer_Upperlimit();

		weapon1_info.tmp_cool_time = weapon->GetMaxCoolTime();
		weapon1_info.tmp_damege = weapon->GetDamage();
		weapon1_info.tmp_attack_range = weapon->GetMaxRot();

		weapon2_info.tmp_cool_time = second_weapon->GetMaxCoolTime();
		weapon2_info.tmp_damege = second_weapon->GetDamage();
		weapon2_info.tmp_attack_range = second_weapon->GetMaxRot();

		tmp_frail_radiusX = player->GetPlayer_RadiusX();
		tmp_frail_radiusY = player->GetPlayer_RadiusY();
	}

	// 15fのインターバル
	if (interval < 15)
	{
		interval++;
	}

	// 武器の選択
	if (weapon_selection == false)
	{
		// 鍛冶ステージで使用
		is_close_level_up = true;

		// 武器を2種類持っていたら武器選択ができる
		//if (weapon2_info.type != none)
		//{
			if (InputCtrl::GetStickRatio(L).x > 0.8 && interval >= 15)
				{
				//左スティックを右に
				interval = 0;
				cursor_x = 960;
				weapon_number = weapon2_info.num;
			}
			else if (InputCtrl::GetStickRatio(L).x < -0.8 && interval >= 15)
			{
				//左スティックを左に
				interval = 0;
				cursor_x = 580;
				weapon_number = weapon1_info.num;

			}
		//}

		// Aボタンで決定
		if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS && lv_point > 0)
		{
			// 武器2がnoneだったら武器2の選択決定は不可
			// それ以外の場合は選択決定可能
			if (cursor_x == 580 || weapon2_info.type != none)
			{
				weapon_selection = true;
			}
		}
	}
	else
	{
		// 鍛冶ステージで使用
		is_close_level_up = false;

		if (weapon_number == weapon1_info.num)
		{
			// レベルアップ詳細カーソル
			switch (weapon1_info.level_hierarchy)
			{
			case 0:
				weapon1_info.tmp_level = 1;
				break;
			case 1:
				if (weapon1_info.cursor_pos == -level_cursor_pos)
				{
					// 樹形図の左を選択
					weapon1_info.tmp_level = 2;
				}
				else
				{
					// 樹形図の右を選択
					weapon1_info.tmp_level = 3;
				}
				break;
			case 2:
				if (weapon1_info.cursor_pos == -level_cursor_pos)
				{
					// 樹形図の左を選択
					weapon1_info.tmp_level = 4;
				}
				else
				{
					// 樹形図の右を選択
					weapon1_info.tmp_level = 5;
				}
				break;
			case 3:
				weapon1_info.tmp_level = 6;
				break;
			case 4:
				if (weapon1_info.cursor_pos == -level_cursor_pos)
				{
					// 樹形図の左を選択
					weapon1_info.tmp_level = 7;
				}
				else
				{
					// 樹形図の右を選択
					weapon1_info.tmp_level = 8;
				}
				break;
			default:
				break;
			}
			
			weapon->SetWeaponLevel(weapon1_info.tmp_level);

			if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS)
			{
				// 武器1のレベルアップ
				LevelUp(weapon, second_weapon, player, &weapon1_info, point);
			}

			// カーソル移動
			LevelUpCursorMove(&weapon1_info);
		}
		else
		{
			// レベルアップ詳細カーソル
			switch (weapon2_info.level_hierarchy)
			{
			case 0:
				weapon2_info.tmp_level = 1;
				break;
			case 1:
				if (weapon2_info.cursor_pos == -level_cursor_pos)
				{
					// 樹形図の左を選択
					weapon2_info.tmp_level = 2;
				}
				else
				{
					// 樹形図の右を選択
					weapon2_info.tmp_level = 3;
				}
				break;
			case 2:
				if (weapon2_info.cursor_pos == -level_cursor_pos)
				{
					// 樹形図の左を選択
					weapon2_info.tmp_level = 4;
				}
				else
				{
					// 樹形図の右を選択
					weapon2_info.tmp_level = 5;
				}
				break;
			case 3:
				weapon2_info.tmp_level = 6;
				break;
			case 4:
				if (weapon2_info.cursor_pos == -level_cursor_pos)
				{
					// 樹形図の左を選択
					weapon2_info.tmp_level = 7;
				}
				else
				{
					// 樹形図の右を選択
					weapon2_info.tmp_level = 8;
				}
				break;
			default:
				break;
			}

			second_weapon->SetWeaponLevel(weapon2_info.tmp_level);

			if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS)
			{
				// 武器2のレベルアップ
				LevelUp(weapon, second_weapon, player, &weapon2_info, point);
			}

			// カーソル移動
			LevelUpCursorMove(&weapon2_info);
		}

		// Bボタンで選択武器のキャンセル
		if (InputCtrl::GetButtonState(XINPUT_BUTTON_B) == PRESS)
		{
			// レベルカーソルの位置直し
			if (weapon_number == weapon1_info.num)
			{
				ReturnLevelUpCursorPos(&weapon1_info);
			}
			else
			{
				ReturnLevelUpCursorPos(&weapon2_info);
			}

			// 現在の武器レベルのセット
			weapon->SetWeaponLevel(weapon1_info.level);
			second_weapon->SetWeaponLevel(weapon2_info.level);

			weapon_selection = false;
		}
	}

	// Xボタン離した
	if (InputCtrl::GetKeyState(KEY_INPUT_X) == RELEASE || InputCtrl::GetButtonState(XINPUT_BUTTON_X) == RELEASE && close_mode == 0)
	{
		close_mode = 1;
	}

	// 閉じるとき
	if (InputCtrl::GetKeyState(KEY_INPUT_X) == PRESS || InputCtrl::GetButtonState(XINPUT_BUTTON_X) == PRESS)
	{
		if (close_mode == 1)
		{
			// 現在の武器レベルのセット
			weapon->SetWeaponLevel(weapon1_info.level);
			second_weapon->SetWeaponLevel(weapon2_info.level);

			// 閉じる
			close_mode = 2;
			//close = true;
		}
	}
}

// 描画
void WeaponLevelUp::draw() const
{
	// 背景
	DrawBox(160, 10, 1120, 710, 0xa0a0a0, TRUE);

	SetFontSize(30);
	DrawFormatString(560, 10, 0x000000, "レベルアップ");

	SetFontSize(20);
	DrawFormatString(900, 20, 0x000000, "LevelUpPoint：%d", lv_point);

	// ボタン案内
	DrawRotaGraph(855, 690, 0.2f, 0.0f, img_button_a, TRUE);
	DrawRotaGraph(945, 690, 0.2f, 0.0f, img_button_b, TRUE);
	DrawRotaGraph(1030, 690, 0.2f, 0.0f, img_button_x, TRUE);
	DrawFormatString(875, 680, 0x000000, "決定");
	DrawFormatString(965, 680, 0x000000, "戻る");
	DrawFormatString(1050, 680, 0x000000, "閉じる");

	// レベルアップ詳細のテキスト群
	DrawLevelUpDetails();

	// 樹形図の線
	DrawRotaGraph(img_x + 5, 440, 0.9f, 0.0f, img_tree_diagram, TRUE);
	DrawRotaGraph(img_x + 385, 440, 0.9f, 0.0f, img_tree_diagram, TRUE);

	// 武器1の画像
	switch (weapon1_info.type)
	{
		case sword:			// 片手剣
			DrawRotaGraph(img_x, img_y, 0.14f, 0.0f, img_sword, TRUE);
			break;
		case dagger:		// 短剣
			DrawRotaGraph(img_x, img_y, 0.14f, 0.0f, img_dagger, TRUE);
			break;
		case greatSword:	// 大剣
			DrawRotaGraph(img_x, img_y, 0.2f, 0.0f, img_great_sword, TRUE);
			break;
		default:
			DrawRotaGraph(img_x, img_y, 0.1f, 0.0f, img_question_mark, TRUE);
			break;
	}

	// 武器2の画像
	switch (weapon2_info.type)
	{
		case spear:			// 槍
			DrawRotaGraph(img_x + 380, img_y, 0.17f, 0.0f, img_spear, TRUE);
			break;
		case frail:			// フレイル
			DrawRotaGraph(img_x + 380, img_y, 0.17f, 0.0f, img_frail, TRUE);
			break;
		case book:			// 本
			DrawRotaGraph(img_x + 380, img_y, 0.14f, 0.0f, img_book, TRUE);
			break;
		default:
			DrawRotaGraph(img_x + 380, img_y, 0.1f, 0.0f, img_question_mark, TRUE);
			break;
	}
	
	// スキルツリー分岐点画像の表示
	for (int i = 0; i <= MAX_LEVEL_HIERARCHY; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			// レベル階層によって分岐
			if (i == 0 || i == 3)
			{
				DrawRotaGraph(img_branch_point_x + 380 * j, img_branch_point_y + LEVEL_HIERARCHY_HEIGHT * i, 0.08f, 0.0f, img_branch_point, TRUE);
			}
			else
			{
				DrawRotaGraph(img_branch_point_x + level_cursor_pos + 380 * j, img_branch_point_y + LEVEL_HIERARCHY_HEIGHT * i, 0.08f, 0.0f, img_branch_point, TRUE);
				DrawRotaGraph(img_branch_point_x - level_cursor_pos + 380 * j, img_branch_point_y + LEVEL_HIERARCHY_HEIGHT * i, 0.08f, 0.0f, img_branch_point, TRUE);
			}
		}
	}


	// 選択したレベルに画像の表示
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j <= MAX_LEVEL_HIERARCHY; j++)
		{
			if (is_chooce[i][j] == true)
			{
				DrawRotaGraph(branch_point_x[i][j], branch_point_y[i][j], 0.1f, 0.0f, img_chooce, TRUE);
			}
		}
	}

	// 武器選択用の円を描画
	//DrawCircle(cursor_x , cursor_y, 20, 0x000000, FALSE);
	
	// 武器選択カーソル
	if (weapon_selection == false)
	{
		DrawRotaGraph(cursor_x, cursor_y - 50, 0.08f, 0.0f, img_cursor, TRUE);
	}
	else
	{
		// 武器選択済み
		if (weapon_number == weapon1_info.num)
		{
			// 武器1
			if(weapon1_info.level_hierarchy <= MAX_LEVEL_HIERARCHY)
			{
				// カーソル表示
				DrawRotaGraph(cursor_x + weapon1_info.cursor_pos, cursor_y + (LEVEL_HIERARCHY_HEIGHT * (weapon1_info.level_hierarchy + 1)), 0.08f, 0.0f, img_cursor, TRUE);
				// レベル選択の円を描画
				//DrawCircle(cursor_x + weapon1_info.cursor_pos, cursor_y + 50 + (LEVEL_HIERARCHY_HEIGHT * (weapon1_info.level_hierarchy + 1)), 20, 0xb00000, FALSE);
				// 丸画像表示
				//DrawRotaGraph(cursor_x + weapon1_cursor_pos, cursor_y + 50 + (LEVEL_HIERARCHY_HEIGHT * (weapon1_level_hierarchy + 1)), 0.1f, 0.0f, img_chooce, TRUE);
			}
		}
		else
		{
			// 武器2
			if (weapon2_info.level_hierarchy <= MAX_LEVEL_HIERARCHY)
			{
				// カーソル表示
				DrawRotaGraph(cursor_x + weapon2_info.cursor_pos, cursor_y + (LEVEL_HIERARCHY_HEIGHT * (weapon2_info.level_hierarchy + 1)), 0.08f, 0.0f, img_cursor, TRUE);

				// レベル選択の円を描画
				//DrawCircle(cursor_x + weapon2_info.cursor_pos, cursor_y + 50 + (LEVEL_HIERARCHY_HEIGHT * (weapon2_info.level_hierarchy + 1)), 20, 0xb00000, FALSE);
			}
		}
	}

#ifdef _DEBUG	
	// テスト表示
	//SetFontSize(20);
	//DrawFormatString(0, 210, 0xa00000, "W1level(State) : %d", weapon1_info.level);
	//DrawFormatString(0, 230, 0xa00000, "W1レベル階層 : %d", weapon1_info.level_hierarchy);
	//DrawFormatString(0, 250, 0xa00000, "W1tmpレベル : %d", weapon1_info.tmp_level);
	//DrawFormatString(0, 270, 0xa00000, "close_mode : %d", close_mode);
	//DrawFormatString(0, 270, 0x000000, "W2level (State): %d", weapon2_info.level);
	//DrawFormatString(0, 290, 0x000000, "W2レベル階層 : %d", weapon2_info.level_hierarchy);
	//DrawFormatString(0, 310, 0x000000, "W2tmpレベル : %d", weapon2_info.tmp_level);
	//DrawFormatString(0, 90, 0x000000, "1cursor_pos : %d", weapon1_info.cursor_pos);
	//DrawFormatString(0, 110, 0x000000, "2cursor_pos : %d", weapon2_info.cursor_pos);
	//DrawFormatString(0, 130, 0x000000, "level_cursor_pos : %d", level_cursor_pos);
	//DrawFormatString(0, 130, 0x000000, "level_cursor_pos : %d", level_cursor_pos);
	//DrawFormatString(0, 0, 0x000000, "branch_point_x[0][0] : %d", branch_point_x[0][0]);
	//DrawFormatString(0, 20, 0x000000, "cursor_x : %d", cursor_x);

	// 多分現在のプレイヤーのステータス
	//DrawFormatString(0, 20, 0xf0f0f0, "weapon.cppからの情報");
	//DrawFormatString(0, 40, 0xf0f0f0, "w_p_speed : %d", w_p_speed);
	//DrawFormatString(0, 60, 0xf0f0f0, "w_p_avoidancecooltime : %d", w_p_avoidancecooltime);
	//DrawFormatString(0, 80, 0xf0f0f0, "w_p_upperlimitlimit : %d", w_p_upperlimitlimit);
	//
	//DrawFormatString(0, 120, 0xf0f0f0, "player.cppからの情報");
	//DrawFormatString(0, 140, 0xf0f0f0, "p_speed : %f", p_speed);
	//DrawFormatString(0, 160, 0xf0f0f0, "p_avoidancecooltime : %d", p_avoidancecooltime);
	//DrawFormatString(0, 180, 0xf0f0f0, "p_upperlimitlimit : %f", p_upperlimitlimit);

	//DrawFormatString(0, 210, 0xa00000, "cool_time : %d", weapon1_info.cool_time);
	//DrawFormatString(0, 230, 0xa00000, "damage : %d", weapon1_info.damege);
	//DrawFormatString(0, 250, 0xa00000, "範囲 : %f", weapon1_info.attack_range);

	//DrawFormatString(0, 270, 0xa00000, "tmp_cool_time : %d", weapon1_info.tmp_cool_time);
	//DrawFormatString(0, 290, 0xa00000, "tmp_damage : %d", weapon1_info.tmp_damege);
	//DrawFormatString(0, 310, 0xa00000, "tmp_範囲 : %f", weapon1_info.tmp_attack_range);

#endif
}

// 初期化処理
void WeaponLevelUp::Init(weapon* weapon, second_weapon* second_weapon, bool& restor_cursor_position)
{
	// 武器選択時変数
	weapon_selection = false;
	cursor_x = 580;
	weapon_number = weapon1_info.num;

	// レベルアップカーソルの初期化
	if (weapon1_info.level_hierarchy == 1 || weapon1_info.level_hierarchy == MAX_LEVEL_HIERARCHY)
	{
		// カーソル位置は左
		weapon1_info.cursor_pos = -level_cursor_pos;
	}
	else if (weapon2_info.level_hierarchy == 1 || weapon2_info.level_hierarchy == MAX_LEVEL_HIERARCHY)
	{		
		// カーソル位置は左
		weapon2_info.cursor_pos = -level_cursor_pos;
	}

	// 現在の武器レベルのセット
	weapon1_info.level = weapon->GetWeaponLevel();
	weapon2_info.level = second_weapon->GetWeaponLevel();

	// 武器の種類のセット
	weapon1_info.type = weapon->GetWeaponType();
	weapon2_info.type = second_weapon->GetWeaponType();

	// 初期化完了
	restor_cursor_position = false;

	//close = false;
}

// レベルアップ処理
void WeaponLevelUp::LevelUp(weapon* weapon, second_weapon* second_weapon, Player* player, weapon_information* info, int& point)
{
	if (info->level_hierarchy < MAX_LEVEL_HIERARCHY && point > 0)
	{
		// 通常のレベルアップ
		point--;

		// カーソルがさしているレベルをセット
		info->level = info->tmp_level;

		// 選択した分岐点の画像用パラメータの更新
		is_chooce[info->num][info->level_hierarchy] = true;
		branch_point_y[info->num][info->level_hierarchy] += LEVEL_HIERARCHY_HEIGHT * info->level_hierarchy;

		if (info->num == weapon1_info.num)
		{
			// 画像用パラメータxの更新
			branch_point_x[info->num][info->level_hierarchy] += info->cursor_pos;

			// 武器1にレベルのセット
			weapon->SetWeaponLevel(info->level);
			info->tmp_cool_time = weapon->GetMaxCoolTime();
			info->tmp_damege = weapon->GetDamage();
			info->tmp_attack_range = weapon->GetMaxRot();
		}
		else
		{
			// 画像用パラメータxの更新
			branch_point_x[info->num][info->level_hierarchy] += 380 + info->cursor_pos;

			// 武器2にレベルのセット
			second_weapon->SetWeaponLevel(info->level);
			info->tmp_cool_time = second_weapon->GetMaxCoolTime();
			info->tmp_damege = second_weapon->GetDamage();
			info->tmp_attack_range = second_weapon->GetMaxRot();
			tmp_frail_radiusX = player->GetPlayer_RadiusX();
			tmp_frail_radiusY = player->GetPlayer_RadiusY();
		}

		info->level_hierarchy++;
		//// レベル階層の制御
		//if (info->level_hierarchy > MAX_LEVEL_HIERARCHY)
		//{
		//	info->level_hierarchy = MAX_LEVEL_HIERARCHY;
		//}

		// playerからのプレイヤー情報
		p_speed = player->GetPlayer_Speed();
		p_avoidancecooltime = player->GetAvoidance_limit();
		p_upperlimitlimit = player->GetPlayer_Upperlimit();

	}
	else if (info->level_hierarchy == MAX_LEVEL_HIERARCHY && is_blacksmith == true)
	{
		// 最終強化

		if (info->cursor_pos == -level_cursor_pos)
		{
			// 樹形図の左を選択
			info->level = 7;
		}
		else
		{
			// 樹形図の右を選択
			info->level = 8;
		}

		// 選択した分岐点の画像用パラメータの更新
		is_chooce[info->num][info->level_hierarchy] = true;
		branch_point_y[info->num][info->level_hierarchy] += LEVEL_HIERARCHY_HEIGHT * info->level_hierarchy;

		if (info->num == weapon1_info.num)
		{
			// 画像用パラメータxの更新
			branch_point_x[info->num][info->level_hierarchy] += info->cursor_pos;

			// 武器1にレベルのセット
			weapon->SetWeaponLevel(info->level);
		}
		else
		{
			// 画像用パラメータxの更新
			branch_point_x[info->num][info->level_hierarchy] += 380 + info->cursor_pos;

			// 武器2にレベルのセット
			second_weapon->SetWeaponLevel(info->level);
		}

		info->level_hierarchy++;

		info->cursor_pos = 0;

		// playerからのプレイヤー情報
		p_speed = player->GetPlayer_Speed();
		p_avoidancecooltime = player->GetAvoidance_limit();
		p_upperlimitlimit = player->GetPlayer_Upperlimit();

		info->tmp_cool_time = weapon->GetMaxCoolTime();
		info->tmp_damege = weapon->GetDamage();
		info->tmp_attack_range = weapon->GetMaxRot();
	}
}

// レベルアップのカーソル移動
void WeaponLevelUp::LevelUpCursorMove(weapon_information* info)
{
	// 武器1のレベルカーソル移動
	if (info->level_hierarchy == 0 || info->level_hierarchy == 3)
	{
		// カーソル移動無し
		info->cursor_pos = 0;
	}
	else if (info->level_hierarchy == 1 || info->level_hierarchy == MAX_LEVEL_HIERARCHY)
	{
		if (info->cursor_pos == 0)
		{
			// レベルの選択ができるときカーソル初期位置は左
			info->cursor_pos = -level_cursor_pos;
		}

		// レベルの選択
		if (InputCtrl::GetStickRatio(L).x > 0.8 && interval >= 15)
		{
			//左スティックを右に
			info->cursor_pos = level_cursor_pos;
		}
		else if (InputCtrl::GetStickRatio(L).x < -0.8 && interval >= 15)
		{
			//左スティックを左に
			info->cursor_pos = -level_cursor_pos;
		}
	}
}

// レベルアップカーソルの位置を戻す
void WeaponLevelUp::ReturnLevelUpCursorPos(weapon_information* info)
{
	if (info->level_hierarchy == 1 || info->level_hierarchy == MAX_LEVEL_HIERARCHY)
	{
		// レベルアップカーソルの位置を左にする
		info->cursor_pos = -level_cursor_pos;
	}
}

// レベルアップ詳細のテキスト群
void WeaponLevelUp::DrawLevelUpDetails() const
{
	// レベルアップの詳細枠
	DrawBox(190, 90, 420, 680, 0x000000, FALSE);
	//if (weapon_selection == true)
	//{

	// テキスト
	DrawFormatString(200, 180, 0x000000, "レベルアップ詳細");

		if (weapon_number == weapon1_info.num)
		{
			DrawFormatString(200, 220, 0x000000, "ダメージ");
			DrawFormatString(200, 240, 0x000000, "　%d　→　%d", weapon1_info.tmp_damege, weapon1_info.damege);
			DrawFormatString(200, 260, 0x000000, "攻撃クールタイム");
			DrawFormatString(200, 280, 0x000000, "　%d　→　%d", weapon1_info.tmp_cool_time, weapon1_info.cool_time);
			DrawFormatString(200, 300, 0x000000, "攻撃範囲");
			DrawFormatString(200, 320, 0x000000, "　%.1f　→　%.1f", weapon1_info.tmp_attack_range, weapon1_info.attack_range);
			
			DrawFormatString(200, 360, 0x000000, "プレイヤーステータス");
			DrawFormatString(200, 380, 0x000000, "移動速度");
			DrawFormatString(200, 400, 0x000000, "　%.1f　→　%.1f", p_speed, w_p_speed);
			DrawFormatString(200, 420, 0x000000, "回避速度");
			DrawFormatString(200, 440, 0x000000, "　%.1f　→　%.1f", p_avoidancecooltime, w_p_avoidancecooltime);
			DrawFormatString(200, 460, 0x000000, "回避クールタイム");
			DrawFormatString(200, 480, 0x000000, "　%.1f　→　%.1f", p_upperlimitlimit, w_p_upperlimitlimit);
		}
		else if(weapon2_info.type != none)
		{
			DrawFormatString(200, 220, 0x000000, "ダメージ");
			DrawFormatString(200, 240, 0x000000, "　%d　→　%d", weapon2_info.tmp_damege, weapon2_info.damege);
			DrawFormatString(200, 260, 0x000000, "攻撃クールタイム");
			DrawFormatString(200, 280, 0x000000, "　%d　→　%d", weapon2_info.tmp_cool_time, weapon2_info.cool_time);
			DrawFormatString(200, 300, 0x000000, "攻撃範囲");
			DrawFormatString(200, 320, 0x000000, "　%.1f　→　%.1f", weapon2_info.tmp_attack_range, weapon2_info.attack_range);

			if (weapon2_info.type == frail)
			{
				// 照準はどこまで攻撃が届くか（鎖の長さ）
				//DrawFormatString(200, 380, 0x000000, "攻撃距離X");
				//DrawFormatString(200, 400, 0x000000, "　%.1f　→　%.1f", tmp_frail_radiusX, frail_radiusX);
				//DrawFormatString(200, 420, 0x000000, "攻撃距離Y");
				//DrawFormatString(200, 440, 0x000000, "　%.1f　→　%.1f", tmp_frail_radiusY, frail_radiusY);
				DrawFormatString(200, 340, 0x000000, "鉄球の飛距離");
				DrawFormatString(200, 360, 0x000000, "　%.1f　→　%.1f", tmp_frail_radiusX, frail_radiusX);
			}
		}
	//}

	// 武器名の表示
	if (cursor_x == 580)
	{
		switch (weapon1_info.type)
		{
		case sword:			// 片手剣
			DrawFormatString(200, 100, 0x000000, "片手剣");
			break;
		case dagger:		// 短剣
			DrawFormatString(200, 100, 0x000000, "短剣");
			break;
		case greatSword:	// 大剣
			DrawFormatString(200, 100, 0x000000, "大剣");
			break;
		default:
			DrawFormatString(200, 100, 0xb00000, "武器がありません");
			break;
		}

		// レベルの表示
		DrawFormatString(200, 120, 0x000000, "Lv. %d",weapon1_info.level);
	}
	else
	{
		switch (weapon2_info.type)
		{
		case spear:
			DrawFormatString(200, 100, 0x000000, "槍");
			break;
		case frail:
			DrawFormatString(200, 100, 0x000000, "フレイル");
			break;
		case book:
			DrawFormatString(200, 100, 0x000000, "魔導書");
			break;
		default:
			DrawFormatString(200, 100, 0xb00000, "武器がありません");
			break;
		}

		if (weapon2_info.type != none)
		{
			// レベルの表示
			DrawFormatString(200, 120, 0x000000, "Lv. %d", weapon2_info.level);
		}
	}
	
	// 武器選択済み
	if (weapon_selection == true)
	{
		if (weapon_number == weapon1_info.num)
		{
			if (weapon1_info.level_hierarchy == MAX_LEVEL_HIERARCHY)
			{
				// 武器1最終強化のテキスト群
				DrawWeapon1FinalText();
			}
			else if (lv_point <= 0)
			{
				DrawFormatString(200, 140, 0xb00000, "ポイントが足りません");
			}
		}
		else
		{
			if (weapon2_info.level_hierarchy == MAX_LEVEL_HIERARCHY)
			{
				// 武器2最終強化のテキスト群
				DrawWeapon2FinalText();
			}
			else if (lv_point <= 0)
			{
				DrawFormatString(200, 140, 0xb00000, "ポイントが足りません");
			}
		}
	}
}

// 武器1最終強化のテキスト群
void WeaponLevelUp::DrawWeapon1FinalText() const
{
	DrawFormatString(200, 140, 0xb00000, "次は最終強化です");
	//DrawFormatString(200, 140, 0xb00000, "→鍛冶");

	if (weapon1_info.cursor_pos == -level_cursor_pos)
	{
		// レベル7
		switch (weapon1_info.type)
		{
		case sword:			// 片手剣
			DrawFormatString(200, 520, 0x000000, "伝説の剣");
			DrawFormatString(200, 550, 0x000000, "斬撃を飛ばす");
			break;
		case dagger:		// 短剣
			DrawFormatString(200, 520, 0x000000, "アサシンダガ―");
			//SetFontSize(15);
			DrawFormatString(200, 550, 0x000000, "回避した軌道にいる敵\nにダメージを与える");
			break;
		case greatSword:	// 大剣
			DrawFormatString(200, 520, 0x000000, "旋風斬");
			DrawFormatString(200, 550, 0x000000, "回転攻撃に変化する");
			break;
		default:
			DrawFormatString(200, 520, 0xb00000, "武器がありません");
			break;
		}
	}
	else
	{
		// レベル8
		switch (weapon1_info.type)
		{
		case sword:			// 片手剣
			DrawFormatString(200, 520, 0x000000, "魔剣ブラッドファング");
			DrawFormatString(200, 550, 0x000000, "自傷武器に変化する\n自傷した際に攻撃力が\n上がり、連続で攻撃を\n当てると微量ながら\n回復する");
			break;
		case dagger:		// 短剣
			DrawFormatString(200, 520, 0x000000, "投げナイフ");
			DrawFormatString(200, 550, 0x000000, "照準の方向にナイフを\n5本発射する");
			break;
		case greatSword:	// 大剣
			DrawFormatString(200, 520, 0x000000, "砂塵の太刀");
			DrawFormatString(200, 550, 0x000000, "砂ぼこりが起こり\n敵に小ダメージを\n与える");
			break;
		default:
			DrawFormatString(200, 520, 0xb00000, "武器がありません");
			break;
		}
	}
}

// 武器2最終強化のテキスト群
void WeaponLevelUp::DrawWeapon2FinalText() const
{
	DrawFormatString(200, 140, 0xb00000, "次は最終強化です");

	if (weapon2_info.cursor_pos == -level_cursor_pos)
	{
		// レベル7
		switch (weapon2_info.type)
		{
		case spear:
			DrawFormatString(200, 520, 0x000000, "ロイヤルランス");
			DrawFormatString(200, 550, 0x000000, "攻撃範囲が縦方向に\n拡大される");
			break;
		case frail:
			DrawFormatString(200, 520, 0x000000, "三つ首の鎖");
			DrawFormatString(200, 550, 0x000000, "鉄球が３つになる");
			break;
		case book:
			DrawFormatString(200, 520, 0x000000, "賢者の加護");
			//SetFontSize(15);
			DrawFormatString(200, 550, 0x000000, "武器ダメージが上がり\n一定時間武器のクール\nタイムが減少しバリア\nがつくが、バリアは攻\n撃されると消える");
			break;
		default:
			DrawFormatString(200, 520, 0xb00000, "武器がありません");
			break;
		}
	}
	else
	{
		// レベル8
		switch (weapon2_info.type)
		{
		case spear:
			DrawFormatString(200, 520, 0x000000, "グングニル");
			DrawFormatString(200, 550, 0x000000, "攻撃が当たった敵に\n雷が落ちる");
			break;
		case frail:
			DrawFormatString(200, 520, 0x000000, "アースクラッシャー");
			DrawFormatString(200, 550, 0x000000, "鉄球が大きくなり\n地割れが発生する");
			break;
		case book:
			DrawFormatString(200, 520, 0x000000, "エンチャントバレット");
			DrawFormatString(200, 550, 0x000000, "球が６つ円状に回転し\n攻撃をする");
			break;
		default:
			DrawFormatString(200, 520, 0xb00000, "武器がありません");
			break;
		}
	}
}

// 武器1のレベルリセット処理
void WeaponLevelUp::Weapon1LevelInit()
{
	weapon1_info.level_hierarchy = 0;
	weapon1_info.cursor_pos = 0;

	for (int i = 0; i <= MAX_LEVEL_HIERARCHY; i++)
	{
		branch_point_x[0][i] = cursor_x;
		branch_point_y[0][i] = img_branch_point_y;
		is_chooce[0][i] = false;
	}
}

// 武器2のレベルリセット処理
void WeaponLevelUp::Weapon2LevelInit()
{
	weapon2_info.level_hierarchy = 0;
	weapon2_info.cursor_pos = 0;

	for (int i = 0; i <= MAX_LEVEL_HIERARCHY; i++)
	{
		branch_point_x[1][i] = cursor_x;
		branch_point_y[1][i] = img_branch_point_y;
		is_chooce[1][i] = false;
	}
}

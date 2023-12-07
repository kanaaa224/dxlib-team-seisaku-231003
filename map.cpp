//#include "map.h"
#include "main.h"

Map::Map() {

	// アイコン移動初期化処理
	cursor_pos = 0;
	cursor_loc = 0;
	move_cool = 0;
	cursor_move = FALSE;
	cursor_r = 45;
	alpha = 0;
	alpha_flg = TRUE;

	// 画像読込
	if (battle_img == 0) battle_img = (LoadGraph("resources/images/skeleton.png"));
	if (event_img == 0) event_img = (LoadGraph("resources/images/event.png"));
	if (rest_img == 0) rest_img = (LoadGraph("resources/images/rest.png"));
	if (anvil_img == 0) anvil_img = (LoadGraph("resources/images/anvil.png"));
	if (boss_img == 0) boss_img = (LoadGraph("resources/images/boss.png"));
	if (icon_back_img == 0) icon_back_img = (LoadGraph("resources/images/icon_back.png"));
	if (cross_img == 0) cross_img = (LoadGraph("resources/images/cross.png"));
	if (crown_img == 0) crown_img = (LoadGraph("resources/images/crown.png"));
	if (roof_img == 0) roof_img = (LoadGraph("resources/images/maps/roof.png"));
	if (wall_img == 0) wall_img = (LoadGraph("resources/images/maps/wall.png"));
	if (tower_img == 0) tower_img = (LoadGraph("resources/images/maps/tower.png"));
	if (map_back_img == 0) map_back_img = (LoadGraph("resources/images/map_back.png"));
	if (button_a_image == 0) button_a_image = LoadGraph("resources/images/button_a.png");
	if (decision_img == 0) decision_img = LoadGraph("resources/images/Logo/UI/logo_dicision.png");

	SoundManager::SetBGM("bgm_map");
	SoundManager::SetVolumeBGM("bgm_map", 50);
	SetLoopPosSoundMem(4798,SoundManager::GetBGMHandle("bgm_map"));

	// リザルト画面用
	battle_count = 0;
	event_count = 0;
	rest_count = 0;
	anvil_count = 0;
	boss_count = 0;
}
Map::~Map() {
	DeleteGraph(battle_img);
	DeleteGraph(event_img);
	DeleteGraph(rest_img);
	DeleteGraph(anvil_img);
	DeleteGraph(boss_img);
	DeleteGraph(cross_img);
	DeleteGraph(crown_img);
	DeleteGraph(roof_img);
	DeleteGraph(wall_img);
	DeleteGraph(tower_img);
	DeleteGraph(map_back_img);
	DeleteGraph(button_a_image);
	DeleteGraph(decision_img);
}

int Map::update(int& mode, int& battleMode, bool& weapon_selected) {

	SoundManager::PlaySoundBGM("bgm_map");

	// アイコン移動距離
	int icon_vec = 0;

	if (map_move != map_move_log) {
		if (map_move < 0) map_move = 0;
		else if (map_move > 470) map_move = 470;
		for (int i = 0; i < data_max; i++) {
			icon_loc[i][1] = icon_loc_def[pattern][i][1] + map_move;
			icon_loc_center[i][1] = icon_loc[i][1] + 25;
		}
		map_move_log = map_move;
	}

	// カーソル移動(Lスティック)
	if (move_cool <= 0) {
		if (next_stage[pattern][now_stage][1] != -1)
		{
			if (InputCtrl::GetStickRatio(L).x >= 0.3) {
				//カーソルの移動音
				SoundManager::PlaySoundSE("se_system_select_syu", false);
				if (cursor_pos + 1 <= 2 && next_stage[pattern][now_stage][cursor_pos + 1] != -1) {
					cursor_pos++;
					cursor_loc = next_stage[pattern][now_stage][cursor_pos];
					move_cool = 15;
				}
				else {
					cursor_pos = 0;
					cursor_loc = next_stage[pattern][now_stage][cursor_pos];
					move_cool = 15;
				}
				cursor_move = TRUE;
				cursor_r = 45;
			}
			else if (InputCtrl::GetStickRatio(L).x <= -0.3) {
				//カーソルの移動音
				SoundManager::PlaySoundSE("se_system_select_syu", false);
				if (cursor_pos - 1 >= 0) {
					cursor_pos--;
					cursor_loc = next_stage[pattern][now_stage][cursor_pos];
					move_cool = 15;
				}
				else {
					for (int i = 2; i > 0; i--) {
						if (next_stage[pattern][now_stage][i] != -1) {
							cursor_pos = i;
							cursor_loc = next_stage[pattern][now_stage][cursor_pos];
							move_cool = 15;
							break;
						}
					}
				}
				cursor_move = TRUE;
				cursor_r = 45;
			}
		}
	}
	else if(InputCtrl::GetStickRatio(L).x < 0.3 && InputCtrl::GetStickRatio(L).x > -0.3){
		move_cool = 0;
	}
	else { move_cool--; }

	// カーソル移動でカーソルが画面内に収まるようにする
	if (cursor_move == TRUE) {
		if (icon_loc[cursor_loc][1] <= 50) {
			icon_vec = 10;
		}
		else if (icon_loc[cursor_loc][1] > SCREEN_HEIGHT - 100) {
			icon_vec = -10;
		}
	}

	// カーソル移動後処理
	if (cursor_r >= 30) {
		 {
			cursor_r = 30;
		}
		cursor_r--;
	}

	if (alpha_flg) {
		alpha = alpha + 4;
		if (alpha >= 255) {
			alpha = 255;
			alpha_flg = FALSE;
		}
	} else {
		alpha = alpha - 4;
		if (alpha <= 0) {
			alpha = 0;
			alpha_flg = TRUE;
		}
	}

	// スクロール(Rスティック)
	if (InputCtrl::GetStickRatio(R).y >= 0.2 || InputCtrl::GetStickRatio(R).y <= -0.2)
	{
		icon_vec = 0;
		cursor_move = FALSE;
		// 上スクロール
		if (icon_loc[data_max - 1][1] < 170) {
			if (InputCtrl::GetStickRatio(R).y >= 0.2 && InputCtrl::GetStickRatio(R).y < 0.5) {
				icon_vec = 1;
			}
			else if (InputCtrl::GetStickRatio(R).y >= 0.5 && InputCtrl::GetStickRatio(R).y < 0.8) {
				icon_vec = 3;
			}
			else if (InputCtrl::GetStickRatio(R).y >= 0.8) {
				icon_vec = 5;
			}
		}
		// 下スクロール
		if (icon_loc[0][1] > SCREEN_HEIGHT - 100) {
			if (InputCtrl::GetStickRatio(R).y <= -0.2 && InputCtrl::GetStickRatio(R).y > -0.5) {
				icon_vec = -1;
			}
			else if (InputCtrl::GetStickRatio(R).y <= -0.5 && InputCtrl::GetStickRatio(R).y > -0.8) {
				icon_vec = -3;
			}
			else if (InputCtrl::GetStickRatio(R).y <= -0.8) {
				icon_vec = -5;
			}
		}
	}

	// アイコン移動処理
	if (icon_vec != 0) {
		map_move = map_move + icon_vec;
	}
	// Aボタンでカーソルのステージに遷移
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS || InputCtrl::GetKeyState(KEY_INPUT_RETURN) == PRESS) {

		SoundManager::StopSoundBGM("bgm_map");
		SoundManager::SetSoundBGMsPosition(0);
		//カーソルの決定音
		SoundManager::PlaySoundSE("se_system_normal_decision", false);

		now_stage = cursor_loc;

		switch (MapData[now_stage])
		{
		case 0:		//戦闘
			if (weapon_selected) mode = GameSceneMode::main;
			else mode = GameSceneMode::weaponSelect;

			battleMode = GameSceneBattleMode::normal;
			battle_count++;
			break;
		case 1:		//イベント（中ボス）
			if (weapon_selected) mode = GameSceneMode::main;
			else mode = GameSceneMode::weaponSelect;

			battleMode = GameSceneBattleMode::midBoss;
			event_count++;
			break;
		case 2:		//休憩
			mode = GameSceneMode::rest;
			ClearStage();
			rest_count++;
			break;
		case 3:		//鍛冶屋
			mode = GameSceneMode::blacksmith;
			ClearStage();
			anvil_count++;
			break;
		case 4:		//ボス
			if (weapon_selected) mode = GameSceneMode::main;
			else mode = GameSceneMode::weaponSelect;

			battleMode = GameSceneBattleMode::boss;
			ClearStage();
			boss_count++;
			break;
		default:
			break;
		}

		return 0;
	}
};

void Map::draw() const {

	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0xaaaaaa, 1);
	DrawExtendGraph(200, -500 + map_move, SCREEN_WIDTH - 200, SCREEN_HEIGHT + 70 + map_move, map_back_img, 1);
	DrawExtendGraph(250, -450 + map_move, 1070, -170 + map_move, roof_img, 1);
	DrawExtendGraph(370, -170 + map_move, 940, 680 + map_move, wall_img, 1);
	//DrawGraph(370, -170 + map_move, wall_img, 1);

	int log_i = 0; // stage_log用変数
	int x_img = 0;
	for (int i = 0; i < DATA_MAX; i++)
	{

			// ステージ間のライン
		for (int j = 0; next_stage[pattern][i][j] > 0 && j <= 2; j++) {
			int next_loc = next_stage[pattern][i][j];
			if (stage_log[log_i] == i && stage_log[log_i + 1] == next_loc) {
				DrawLineAA(icon_loc_center[i][0], icon_loc_center[i][1],
					icon_loc_center[next_loc][0], icon_loc_center[next_loc][1], 0xFFD000, 5);
				log_i++;
			}
			else if (i == now_stage && j == cursor_pos) {

				DrawLineAA(icon_loc_center[i][0], icon_loc_center[i][1],
					icon_loc_center[next_loc][0], icon_loc_center[next_loc][1], GetColor(255, 208 + (alpha * (255 - 208) / 255), alpha), 9.0f - ((float)alpha * 4 / 255));
			}
			else {
				DrawLineAA(icon_loc_center[i][0], icon_loc_center[i][1],
					icon_loc_center[next_loc][0], icon_loc_center[next_loc][1], 0x888888, 5);
			}
		}
			DrawGraph(icon_loc[i][0] - 5, icon_loc[i][1] - 5, icon_back_img, TRUE);
		// アイコン表示
		switch (MapData[i]) {
		case 0:
			DrawGraph(icon_loc[i][0], icon_loc[i][1], battle_img, TRUE);
			break;
		case 1:
			DrawGraph(icon_loc[i][0], icon_loc[i][1], event_img, TRUE);
			break;
		case 2:
			DrawGraph(icon_loc[i][0], icon_loc[i][1], rest_img, TRUE);
			break;
		case 3:
			DrawGraph(icon_loc[i][0], icon_loc[i][1], anvil_img, TRUE);
			break;
		case 4:
			DrawGraph(icon_loc[i][0], icon_loc[i][1], boss_img, TRUE);
			break;
		default:
			break;
		}
		if (i == stage_log[x_img]) {
			DrawGraph(icon_loc[i][0], icon_loc[i][1], cross_img, TRUE);
			//DrawGraph(icon_loc[i][0] + 10, icon_loc[i][1] - 20, crown_img, TRUE);
			x_img++;
		}
		
		// カーソル表示(アイコンの円と被るように半径に-1)
		DrawCircle(icon_loc_center[cursor_loc][0], icon_loc_center[cursor_loc][1], cursor_r - 1, 0x050505, 0, 5);
		DrawCircle(icon_loc_center[cursor_loc][0], icon_loc_center[cursor_loc][1], cursor_r - 1, 0xFFD000, 0, 3);

		// Aボタン
		DrawGraph(1150, 650, button_a_image, TRUE);
		DrawString(1194, 662, "決定\n", 0xffffff);
	}

#ifdef _DEBUG	
	DrawFormatString(0, 80, 0xffffff, "リザルト用（仮）");
	DrawFormatString(0, 100, 0xffffff, "battle_count : %d", battle_count);
	DrawFormatString(0, 120, 0xffffff, "event_count : %d", event_count);
	DrawFormatString(0, 140, 0xffffff, "rest_count : %d", rest_count);
	DrawFormatString(0, 160, 0xffffff, "anvil_count : %d", anvil_count);
	DrawFormatString(0, 180, 0xffffff, "boss_count : %d", boss_count);
#endif
}

void Map::ResetStage() {

	// マップデータ,ログ初期化処理
	for (int i = 0; i < DATA_MAX; i++)
	{
		MapData[i] = 0;
		if (sizeof(stage_log) / sizeof(stage_log[0]) > i) {
			stage_log[i] = -1;
		}
	}

	pattern = 1;//GetRand(PATTERN_MAX - 1);
	data_max = pattern_data_max[pattern];
	now_stage = data_max - 1;

	// マップ生成(0:戦闘、1:ランダムイベント、2:休憩、3:鍛冶屋、4:ボス)

	// ランダムイベント
	SetStage(map_ctrl[pattern][0][0], map_ctrl[pattern][0][1], map_ctrl[pattern][0][2], map_ctrl[pattern][0][3], map_ctrl[pattern][0][4], 1);

	// 休憩1
	SetStage(map_ctrl[pattern][1][0], map_ctrl[pattern][1][1], map_ctrl[pattern][1][2], map_ctrl[pattern][1][3], map_ctrl[pattern][1][4], 2);
	// 休憩2
	SetStage(map_ctrl[pattern][2][0], map_ctrl[pattern][2][1], map_ctrl[pattern][2][2], map_ctrl[pattern][2][3], map_ctrl[pattern][2][4], 2);
	// 休憩3
	SetStage(map_ctrl[pattern][3][0], map_ctrl[pattern][3][1], map_ctrl[pattern][3][2], map_ctrl[pattern][3][3], map_ctrl[pattern][3][4], 2);
	// 休憩4
	MapData[data_max - 2] = 2;

	// 鍛冶屋
	SetStage(map_ctrl[pattern][4][0], map_ctrl[pattern][4][1], map_ctrl[pattern][4][2], map_ctrl[pattern][4][3], map_ctrl[pattern][4][4], 3);

	// ボス
	MapData[data_max - 1] = 4;

	// アイコン位置をデフォルトにセット
	for (int i = 0; i < data_max; i++)
	{
		icon_loc[i][0] = icon_loc_def[pattern][i][0];
		icon_loc[i][1] = icon_loc_def[pattern][i][1];
		icon_loc_center[i][0] = icon_loc_def[pattern][i][0] + 25;
		icon_loc_center[i][1] = icon_loc_def[pattern][i][1] + 25;
		map_move = 0;
		map_move_log = 0;
	}
}

void Map::SetStage(int st_min, int st_max, int rand_min, int rand_max, int type ,int data_num) {
	int RandNum = GetRand(rand_max - rand_min) + rand_min;
	switch (type)
	{
	case 0:
		for (int i = 0; i < RandNum;) {
			int r = GetRand(st_max - st_min) + st_min;
			// 未変更(0なら)変更
			if (MapData[r] == 0) {
				MapData[r] = data_num;
				i++;
			}
			else continue;
		}
		break;
	case 1:
		for (int i = 0; i < RandNum;) {
			int r;
			switch (GetRand(1))
			{
			case 0:
				r = st_min;
				break;
			case 1:
				r = st_max;
				break;
			default:
				break;
			}
			// 未変更(0なら)変更
			if (MapData[r] == 0) {
				MapData[r] = data_num;
				i++;
			}
			else continue;
		}
		break;
	default:
		break;
	}
	
}
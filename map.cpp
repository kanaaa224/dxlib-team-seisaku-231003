//#include "map.h"
#include "main.h"

Map::Map() {

	// アイコン移動初期化処理
	icon_vec = 0;
	cursor_pos = 0;
	cursor_loc = 0;
	move_cool = 0;
	cursor_move = FALSE;
	cursor_r = 30;
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
}
Map::~Map() {
	DeleteGraph(battle_img);
	DeleteGraph(event_img);
	DeleteGraph(rest_img);
	DeleteGraph(anvil_img);
	DeleteGraph(boss_img);
	DeleteGraph(cross_img);
}

int Map::update(int& mode, int& battleMode, bool& weapon_selected) {

	// アイコン移動距離リセット
	icon_vec = 0;


	// カーソル移動(Lスティック)
	if (move_cool <= 0) {
		if (InputCtrl::GetStickRatio(L).x >= 0.3) {
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
		if (next_stage[pattern][now_stage][1] == -1) {
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
		if (icon_loc[data_max - 1][1] < 50) {
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
		for (int i = 0; i < data_max; i++)
		{
			icon_loc[i][1] = icon_loc[i][1] + icon_vec;
			icon_loc_center[i][1] = icon_loc[i][1] + 25;
		}
	}
	// Aボタンでカーソルのステージに遷移
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS || InputCtrl::GetKeyState(KEY_INPUT_RETURN) == PRESS) {

		now_stage = cursor_loc;

		switch (MapData[now_stage])
		{
		case 0:		//戦闘
			if (weapon_selected) mode = GameSceneMode::main;
			else mode = GameSceneMode::weaponSelect;

			battleMode = GameSceneBattleMode::normal;

			break;
		case 1:		//イベント（中ボス）
			if (weapon_selected) mode = GameSceneMode::main;
			else mode = GameSceneMode::weaponSelect;

			battleMode = GameSceneBattleMode::midBoss;

			break;
		case 2:		//休憩
			mode = GameSceneMode::rest;
			ClearStage();
			break;
		case 3:		//鍛冶屋
			mode = GameSceneMode::blacksmith;
			break;
		case 4:		//ボス
			if (weapon_selected) mode = GameSceneMode::main;
			else mode = GameSceneMode::weaponSelect;

			battleMode = GameSceneBattleMode::boss;

			ClearStage();
			break;
		default:
			break;
		}

		return 0;
	}
};

void Map::draw() const {
	int log_i = 0; // stage_log用変数
	int x_img = 0;
	for (int i = 0; i < DATA_MAX; i++)
	{
		// デバック表示
		DrawFormatString(10, 30, 0xffff00, "内部データ");
		DrawFormatString(10 * i + 10, 50, 0xffffff, "%d", MapData[i]);
		DrawFormatString(10, 680, 0xffffff, "Aボタンでカーソルのステージへ");

			// ステージ間のライン
			for (int j = 0; next_stage[pattern][i][j] > 0 && j <= 2; j++) {
				int next_loc = next_stage[pattern][i][j];
				if (stage_log[log_i] == i && stage_log[log_i + 1] == next_loc) {
					DrawLineAA(icon_loc_center[i][0], icon_loc_center[i][1],
						icon_loc_center[next_loc][0], icon_loc_center[next_loc][1], 0xaa0000, 5);
					log_i++;
				}
				else if (i == now_stage && j == cursor_pos) {

					DrawLineAA(icon_loc_center[i][0], icon_loc_center[i][1],
						icon_loc_center[next_loc][0], icon_loc_center[next_loc][1], GetColor(255, alpha, alpha), 9.0f - ((float)alpha * 4 / 255));
				}
				else {
					DrawLineAA(icon_loc_center[i][0], icon_loc_center[i][1],
						icon_loc_center[next_loc][0], icon_loc_center[next_loc][1], 0xffffff, 5);
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
				x_img++;
			}
			//アイコン番号表示(Debug)
			DrawFormatString(icon_loc[i][0], icon_loc[i][1], 0x00ff00, "%d", i);
		
		// カーソル表示(アイコンの円と被るように半径に-1)
		DrawCircle(icon_loc_center[cursor_loc][0], icon_loc_center[cursor_loc][1], cursor_r - 1, 0xff0000, 0, 3);
	}
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

	pattern = GetRand(PATTERN_MAX - 1);
	data_max = pattern_data_max[pattern];
	now_stage = data_max - 1;

	// マップ生成(0:戦闘、1:ランダムイベント、2:休憩、3:鍛冶屋、4:ボス)
	// 生成内容(ステージ範囲)(ステージ数) 

	// ランダムイベント(st7固定)
	SetStage(map_ctrl[pattern][0][0], map_ctrl[pattern][0][1], map_ctrl[pattern][0][2], map_ctrl[pattern][0][3], 1);

	// 休憩1(st3-6)(1-2)
	SetStage(map_ctrl[pattern][1][0], map_ctrl[pattern][1][1], map_ctrl[pattern][1][2], map_ctrl[pattern][1][3], 2);
	// 休憩2(st8-18)(2-3)
	SetStage(map_ctrl[pattern][2][0], map_ctrl[pattern][2][1], map_ctrl[pattern][2][2], map_ctrl[pattern][2][3], 2);
	// 休憩3(ボス前)
	MapData[data_max - 2] = 2;

	// 鍛冶屋(st15-18)(1)
	SetStage(map_ctrl[pattern][3][0], map_ctrl[pattern][3][1], map_ctrl[pattern][3][2], map_ctrl[pattern][3][3], 3);

	// ボス
	MapData[data_max - 1] = 4;

	// アイコン位置をデフォルトにセット
	for (int i = 0; i < data_max; i++)
	{
		icon_loc[i][0] = icon_loc_def[pattern][i][0];
		icon_loc[i][1] = icon_loc_def[pattern][i][1];
		icon_loc_center[i][0] = icon_loc_def[pattern][i][0] + 25;
		icon_loc_center[i][1] = icon_loc_def[pattern][i][1] + 25;
	}
}

void Map::SetStage(int st_min, int st_max, int rand_min, int rand_max, int data_num) {
	int RandNum = GetRand(rand_max - rand_min) + rand_min;
	for (int i = 0; i < RandNum;) {
		int r = GetRand(st_max - st_min) + st_min;
		// 未変更(0なら)変更
		if (MapData[r] == 0) {
			MapData[r] = data_num;
			i++;
		}
		else continue;
	}
}
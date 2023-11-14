

#include "main.h"
#include "map_temp.h"

map_temp::map_temp() {
	// マップデータ初期化処理
	for (int i = 0; i <= DATA_MAX; i++)
	{
		MapDeta[i] = 0;
	}


	// マップ生成(0:戦闘、1:ランダムイベント、2:休憩、3:鍛冶屋、4:ボス)
	// 生成内容(ステージ範囲)(ステージ数) 

	// ランダムイベント(st7固定)
	MapDeta[7] = 1;

	// 休憩1(st3-6)(1-2)
	RandNum[0] = GetRand(1) + 1;
	for (int i = 0; i < RandNum[0];) {
		int r = GetRand(3) + 3;
		// 未変更(0なら)変更
		if (MapDeta[r] == 0) {
			MapDeta[r] = 2;
			i++;
		}
		else continue;
	}
	// 休憩2(st8-18)(2-3)
	RandNum[1] = GetRand(1) + 2;
	for (int i = 0; i < RandNum[1];) {
		int r = GetRand(11) + 8;
		// 未変更(0なら)変更
		if (MapDeta[r] == 0) {
			MapDeta[r] = 2;
			i++;
		}
		else continue;
	}
	// 休憩3(st19固定)
	MapDeta[19] = 2;

	// 鍛冶屋(st14-18)(1)
	RandNum[2] = 1;
	for (int i = 0; i < RandNum[2];) {
		int r = GetRand(5) + 14;
		// 未変更(0なら)変更
		if (MapDeta[r] == 0) {
			MapDeta[r] = 3;
			i++;
		}
		else continue;
	}

	// ボス(st20固定)
	MapDeta[20] = 4;

	// アイコン位置をデフォルトにセット
	for (int i = 0; i < DATA_MAX; i++)
	{
		icon_loc[i][0] = icon_loc_def[i][0];
		icon_loc[i][1] = icon_loc_def[i][1];
		icon_loc_change[i][0] = icon_loc_def[i][0];
		icon_loc_change[i][1] = icon_loc_def[i][1];
	}

	// 移動量初期化処理
	icon_vec = 0;
	total_vec = 0;
	change_icon = 0;
	change_icon_tab = 0;

	// 画像読込
	if (battle_img == 0) battle_img = (LoadGraph("resources/images/skeleton.png"));
	if (event_img == 0) event_img = (LoadGraph("resources/images/event.png"));
	if (rest_img == 0) rest_img = (LoadGraph("resources/images/rest.png"));
	if (anvil_img == 0) anvil_img = (LoadGraph("resources/images/anvil.png"));
	if (boss_img == 0) boss_img = (LoadGraph("resources/images/boss.png"));
	if (map_cursor == 0) map_cursor = (LoadGraph("resources/images/map_cursor.png"));
}
map_temp::~map_temp() {
	DeleteGraph(battle_img);
	DeleteGraph(event_img);
	DeleteGraph(rest_img);
	DeleteGraph(anvil_img);
	DeleteGraph(boss_img);
	DeleteGraph(map_cursor);
}

Scene* map_temp::update() {

	// アイコン移動距離リセット
	icon_vec = 0;

	// スクロール
	if (InputCtrl::GetStickRatio(L).y >= 0.2 || InputCtrl::GetStickRatio(L).y <= -0.2)
	{
		// 上スクロール
		if (icon_loc[20][1] < 50) {
			if (InputCtrl::GetStickRatio(L).y >= 0.2 && InputCtrl::GetStickRatio(L).y < 0.5) {
				icon_vec = 1;
			}
			else if (InputCtrl::GetStickRatio(L).y >= 0.5 && InputCtrl::GetStickRatio(L).y < 0.8) {
				icon_vec = 3;
			}
			else if (InputCtrl::GetStickRatio(L).y >= 0.8) {
				icon_vec = 5;
			}
		}
		// 下スクロール
		if (icon_loc[0][1] > SCREEN_HEIGHT - 100) {
			if (InputCtrl::GetStickRatio(L).y <= -0.2 && InputCtrl::GetStickRatio(L).y > -0.5) {
				icon_vec = -1;
			}
			else if (InputCtrl::GetStickRatio(L).y <= -0.5 && InputCtrl::GetStickRatio(L).y > -0.8) {
				icon_vec = -3;
			}
			else if (InputCtrl::GetStickRatio(L).y <= -0.8) {
				icon_vec = -5;
			}
		}
	}

	// アイコン移動処理
	for (int i = 0; i < DATA_MAX; i++)
	{
		icon_loc[i][1] = icon_loc[i][1] + icon_vec;
	}

	// 総合移動量加算
	total_vec = total_vec + icon_vec;

	if (InputCtrl::GetKeyState(KEY_INPUT_0) == PRESS) {
		change_icon = change_icon_tab * 10 + 0;
	}
	if (InputCtrl::GetKeyState(KEY_INPUT_1) == PRESS) {
		change_icon = change_icon_tab * 10 + 1;
	}
	if (InputCtrl::GetKeyState(KEY_INPUT_2) == PRESS) {
		change_icon = change_icon_tab * 10 + 2;
	}
	if (InputCtrl::GetKeyState(KEY_INPUT_3) == PRESS) {
		change_icon = change_icon_tab * 10 + 3;
	}
	if (InputCtrl::GetKeyState(KEY_INPUT_4) == PRESS) {
		change_icon = change_icon_tab * 10 + 4;
	}
	if (InputCtrl::GetKeyState(KEY_INPUT_5) == PRESS) {
		change_icon = change_icon_tab * 10 + 5;
	}
	if (InputCtrl::GetKeyState(KEY_INPUT_6) == PRESS) {
		change_icon = change_icon_tab * 10 + 6;
	}
	if (InputCtrl::GetKeyState(KEY_INPUT_7) == PRESS) {
		change_icon = change_icon_tab * 10 + 7;
	}
	if (InputCtrl::GetKeyState(KEY_INPUT_8) == PRESS) {
		change_icon = change_icon_tab * 10 + 8;
	}
	if (InputCtrl::GetKeyState(KEY_INPUT_9) == PRESS) {
		change_icon = change_icon_tab * 10 + 9;
	}
	if (InputCtrl::GetKeyState(KEY_INPUT_TAB) == PRESS) {
		if (DATA_MAX - 1 > (change_icon_tab + 1) * 10) {
			change_icon_tab++;
			change_icon = 10 + change_icon;
		}
		else {
			change_icon_tab = 0;
			change_icon = change_icon % 10;
		}
	}

	if (InputCtrl::GetKeyState(KEY_INPUT_UP) == PRESS) {
		icon_loc[change_icon][1] = icon_loc[change_icon][1] - 10;
		icon_loc_change[change_icon][1] = icon_loc_change[change_icon][1] - 10;
	}
	if (InputCtrl::GetKeyState(KEY_INPUT_DOWN) == PRESS) {
		icon_loc[change_icon][1] = icon_loc[change_icon][1] + 10;
		icon_loc_change[change_icon][1] = icon_loc_change[change_icon][1] + 10;
	}
	if (InputCtrl::GetKeyState(KEY_INPUT_LEFT) == PRESS) {
		icon_loc[change_icon][0] = icon_loc[change_icon][0] - 10;
		icon_loc_change[change_icon][0] = icon_loc_change[change_icon][0] - 10;
	}
	if (InputCtrl::GetKeyState(KEY_INPUT_RIGHT) == PRESS) {
		icon_loc[change_icon][0] = icon_loc[change_icon][0] + 10;
		icon_loc_change[change_icon][0] = icon_loc_change[change_icon][0] + 10;
	}

	// BでDebugScene
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_B) == PRESS) {
		return new DebugScene;
	}

	return this;
};

void map_temp::draw() const {

	for (int i = 0; i < DATA_MAX; i++)
	{
		// デバック表示
		DrawFormatString(10, 30, 0xffff00, "内部データ");
		DrawFormatString(10 * i + 10, 50, 0xffffff, "%d", MapDeta[i]);
		DrawFormatString(10, 700, 0xffffff, "BボタンでDebugScene");

		// ステージ間のライン
		for (int j = 0; next_stage[i][j] > 0 && j <= 2; j++)
		{
			int next_loc = next_stage[i][j];

			DrawLine(icon_loc[i][0] + 25, icon_loc[i][1] + 25,
				icon_loc[next_loc][0] + 25, icon_loc[next_loc][1] + 25, 0xffffff);
		}

		// アイコン表示
		switch (MapDeta[i]) {
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
		DrawFormatString(icon_loc[i][0], icon_loc[i][1], 0x00ff00, "%d", i);
		DrawFormatString(icon_loc[i][0] - 45, icon_loc[i][1] + 50, 0x007000, "(x:%d , y:%d)", icon_loc_change[i][0], icon_loc_change[i][1]);
	}
	DrawFormatString(0, 480, 0x00ff00, "(x:%d , y:%d)", icon_loc_change[change_icon][0], icon_loc_change[change_icon][1]);
	SetFontSize(16);
	DrawFormatString(0, 370, 0xffffff, "TAB:%d0～%d9", change_icon_tab, change_icon_tab);
	SetFontSize(64);
	DrawFormatString(20, 400, 0xffffff, "%d", change_icon);

	// 罫線描画(100毎)
	//for (int i = -20; i <= 20; i++)
	//{
	//	DrawLine(-2000, 100 * i + total_vec, 2000, 100 * i + total_vec, 0xffffff); // x座標
	//	DrawLine(100 * i, -2000 + total_vec, 100 * i, 2000 + total_vec, 0xffffff); // y座標
	//}
}

#include "main.h"
#include "map.h"

Map::Map() {
	// マップデータ初期化処理
	for (int i = 0; i <= DATA_MAX; i++)
	{
		MapData[i] = 0;
	}

	// マップ生成(0:戦闘、1:ランダムイベント、2:休憩、3:鍛冶屋、4:ボス)
	MapData[7] = 1;


	RandNum[0] = GetRand(1) + 1;
	for (int i = 0; i < RandNum[0]; i++) {
		int r = GetRand(3) + 3;
		if (MapData[r] == 0) {
			MapData[r] = 2;
		}else continue;
	}

	RandNum[1] = GetRand(1) + 2;
	for (int i = 0; i < RandNum[1]; i++) {
		int r = GetRand(10) + 9;
		if (MapData[r] == 0) {
			MapData[r] = 2;
		}
		else continue;
	}
	MapData[19] = 2;


	RandNum[2] = GetRand(1) + 1;
	for (int i = 0; i < RandNum[2]; i++) {
		int r = GetRand(10) + 9;
		if (MapData[r] == 0) {
			MapData[r] = 3;
		}
		else continue;
	}


	MapData[20] = 4;

	for (int i = 0; i < DATA_MAX; i++)
	{
		icon_loc[i][0] = icon_loc_def[i][0];
		icon_loc[i][1] = icon_loc_def[i][1];
	}

	icon_vec = 0;
	cursor_pos = 0;
	move_cool = 0;
	cursor_move = FALSE;
	// 画像読込
	if (battle_img == 0) battle_img = (LoadGraph("resources/images/skeleton.png"));
	if (event_img == 0) event_img = (LoadGraph("resources/images/event.png"));
	if (rest_img == 0) rest_img = (LoadGraph("resources/images/rest.png"));
	if (anvil_img == 0) anvil_img = (LoadGraph("resources/images/anvil.png"));
	if (boss_img == 0) boss_img = (LoadGraph("resources/images/boss.png"));
	if (map_cursor == 0) map_cursor = (LoadGraph("resources/images/map_cursor.png"));
}
Map::~Map() {

}

Scene* Map::update() {

	icon_vec = 0;

	if (move_cool <= 0) {
		if (InputCtrl::GetStickRatio(L).y >= 0.3 && cursor_pos < DATA_MAX - 1) {
			cursor_pos++;
			move_cool = 15;
			cursor_move = TRUE;
		}
		else if (InputCtrl::GetStickRatio(L).y <= -0.3 && cursor_pos > 0) {
			cursor_pos--;
			move_cool = 15;
			cursor_move = TRUE;
		}
	}
	else { move_cool--; }


	if (cursor_move == TRUE){
		if (icon_loc[cursor_pos][1] <= 50) {
			icon_vec = 10;
		}
		else if (icon_loc[cursor_pos][1] >= SCREEN_HEIGHT - 100) {
			icon_vec = -10;
		}
	}

	

	if (InputCtrl::GetStickRatio(R).y >= 0.2 || InputCtrl::GetStickRatio(R).y <= -0.2)
	{
		icon_vec = 0;
		cursor_move = FALSE;

		if (icon_loc[20][1] < 50) {
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

	for (int i = 0; i < DATA_MAX; i++)
	{
		icon_loc[i][1] = icon_loc[i][1] + icon_vec;
	}

	if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS) {
		switch (MapData[cursor_pos])
		{
		case 0:
			return new GameScene;
			break;
		case 1:
			return new DebugScene;
			break;
		case 2:
			return new DebugScene;
			break;
		case 3:
			return new DebugScene;
			break;
		case 4:
			return new DebugScene;
			break;
		default:
			break;
		}
	}


	if (InputCtrl::GetButtonState(XINPUT_BUTTON_B) == PRESS) {
		return new DebugScene;
	}

	return this;
};

void Map::draw() const {

	for (int i = 0; i < DATA_MAX; i++)
	{
		DrawFormatString(10, 30, 0xffff00, "内部データ");
		DrawFormatString(10 * i + 10, 50, 0xffffff, "%d", MapData[i]);
		DrawFormatString(10, 680, 0xffffff, "Aボタンでカーソルのステージへ");
		DrawFormatString(10, 700, 0xffffff, "BボタンでDebugSceneへ");

		// ステージ間のライン
		for (int j = 0; next_stage[i][j] != 0 && j <= 2; j++)
		{
			int next_loc = next_stage[i][j];

			DrawLine(icon_loc[i][0] + 25, icon_loc[i][1] + 25,
				icon_loc[next_loc][0] + 25, icon_loc[next_loc][1] + 25, 0xffffff);
		}

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
	}
	DrawGraph(icon_loc[cursor_pos][0], icon_loc[cursor_pos][1], map_cursor, TRUE);

}
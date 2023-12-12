#pragma once

#include "rest.h"


#define PATTERN_MAX 3
#define DATA_MAX 21

class Map
{
private:
	int MapData[DATA_MAX];

	// アイコン座標(初期)
	const int icon_loc_def[PATTERN_MAX][DATA_MAX][2] = { {
		{430, 620}, {630, 620}, {830, 620}, {390, 500}, {530, 510},
		{730, 510}, {880, 500}, {630, 400}, {470, 300}, {630, 230},
		{820, 300}, {380, 110}, {560, 110}, {760, 170}, {880, 170},
		{820, 50}, {470, -70}, {630, 0}, {820, -70}, {630, -170},
		{630, -270},
	}, {
		{530, 620}, {730, 620}, {430, 500}, {630, 500}, {730, 500},
		{530, 400}, {730, 400}, {630, 350}, {430, 250}, {780, 250},
		{430, 160}, {560, 160}, {780, 160}, {430, 60}, {560, 60},
		{730, 60}, {830, 60}, {560, -60}, {780, -60}, {630, -170},
		{630, -270},
	}, {
		{630, 620}, {550, 550}, {750, 570}, {470, 470}, {630, 470},
		{750, 500}, {750, 430}, {630, 350}, {500, 250}, {750, 250},
		{450, 150}, {550, 150}, {700, 150}, {800, 150}, {500, 60},
		{750, 60}, {500, -40}, {750, -40}, {630, -70}, {630, -170},
		{630, -270},
	} };
	int icon_loc[DATA_MAX][2];        // アイコン座標
	int icon_loc_center[DATA_MAX][2]; // アイコン座標(中央)
	int map_move;
	int map_move_log;

	// 次に行けるステージ
	const int next_stage[PATTERN_MAX][DATA_MAX][3]{ {
			{3,-1,-1},{4,5,-1},{6,-1,-1},{7,-1,-1},{7,-1,-1},
		    {7,-1,-1},{7,-1,-1},{8,9,10},{11,12,-1},{17,-1,-1},
			{13,14,-1},{16,-1,-1},{16,-1,-1},{15,-1,-1},{15,-1,-1},
			{18,-1,-1},{19,-1,-1},{19,-1,-1},{19,-1,-1},{20,-1,-1},
			{0,1,2}
		}, {
			{2,3,-1},{4,-1,-1},{5,-1,-1},{5,-1,-1},{6,-1,-1},
			{7,-1,-1},{7,-1,-1},{8,9,-1},{10,11,-1},{12,-1,-1},
			{13,-1,-1},{14,-1,-1},{15,16,-1},{17,-1,-1},{17,-1,-1},
			{18,-1,-1},{18,-1,-1},{19,-1,-1},{19,-1,-1},{20,-1,-1},
			{0,1,-1}
		}, {
			{1,2,-1},{3,4,-1},{5,-1,-1},{7,-1,-1},{7,-1,-1},
			{6,-1,-1},{7,-1,-1},{8,9,-1},{10,11,-1},{12,13,-1},
			{14,-1,-1},{14,-1,-1},{15,-1,-1},{15,-1,-1},{16,-1,-1},
			{17,-1,-1},{18,-1,-1},{18,-1,-1},{19,-1,-1},{20,-1,-1},
			{0,-1,-1}
		},
	};
	int stage_log[10];
	int pattern;
	const int pattern_data_max[PATTERN_MAX]{ 21,21,21 };
	int data_max;

	int cursor_pos;    // カーソル位置(次ステージ)
	int cursor_loc;    // カーソル位置(全体マップ)
	int move_cool;     // カーソル移動クールタイム
	bool cursor_move;  // カーソル移動によるカメラ移動をするか(スクロール移動すると解除)
	int cursor_r;      // カーソル半径
	int alpha;
	bool alpha_flg;
	int now_stage;     // 現在のステージ
	int no_input_time;
	bool intro_flg;
	int intro_time;
	int select_draw;
	int select_loc;

	// 画像
	int battle_img = 0;
	int event_img = 0;
	int rest_img = 0;
	int anvil_img = 0;
	int boss_img = 0;
	int icon_back_img = 0;
	int cross_img = 0;
	int roof_img = 0;
	int wall_img = 0;
	int map_back_img = 0;
	int button_a_image = 0;
	int decision_img = 0;
	int map_first_img = 0;
	int stage_select_img = 0;

	// リザルト画面で使用（縮小マップ作成が無理だった場合）
	// ステージに何回到達したか
	int battle_count;		// 通常ステージ
	int event_count;		// イベント
	int rest_count;			// 休憩
	int anvil_count;		// 鍛冶
	int boss_count;			// ボス

public:
	Map();

	~Map();

	int update(int&, int&, bool&);

	void draw() const;

	int NowStage() {
		return now_stage;
	}

	// ステージクリア後処理
	void ClearStage() {
		cursor_pos = 0;
		cursor_loc = next_stage[pattern][now_stage][0];
		cursor_r = 45;
		int center_def = 360 - icon_loc[cursor_loc][1];
		map_move = map_move + center_def;
		alpha = 0;
		alpha_flg = TRUE;
		no_input_time = 30;
		select_draw = 180;
		select_loc = -120;
		for (int i = 0; i <= 10; i++) {
			if (stage_log[i] == -1) {
				stage_log[i] = now_stage;
				break;
			}
		}
		switch (MapData[now_stage])
		{
		case 0:		//戦闘
			battle_count++;
			break;
		case 1:		//イベント（中ボス）
			event_count++;
			break;
		case 2:		//休憩
			rest_count++;
			break;
		case 3:		//鍛冶屋
			anvil_count++;
			break;
		case 4:		//ボス
			boss_count++;
			break;
		default:
			break;
		}
	}

	void ResetStage();

	void SetStage(int st_min, int st_max, int rand_min, int rand_max, int type, int data_num);

	// リザルト画面用
	int GetBattleCount() { return battle_count; }
	int GetEventCount() { return event_count; }
	int GetRestCount() { return rest_count; }
	int GetAnvilCount() { return anvil_count; }
	int GetBossCount() { return boss_count; }
};
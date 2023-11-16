#pragma once
#include"DxLib.h"
#include"scene.h"

#define DATA_MAX 21 // 最大ステージ数

class map_temp : public Scene
{

private:
	int MapDeta[DATA_MAX]; // マップ内部データ
	int RandNum[3];        // GetRand格納用

	// アイコン座標(初期)
	const int icon_loc_def[DATA_MAX][2] = {
	{630, 590}, {530, 540}, {730, 540}, {470, 470}, {580, 470},
	{730, 470}, {530, 400}, {630, 320}, {530, 220}, {730, 220},
	{430, 120}, {530, 120}, {630, 120}, {480, 30}, {580, 30},
	{730, 30}, {530, -20}, {730, -70}, {630, -130}, {630, -200},
	{630, -300},
	};
	int icon_loc[DATA_MAX][2];         // アイコン座標
	int icon_vec;                      // アイコン移動量
	int total_vec;                     // 総合移動量

	// テンプレート調整用変数
	int icon_loc_change[DATA_MAX][2];  // 変更後デフォルトアイコン座標
	int change_icon;                   // 移動させるアイコン
	int change_icon_tab;               // 移動させるアイコン(十の位)

	// 次に行けるステージ(最後は1番最初の選択ステージ)
	const int next_stage[DATA_MAX][3]{
		{1,2,-1},{3,4,-1},{5,-1},{6,-1},
		{6,-1},{7,-1},{7,-1},{8,9,-1},{10,11,12},
		{15,-1},{13,-1},{13,14,-1},{14,-1},{16,-1},
		{16,-1},{17,-1},{18,-1},{18,-1},{19,-1},
		{20,-1},{0,1,2}
	};

	// 画像
	int battle_img = 0;
	int event_img = 0;
	int rest_img = 0;
	int anvil_img = 0;
	int boss_img = 0;
	int map_cursor = 0;
public:
	map_temp();

	~map_temp();

	virtual Scene* update() override;

	virtual void draw() const override;
};

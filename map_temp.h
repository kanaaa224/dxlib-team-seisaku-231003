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
	{360, 590}, {630, 610}, {920, 580}, {390, 470}, {570, 510},
	{730, 480}, {910, 470}, {640, 370}, {440, 270}, {580, 220},
	{800, 290}, {340, 180}, {710, 160}, {960, 210}, {460, 80},
	{850, 130}, {760, 40}, {380, -80}, {860, -110}, {640, -200},
	{640, -300},
	};
	int icon_loc[DATA_MAX][2];         // アイコン座標
	int icon_loc_change[DATA_MAX][2];
	int icon_vec;                      // アイコン移動量
	int total_vec;                     // 総合移動量
	int change_icon;                   // 移動させるアイコン
	int change_icon_tab;               // 移動させるアイコン(十の位)

	// 次に行けるステージ(最後は1番最初の選択ステージ)
	const int next_stage[DATA_MAX][3]{
		{3,4,-1},{4,-1},{5,6,-1},{7,-1},
		{7,-1},{7,-1},{7,-1},{8,9,10},{11,14,-1},
		{12,14,-1},{12,13,-1},{14,-1},{16,-1},{15,-1},
		{17,18,-1},{16,-1},{17,18,-1},{19,-1},{19,-1},
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

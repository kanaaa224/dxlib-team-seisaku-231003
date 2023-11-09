#pragma once
#include"DxLib.h"
#include"SphereCollider.h"
#include"scene_rest.h"

class GameScene;

#define DATA_MAX 21

class Map : SphereCollider
{
private:
	int MapDeta[DATA_MAX];
	int RandNum[3];

	// ƒAƒCƒRƒ“À•W(‰Šú)
	int icon_loc_def[21][2] = {
	{360, 590}, {630, 610}, {920, 580}, {390, 470}, {570, 510},
	{730, 480}, {910, 470}, {640, 370}, {440, 270}, {580, 220},
	{800, 290}, {340, 180}, {710, 160}, {960, 210}, {460, 80},
	{850, 130}, {760, 40}, {380, -80}, {860, -110}, {640, -200},
	{640, -300},
	};
	int icon_loc[21][2];  // ƒAƒCƒRƒ“À•W
	int icon_vec;         // ƒAƒCƒRƒ“ˆÚ“®—Ê

	// Ÿ‚És‚¯‚éƒXƒe[ƒW
	int next_stage[21][3]{
		{3,4},{4},{5,6},{7},{7},
		{7},{7},{8,9,10},{11,14},{12,14},
		{12,13},{14},{16},{15},{17,18},
		{16},{17,18},{19},{19},{20},
	};

	Rest* rest;

	int cursor_pos;    // ƒJ[ƒ\ƒ‹ˆÊ’u
	int cursor_loc_x, cursor_loc_y;
	int move_cool;     // ƒJ[ƒ\ƒ‹ˆÚ“®ƒN[ƒ‹ƒ^ƒCƒ€
	bool cursor_move;  // ƒJ[ƒ\ƒ‹ˆÚ“®‚É‚æ‚éƒJƒƒ‰ˆÚ“®‚ğ‚·‚é‚©(ƒXƒNƒ[ƒ‹ˆÚ“®‚·‚é‚Æ‰ğœ)
	int angle;
	int r;

	//bool& map_flg;

	bool is_rest;		//‹xŒeƒXƒe[ƒW‚Ìƒtƒ‰ƒO
	bool is_show_rest;	//‹xŒeƒXƒe[ƒW‚ğ‰f‚·H

	// ‰æ‘œ
	int battle_img = 0;
	int event_img = 0;
	int rest_img = 0;
	int anvil_img = 0;
	int boss_img = 0;
	int map_cursor = 0;
public:
	Map(GameScene*gamemain);

	~Map();

	int update();

<<<<<<< HEAD
	void draw() const;

	bool GetIsMapMode()
	{
		return is_map_mode;
	}

	void SetIsMapMode(const bool flg)
	{
		is_map_mode = flg;
	}

=======
	virtual void draw() const override;
>>>>>>> parent of 5ada5a5 (ä¸å¿…è¦ãªã‚‚ã®ã‚’æ¶ˆã—ãŸ)
};
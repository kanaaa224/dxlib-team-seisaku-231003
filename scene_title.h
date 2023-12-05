#pragma once

#include "scene.h"
#define TITLEINTERVAL 15
#define TITLECURSOR 4

#define TITLE_MOVE_DOWN -0.5f
#define TITLE_MOVE_UP 0.5f

#define TITLE_STAR_BRIGHT_COLOR1 -2.0f
#define TITLE_STAR_BRIGHT_COLOR2 1.5f

#define TITLE_SELECT_MG /*0.4*/ 0.1


class Title :public Scene
{
private:

	//画像の読込用変数
	int TitleImage;
	int Titlelogo;
	int Titlelogo_white;

	int Title_Background_Img[2];
	int Title_SkyStar_Img;

	int Title_Start_Img;
	int Title_Help_Img;
	int Title_Credit_Img;
	int Title_End_Img;

	int Title_Cosol_sword_Img;
	int Title_Cosol_greatsword_Img;
	int Title_Cosol_shortsword_Img;

	//セレクト倍率
	double Title_Select_magnification;
	double Title_Cosor_sword_Angle;
	double Title_Cosor_greatsword_Angle;
	double Title_Cosor_shortsword_Angle;

	//座標系
	float logo_white_x, logo_white_y;
	float logo_move_x, logo_move_y;
	int	  Title_Star_x[8], Title_Star_y[8];
	int Title_Cosor_greatsword_x;
	int Title_Cosor_greatsword_y;

	//フラグ系
	bool logo_location_y_flg;
	bool Title_Select_mg_flg;
	bool Title_Anim_flg;
	bool Title_FadeOut_flg;
	bool Title_FadeIn_flg;
	bool Title_select_flg;
	bool Title_Cursor_Flg;
	bool Title_logo_Anim_End_Flg;

	//fps系
	int Title_Animation_fps;

	//カウンタ
	int Star_Anim_Count;
	int Title_Star_rand_Count;

	//乱数
	int Title_Star_rand;

	//デバッグ用マウスポインタ
	int Title_Debug_Mousepoint_x;
	int Title_Debug_Mousepoint_y;

	//色
	int Title_Star_Anim_Color_red;
	int Title_Star_Anim_Color_green;
	int Title_Star_Anim_Color_blue;

	int g_MenuNumber;
	//カーソル画像読み込み用変数
	int cursor;
	int g_MenuY;
	//タイトルカーソル（スティック）制御用の変数
	int TitleInterval;

public:
	//コンストラクタ
	Title();
	~Title();
	//更新
	Scene* update() override;
	//描画
	void draw() const override;

	//タイトルロゴアニメーション
	void Title_logo_Animation();

	//星のランダム生成
	void Title_Star_Rands(int rands_x, int rands_y, int rands1_x, int rands1_y);

	//星のフェードアウト関数
	void Title_Star_FadeOut();

	//星のフェードイン関数
	void Title_Star_FadeIn();

	//タイトルのセレクトアニメーション
	void Title_Select_Anim();

	//タイトルのカーソルアニメーション
	void Title_Cursor_Anim();
};
#pragma once
#include"DxLib.h"

//画面サイズ
#define _SCREEN_HEIGHT_ 720 //縦
#define _SCREEN_WIDHT_	1280//横

//色
#define C_RED   GetColor(255,0,0)       //赤
#define C_GREEN GetColor(0,255,0)       //緑
#define C_BLUE  GetColor(0,0,255)       //青
#define C_BLACK GetColor(0,0,0)         //黒
#define C_WHITE GetColor(255,255,255)   //白

//当たり判定
#define COLLISION 1
#define NO_COLLISION 0

//プレイヤー
#define PLAYER_LOCATION_X 640
#define PLAYER_LOCATION_Y 360

//敵
//雑魚敵のリスポーンポイント
#define POINT_0_X  -50
#define POINT_0_Y  -50
#define POINT_1_X  295
#define POINT_1_Y  -50
#define POINT_2_X  615
#define POINT_2_Y  -50
#define POINT_3_X  935
#define POINT_3_Y  -50
#define POINT_4_X  1280
#define POINT_4_Y  -50
#define POINT_5_X  -50
#define POINT_5_Y  335
#define POINT_6_X  1280
#define POINT_6_Y  335
#define POINT_7_X  -50
#define POINT_7_Y  720
#define POINT_8_X  295
#define POINT_8_Y  720
#define POINT_9_X  615
#define POINT_9_Y  720
#define POINT_10_X 935
#define POINT_10_Y 720
#define POINT_11_X 1280
#define POINT_11_Y 720
//スライム
#define MAX_SLIME_NUM 10000//スライムの最大数
#define SLIME_1_STAGE_NUM 10 //１ステージ目のスライムの数
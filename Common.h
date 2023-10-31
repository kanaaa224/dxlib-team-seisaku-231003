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
#define NO_COLLISION 0
#define HIT          1
#define OVERLAP      2

//プレイヤー
#define PLAYER_LOCATION_X 640
#define PLAYER_LOCATION_Y 360

//敵
// 
#define MAX_ALPHA 255		//透過の最大値
//スライム
#define SLIME_HP_MAX 100.0f	//HP
#define MAX_SLIME_NUM 10000	//スライムの最大数
#define SLIME_1_STAGE_NUM 1 //１ステージ目のスライムの数
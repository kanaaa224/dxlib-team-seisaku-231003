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
#define DAMAGE_STOP_FRAME 60//ダメージストップ（ダメージが与えられた時）
#define KNCKBACK 15.0f		//ノックバック
#define ENEMY_SPEED 1.8f	//敵の移動速度
#define RED_FRAME 15		//ダメージを受けた時の赤く表示するフレーム数

#define DISTANT  0			//遠ざかっている
#define APPROACH 1			//近づいている
#define SAME     2			//同じ

#define ENEMY_RADIUS 20//敵の半径

//スライム
#define SLIME_HP_MAX 20.0f		//HP
#define SLIME_ATTAK_DAMAGE 12.0f//ダメージ
#define MAX_SLIME_NUM 100		//スライムの最大数

#define SLIME_1_STAGE_NUM 10 //１ステージ目のスライムの数
#define SLIME_2_STAGE_NUM 15 //２ステージ目のスライムの数
#define SLIME_3_STAGE_NUM 20 //３ステージ目のスライムの数
#define SLIME_4_STAGE_NUM 25 //４ステージ目のスライムの数
#define SLIME_5_STAGE_NUM 30 //５ステージ目のスライムの数
#define SLIME_6_STAGE_NUM 35 //６ステージ目のスライムの数
#define SLIME_7_STAGE_NUM 40 //７ステージ目のスライムの数
#define SLIME_8_STAGE_NUM 45 //８ステージ目のスライムの数
#define SLIME_9_STAGE_NUM 50 //９ステージ目のスライムの数

//スケルトン
#define SKELETON_HP_MAX 40.0f		//HP
#define SKELETON_ATTAK_DAMAGE 16.0f	//ダメージ
#define MAX_SKELETON_NUM 30			//スケルトンの最大数

#define SKELETON_1_STAGE_NUM 3  //１ステージ目のスケルトンの数
#define SKELETON_2_STAGE_NUM 0  //２ステージ目のスケルトンの数
#define SKELETON_3_STAGE_NUM 0  //３ステージ目のスケルトンの数
#define SKELETON_4_STAGE_NUM 0  //４ステージ目のスケルトンの数
#define SKELETON_5_STAGE_NUM 3  //５ステージ目のスケルトンの数
#define SKELETON_6_STAGE_NUM 6  //６ステージ目のスケルトンの数
#define SKELETON_7_STAGE_NUM 9  //７ステージ目のスケルトンの数
#define SKELETON_8_STAGE_NUM 12 //８ステージ目のスケルトンの数
#define SKELETON_9_STAGE_NUM 15 //９ステージ目のスケルトンの数
#pragma once
#include"DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>

//ラジアンを度に変更
#define RADIAN_DEGREE(_rad) ((_rad)*180.0f/M_PI)
//秒をフレームに変更
#define SECOND_FRAME(_s) ((_s) * 60)

//
#define HIT_VECTOR 0.06f

//画像左右
#define IMG_L 0//左
#define IMG_R 1//右

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
#define DAMAGE_STOP_FRAME 30//ダメージストップ（ダメージが与えられた時）
#define KNCKBACK 30.0f		//ノックバック
#define ENEMY_SPEED 1.0f	//敵の移動速度
#define RED_FRAME 15		//ダメージを受けた時の赤く表示するフレーム数

#define DISTANT  0			//遠ざかっている
#define APPROACH 1			//近づいている
#define SAME     2			//同じ

#define ENEMY_RADIUS 20//敵の半径

//スライム
#define SLIME_HP_MAX 10.0f	//HP
#define SLIME_ATTAK_DAMAGE 1.0f	//最初のダメージ
#define MAX_SLIME_NUM 1000		//スライムの最大数

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
#define SKELETON_HP_MAX 20.0f		//HP
#define SKELETON_ATTAK_DAMAGE 2.0f	//ダメージ
#define MAX_SKELETON_NUM 300		//スケルトンの最大数

#define SKELETON_1_STAGE_NUM 0  //１ステージ目のスケルトンの数
#define SKELETON_2_STAGE_NUM 0  //２ステージ目のスケルトンの数
#define SKELETON_3_STAGE_NUM 0  //３ステージ目のスケルトンの数
#define SKELETON_4_STAGE_NUM 0  //４ステージ目のスケルトンの数
#define SKELETON_5_STAGE_NUM 3  //５ステージ目のスケルトンの数
#define SKELETON_6_STAGE_NUM 6  //６ステージ目のスケルトンの数
#define SKELETON_7_STAGE_NUM 9  //７ステージ目のスケルトンの数
#define SKELETON_8_STAGE_NUM 12 //８ステージ目のスケルトンの数
#define SKELETON_9_STAGE_NUM 15 //９ステージ目のスケルトンの数

//魔法使い
#define WIZARD_HP_MAX 4.0f			//HP
#define WIZARD_ATTAK_DAMAGE 1.0f	//ダメージ
#define MAX_WIZARD_NUM 100			//魔法使いの最大数

#define STOP_SHOOTING_DISTANCE 400 //プレイヤーとの距離がこの値になったら立ち止まる

#define WIZARD_1_STAGE_NUM 1 //１ステージ目の魔法使いの数←仮で数が入っている
#define WIZARD_2_STAGE_NUM 0 //２ステージ目の魔法使いの数
#define WIZARD_3_STAGE_NUM 0 //３ステージ目の魔法使いの数
#define WIZARD_4_STAGE_NUM 0 //４ステージ目の魔法使いの数
#define WIZARD_5_STAGE_NUM 0 //５ステージ目の魔法使いの数
#define WIZARD_6_STAGE_NUM 2 //６ステージ目の魔法使いの数
#define WIZARD_7_STAGE_NUM 3 //７ステージ目の魔法使いの数
#define WIZARD_8_STAGE_NUM 4 //８ステージ目の魔法使いの数
#define WIZARD_9_STAGE_NUM 5 //９ステージ目の魔法使いの数

//弾
#define BULLET_ATTAK_DAMAGE 2.0f	//ダメージ
#define MAX_BULLET_NUM 10000		//弾の最大数
#define BULLET_SPEED   3.0f			//弾の速度
#define BULLET_RADIUS  10			//弾の半径
#define BULLET_LIFE_TIME 120

//大きい弾
#define MAX_BIG_BULLET_NUM 3

//幽霊
#define MAX_GHOST_NUM 200

//ミノタウロス
#define BOX_MAX_WIDTH  50	//タックル攻撃予測の矩形の最大の幅
#define BOX_MAX_LENGTH 500	//タックル攻撃予測の矩形の長さ
#define TACKLE_SPEED   8	//タックルのスピード
#define ROAR_RADIUS    200	//咆哮の半径
#define PLAYER_RADIUS  23
#define MINOTAUR_MAX_HP 400		//ミノタウロスの最大HP
#define MINOTAUR_ATTAK_DAMAGE 10//ミノタウロスの攻撃力
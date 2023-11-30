#pragma once

#include "inputCtrl.h"
#include "scene.h"

class weapon;								// 最初の武器
class second_weapon;						// 二つ目の武器

class ResultScene : public Scene
{
private:

	// 画像用変数
	//int img_map;					// マップ
	//int img_branchPoint;			// 分岐点
	//int img_weapon1;				// 武器１
	//int img_weapon2;				// 武器２
	//int img_background;			// 背景
	int img_button_a;				// Aボタン

	// 武器画像読込用変数
	int img_sword;					// 片手剣
	int img_dagger;					// 短剣
	int img_great_sword;			//大剣
	int img_question_mark;			// はてなマーク（武器無しの場合）
	int img_spear;					// 槍
	int img_frail;					// フレイア
	int img_book;					// 本

	// フェード演出
	int value;						// 不透明度

	struct weapon_info
	{
		int type;					// 種類
		int level;					// レベル
		int damage;					// ダメージ総量
	};

	weapon_info weapon1_info;
	weapon_info weapon2_info;

	// テスト
	FILE* fp;
	struct Sample
	{
		int type;
		int level;
		int damage;
	};
	struct Sample sample[2];
	bool is_fopen;

public:
	ResultScene(int &num1,int &num2);
	//ResultScene();
	~ResultScene();

	// 更新
	Scene* update() override;

	// 描画
	void draw() const override;

};

